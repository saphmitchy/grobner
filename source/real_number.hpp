#ifndef GROBNER_FIELD_REAL_NUMBER_HPP
#define GROBNER_FIELD_REAL_NUMBER_HPP 1
#include <cassert>
#include <iostream>
#include "field.hpp"


namespace grobner {

namespace field {

class Real_number : public Field<Real_number> {
    // TODO
    // static_assert(Is_prime::is_prime);
    
    long double _val;
    public:
    static constexpr long double eps = 1e-10;
    ~Real_number() {}
    Real_number e() const { return Real_number(1.0); }
    Real_number o() const { return Real_number(0.0); }
    Real_number inv() const { 
        assert(_val != 0);
        return Real_number(1.0/_val);
    }
    bool is_zero() const { return std::abs(_val) < eps ; }
    Real_number operator-() const { return Real_number(-_val); }
    Real_number() : Real_number(0) {}
    Real_number(const double val_) : _val(val_) {}
    Real_number& operator+=(const Real_number& rhs) {
        _val += rhs._val;
        return *this;
    }
    Real_number& operator-=(const Real_number& rhs) {
        _val -= rhs._val;
        return *this;
    }
    Real_number& operator*=(const Real_number& rhs) {
        _val *= rhs._val;
        return *this;
    }
    Real_number& operator/=(const Real_number& rhs) {
        assert(!rhs.is_zero());
        _val /= rhs._val;
        return *this;
    }
    Real_number operator+(const Real_number& rhs) const { return Real_number(*this) += rhs; }
    Real_number operator-(const Real_number& rhs) const { return Real_number(*this) -= rhs; }
    Real_number operator*(const Real_number& rhs) const { return Real_number(*this) *= rhs; }
    Real_number operator/(const Real_number& rhs) const { return Real_number(*this) /= rhs; }
    double val() const { return _val; }
};

bool operator==(const Real_number &lhs, const Real_number &rhs) {
    return std::abs((lhs.val()-rhs.val())/lhs.val()) < Real_number::eps;
}
bool operator!=(const Real_number &lhs, const Real_number &rhs) {
    return !(lhs == rhs);
}
std::ostream& operator<<(std::ostream &os, const Real_number &x){
    os << x.val();
    return os;
}

} // namespace field

} // namespace grobner

#endif