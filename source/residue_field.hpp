#ifndef GROBNER_FIELD_RESIDUE_FIELD_HPP
#define GROBNER_FIELD_RESIDUE_FIELD_HPP 1

#include <cassert>
#include <iostream>
#include "field.hpp"

namespace grobner {

namespace field {

/**
 * @brief define class of residue field. 
 * 
 * @tparam P modulo. must be prime number
 */
template<int P>
class Residue_Field : public Field<Residue_Field<P>> {
    // TODO
    // static_assert(Is_prime<P>::is_prime);
    
    int _val;
    public:
    ~Residue_Field() {}
    static int** plus_list;
    static int* minus_list;
    static int** prod_list;
    static int* div_list;
    Residue_Field e() const { return Residue_Field(1); }
    Residue_Field o() const { return Residue_Field(0); }
    Residue_Field inv() const { 
        assert(_val > 0);
        return Residue_Field(div_list[_val]);
    }
    bool is_zero() const { return _val == 0; }
    Residue_Field operator-() const { return Residue_Field(minus_list[_val]); }
    Residue_Field() : Residue_Field(0) {}
    Residue_Field(const int val_) : _val(val_) {
        assert(0 <= _val && _val < P);
    }
    Residue_Field& operator+=(const Residue_Field& rhs) {
        _val = plus_list[_val][rhs._val];
        return *this;
    }
    Residue_Field& operator-=(const Residue_Field& rhs) {
        _val = plus_list[_val][minus_list[rhs._val]];
        return *this;
    }
    Residue_Field& operator*=(const Residue_Field& rhs) {
        _val = prod_list[_val][rhs._val];
        return *this;
    }
    Residue_Field& operator/=(const Residue_Field& rhs) {
        assert(rhs._val > 0);
        _val = prod_list[_val][div_list[rhs._val]];
        return *this;
    }
    Residue_Field operator+(const Residue_Field& rhs) const { return Residue_Field(*this) += rhs; }
    Residue_Field operator-(const Residue_Field& rhs) const { return Residue_Field(*this) -= rhs; }
    Residue_Field operator*(const Residue_Field& rhs) const { return Residue_Field(*this) *= rhs; }
    Residue_Field operator/(const Residue_Field& rhs) const { return Residue_Field(*this) /= rhs; }
    int val() const { return _val; }
};

template<int P>
bool operator==(const Residue_Field<P> &lhs, const Residue_Field<P> &rhs) {
    return lhs.val() == rhs.val();
}
template<int P>
bool operator!=(const Residue_Field<P> &lhs, const Residue_Field<P> &rhs) {
    return !(lhs == rhs);
}
template<int P>
std::ostream& operator<<(std::ostream &os, const Residue_Field<P> &x){
    os << x.val();
    return os;
}

/**
 * @brief calculate n^k mod P. n^k is k raised to the power of n.
 * 
 * @tparam P modulo
 * @param n power index
 * @param b base
 * @return int 
 */
template<int P>
constexpr int modpow(int n, int b) {
    if(b == 0) return 1;
    else if(b&1) return (long long) modpow<P>(n, b-1) * n % P;
    long long ret = modpow<P>(n, b/2);
    return ret * ret % P;
}

/**
 * @brief make two dimensional array storing the result of addtion
 * 
 * @tparam P modulo
 * @return constexpr int** 
 */
template<int P>
constexpr int** make_plus_list() {
    int** ret= new int*[P];
    for(int i = 0; i < P; i++) ret[i] = new int[P];
    for(int i = 0; i < P; i++) {
        for(int j = 0; j < P; j++) {
            ret[i][j] = (long long) (i + j) % P;
            // assert(i + j == ret[i][j] || i+j == ret[i][j]-P);
            // assert(ret[i][j] >= 0);
            // assert(ret[i][j] < P);
        }
    }
    return ret;
}

/**
 * @brief make two dimensional array storing the inverse element of addition
 * 
 * @tparam P modulo
 * @return constexpr int* 
 */
template<int P>
constexpr int* make_minus_list() {
    int* ret = new int[P];
    for(int i = 0; i < P; i++) {
        ret[i] = i == 0 ? 0 : P - i;
    }
    return ret;
}

/**
 * @brief make two dimensional array storing the result of product
 * 
 * @tparam P modulo
 * @return constexpr int** 
 */
template<int P>
constexpr int** make_prod_list() {
    int** ret = new int*[P];
    for(int i = 0; i < P; i++) ret[i] = new int[P];
    for(int i = 0; i < P; i++) {
        for(int j = 0; j < P; j++) {
            ret[i][j] = (long long) i * j % P;
        }
    }
    return ret;
}

/**
 * @brief make two dimensional array storing the inverse element of product
 * 
 * @tparam P modulo
 * @return constexpr int* 
 */
template<int P>
constexpr int* make_div_list() {
    int* ret = new int[P];
    for(int i = 0; i < P; i++) {
        // calculate inverse element of product by using Fermat's little Theorem; N^(P-1) = 1 mod P
        ret[i] = modpow<P>(i, P-2);
    }
    return ret;
}

template<int P>
int** Residue_Field<P>::plus_list = make_plus_list<P>();
template<int P>
int* Residue_Field<P>::minus_list = make_minus_list<P>();
template<int P>
int** Residue_Field<P>::prod_list = make_prod_list<P>();
template<int P>
int* Residue_Field<P>::div_list = make_div_list<P>();

} // namespace field

} // namespace grobner

#endif