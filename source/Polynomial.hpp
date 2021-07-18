#ifndef GROBNER_POLYNOMIAL_HPP
#define GROBNER_POLYNOMIAL_HPP 1

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cassert>
#include <functional>
#include <utility>
#include <type_traits>
#include <source/field.hpp>
#include <source/real_number.hpp>
#include <source/term_compare.hpp>

namespace grobner {

using Term = std::string;

static bool can_div_term(const Term &ls, const Term &rs) {
    auto liter = ls.cbegin(), riter = rs.cbegin();
    while(liter != ls.cend() && riter != rs.cend()) {
        if(*liter == *riter) {
            ++liter;
            ++riter;
        } else {
            ++liter;
        }
    }
    return riter == rs.cend();
}

static Term div_term (const Term &ls, const Term &rs) {
    auto liter = ls.cbegin(), riter = rs.cbegin();
    Term ret;
    while(liter != ls.cend() && riter != rs.cend()) {
        if(*liter == *riter) {
            ++liter;
            ++riter;
        } else {
            ret += *liter;
            ++liter;
        }
    }
    assert(riter == rs.cend());
    while(liter != ls.cend()) {
        ret += *liter;
        ++liter;
    }
    return ret;
}

Term gcd(const Term &x, const Term &y) {
    Term ret;
    auto xitr = x.cbegin(), yitr = y.cbegin();
    while(xitr != x.cend() && yitr != y.cend()) {
        if(*xitr == *yitr) {
            ret += *xitr;
            ++xitr;
            ++yitr;
        } else if(*xitr > *yitr) {
            ++yitr;
        } else {
            ++xitr;
        }
    }
    return ret;
}

class Polynomial_Base {};

/**
 * @brief class of Multivariate polynomial
 * 
 * @tparam Field 
 * @tparam Comp the functoin decide Order. default is Lexicograph
 */
template<class Field, class Comp = compare::Lexicograph>
class Polynomial : public Polynomial_Base {
    public:
    using Unary = std::pair<Term, Field>;
    static_assert(std::is_move_assignable<Unary>::value == true, "OK");
    Polynomial() : terms() {}
    Polynomial(const std::vector<Unary> &init) : Polynomial() {
        for(auto i : init) {
            std::sort(i.first.begin(), i.first.end());
            terms[i.first] += i.second;
        }
        clean_up();
    }
    Polynomial(const Field init) : Polynomial(std::vector<Unary>({make_pair(std::string(""), init)})) {
        clean_up();
    }
    Polynomial(const Term init) : Polynomial(std::vector<Unary>({make_pair(init, Field().e())})) {}
    ~Polynomial() {}
    std::vector<Unary> val() const {
        return std::vector<Unary>(terms.begin(), terms.end());
    }
    Polynomial o() {
        return Polynomial();
    }
    Polynomial e() const {
        return Polynomial(Field().e());
    }
    bool is_zero() const { return terms.empty(); }
    Polynomial LT() const {
        assert(!is_zero());
        return Polynomial({*terms.begin()});
    }
    Field LC() const {
        assert(!is_zero());
        return terms.begin()->second;
    }
    Term LM() const {
        assert(!is_zero());
        return terms.begin()->first;
    }
    /**
     * @brief calculate division of Polynomial.
     * 
     * @param rhs right value
     * @return std::pair<Polynomial, Polynomial> first element is quotient, second element is remainder.
     */
    std::pair<Polynomial, Polynomial> division(const Polynomial& rhs) {
        Polynomial lhs(*this);
        Polynomial quotient, remainder;
        while(!lhs.is_zero()) {
            if(can_div_term(lhs.LM(), rhs.LM())) {
                Term dm = div_term(lhs.LM(), rhs.LM());
                Field dc = lhs.LC() /  rhs.LC();
                Polynomial dpoly({{dm, dc}});
                lhs -= rhs * dpoly;
                quotient += dpoly;
            } else {
                Polynomial dpoly = lhs.LT();
                remainder += dpoly;
                lhs -= dpoly;
            }
        }
        return {quotient ,remainder};
    }
    Polynomial operator-() const {
        Polynomial ret(*this);
        for(auto &i : ret.terms) {
            i.second = -i.second;
        }
        return ret;
    }
    Polynomial& operator+=(const Polynomial& rhs) {
        std::vector<Term> erase_list;
        for(const auto &i : rhs.terms) {
            terms[i.first] += i.second;
            if(terms[i.first].is_zero()) erase_list.push_back(i.first);
        }
        for(const auto &i : erase_list) {
            terms.erase(i);
        }
        return *this;
    }
    Polynomial& operator-=(const Polynomial& rhs) {
        std::vector<Term> erase_list;
        for(const auto &i : rhs.terms) {
            terms[i.first] -= i.second;
            if(terms[i.first].is_zero()) erase_list.push_back(i.first);
        }
        for(const auto &i : erase_list) {
            terms.erase(i);
        }
        return *this;
    }
    Polynomial& operator*=(const Polynomial &rhs) {
        std::map<Term, Field, Comp> tmp_terms;
        for(const auto &i : rhs.terms) {
            for(const auto &j : terms) {
                Term merged_term = merge_term(i.first, j.first);
                tmp_terms[merged_term] += i.second * j.second;
                if(tmp_terms[merged_term].is_zero()) tmp_terms.erase(merged_term);
            }
        }
        terms = tmp_terms;
        return *this;
    }
    Polynomial& operator*=(const Field &rhs) {
        if(rhs.is_zero()) terms.clear();
        else {
            for(auto &i : terms) i.second *= rhs;
        }
        return *this;
    }
    Polynomial& operator/=(const Polynomial &rhs) {
        terms = division(rhs).first.terms;
        return *this;
    }
    Polynomial& operator/=(const Field &rhs) {
        assert(!rhs.is_zero());
        operator*=(rhs.inv());
        return *this;
    }
    Polynomial& operator%=(const Polynomial &rhs) {
        terms = division(rhs).second.terms;
        return *this;
    }
    Polynomial operator+(const Polynomial& rhs) const { return Polynomial(*this) += rhs; }
    Polynomial operator-(const Polynomial& rhs) const { return Polynomial(*this) -= rhs; }
    Polynomial operator*(const Polynomial& rhs) const { return Polynomial(*this) *= rhs; }
    Polynomial operator*(const Field& rhs) const { return Polynomial(*this) *= rhs; }
    Polynomial operator/(const Polynomial& rhs) const { return Polynomial(*this) /= rhs; }
    Polynomial operator/(const Field& rhs) const { return Polynomial(*this) /= rhs; }
    Polynomial operator%(const Polynomial& rhs) const { return Polynomial(*this) %= rhs; }
    
    private:
    std::map<Term, Field, Comp> terms;

    void clean_up() {
        std::map<Term, Field, Comp> tmp_terms;
        for(auto &i : terms) {
            if(!i.second.is_zero()) tmp_terms[i.first] = i.second;
        }
        terms = tmp_terms;
    }
    static Term merge_term(const Term &ls, const Term &rs) {
        auto liter = ls.cbegin(), riter = rs.cbegin();
        Term ret;
        while(liter != ls.cend() || riter != rs.cend()) {
            if(riter == rs.cend()) {
                ret += *liter;
                ++liter;
            } else if(liter == ls.cend()) {
                ret += *riter;
                ++riter;
            } else if(*liter < *riter) {
                ret += *liter;
                ++liter;
            } else {
                ret += *riter;
                ++riter;
            }
        }
        return ret;
    }

    template<class _T, class _Comp>
    friend bool operator==(const Polynomial<_T, _Comp> &lhs, const Polynomial<_T, _Comp> &rhs);
    template<class _T, class _Comp>
    friend bool operator!=(const Polynomial<_T, _Comp> &lhs, const Polynomial<_T, _Comp> &rhs);
    template<class _T, class _Comp>
    friend std::ostream& operator<<(std::ostream &os, const Polynomial<_T, _Comp> &x);
    template<class _T, class _Comp>
    friend bool can_div_poly(const Polynomial<_T, _Comp> &lhs, const Polynomial<_T, _Comp> &rhs);
};

template<class Field, class Comp>
std::ostream& operator<<(std::ostream &os, const Polynomial<Field, Comp> &x){
    os << "( ";
    for(const auto &i : x.terms) {
        os << i.first << " : " << i.second << ", ";
    }
    os << ")";
    return os;
}

template<class Field, class Comp>
bool operator==(const Polynomial<Field, Comp> &lhs, const Polynomial<Field, Comp> &rhs) {
    return lhs.terms == rhs.terms;
}
template<class Field, class Comp>
bool operator!=(const Polynomial<Field, Comp> &lhs, const Polynomial<Field, Comp> &rhs) {
    return !(lhs == rhs);
}

template<class Field, class Comp>
Polynomial<Field, Comp> S_poly(const Polynomial<Field, Comp> &x, const Polynomial<Field, Comp> &y) {
    Term g = gcd(x.LM(), y.LM());
    return x * Polynomial<Field, Comp>({{div_term(y.LM(), g), y.LC()}})
         - y * Polynomial<Field, Comp>({{div_term(x.LM(), g), x.LC()}});
}

template<class Field, class Comp>
bool can_div_poly(const Polynomial<Field, Comp> &x, const Polynomial<Field, Comp> &y) {
    assert(!y.is_zero());
    for(auto &t : x.terms) if(can_div_term(t.first, y.LM())) return true;
    return false;
}

} // namespace grobner

#endif