#ifndef GROBNER_BUCHBERGER_HPP
#define GROBNER_BUCHBERGER_HPP 1

#include <source/Polynomial.hpp>
#include <type_traits>
#include <vector>
#include <iostream>
#include <algorithm>

namespace grobner {

template<class Poly>
Poly reduction(Poly x, const std::vector<Poly> &base, size_t exclude = -1) {
    static_assert(std::is_base_of<Polynomial_Base, Poly>::value == true, 
                  "Poly must be Polynomial");
    size_t base_size = base.size(), undiv_interval = 0, i = 0;
    while(undiv_interval != base_size) {
        if(i != exclude && !base[i].is_zero() && can_div_poly(x, base[i])) {
            x %= base[i];
            undiv_interval = 1;
        } else {
            ++undiv_interval;
        }
        i = (i == base_size-1 ? 0 : i+1);
    }
    return x;
}

template<class Poly>
std::vector<Poly> buchberger_main(const std::vector<Poly> &x) {
    static_assert(std::is_base_of<Polynomial_Base, Poly>::value == true, 
                  "Poly must be Polynomial");
    auto basis = x;
    std::vector<Poly> que;
    for(size_t i = 0; i < basis.size(); i++) {
        for(size_t j = 0; j < i; j++) {
            que.push_back(S_poly(basis[i], basis[j]));
        }
    }
    while(!que.empty()) {
        auto y = que.back(); que.pop_back();
        if(y.is_zero()) continue;
        auto z = reduction(y, basis);
        if(!z.is_zero()) {
            for(const auto &b : basis) que.push_back(S_poly(z, b));
            basis.push_back(z);
        }
    }
    return basis;
}

template<class Poly>
std::vector<Poly> normalize(std::vector<Poly> &x){
    static_assert(std::is_base_of<Polynomial_Base, Poly>::value == true, 
                  "Poly must be Polynomial");
    std::vector<Poly> ret;
    for(size_t i = 0; i < x.size(); i++) {
        bool can_div = false;
        for(size_t j = i+1; j < x.size(); j++) {
            if(can_div_term(x[i].LM(), x[j].LM())) {
                can_div = true;
            }
        }
        if(!can_div) ret.push_back(x[i]);
    }
    #ifdef BUCHBERGER_DEBUG
    std::cerr << "normed=\n";
    for(auto &p : ret) std::cerr << p << std::endl;
    #endif
    for(size_t i = 0; i < ret.size(); i++) {
        ret[i] = reduction(ret[i], ret, i);
        if(!ret[i].is_zero()) ret[i] /= ret[i].LC();
        else ret.erase(ret.begin()+i);
    }
    return ret;
}

template<class Poly>
std::vector<Poly> buchberger(const std::vector<Poly> &x){
    static_assert(std::is_base_of<Polynomial_Base, Poly>::value == true, 
                  "Poly must be Polynomial");
    auto tmp = buchberger_main(x);
    #ifdef BUCHBERGER_DEBUG
    std::cerr << "inv=\n";
    for(auto &p : tmp) std::cerr << p << std::endl;
    #endif
    return normalize(tmp);
}

} // namespace grobner

#endif