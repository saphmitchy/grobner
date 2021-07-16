#include <source/Polynomial.hpp>
#include <source/residue_field.hpp>
#include <vector>
#include <iostream>
#define BOOST_TEST_MODULE test_poly
#include <boost/test/included/unit_test.hpp>

using namespace grobner;

using F5 = field::Residue_Field<5>;
using Unary5 = Polynomial<F5>::Unary;

BOOST_AUTO_TEST_CASE(test_constract) {
    Polynomial<F5> x;
    BOOST_TEST(x.val().empty());
    std::vector<Unary5> y({{"xx", F5(2)},
                           {"xy", F5(3)},
                           {"yyy", F5(0)},
                           {"yzy", F5(4)},
                           {"", F5(4)},
                           {"xz", F5(1)}});
    std::vector<Unary5> z({{"xx", F5(2)},
                           {"xy", F5(3)},
                           {"xz", F5(1)},
                           {"yyz", F5(4)},
                           {"", F5(4)}});
    auto y_tmp = Polynomial<F5>(y);
    BOOST_TEST(y_tmp.val() == z);
    Polynomial<F5> w(F5(4));
    BOOST_TEST(w.val() == std::vector<Unary5>({{"", F5(4)}}));
    Polynomial<F5> u("xyz");
    BOOST_TEST(u.val() == std::vector<Unary5>({{"xyz", F5(1)}}));
}

BOOST_AUTO_TEST_CASE(test_o) {
    std::vector<Unary5> y({{"xx", F5(2)},
                           {"xy", F5(3)},
                           {"yyy", F5(0)},
                           {"yzy", F5(4)},
                           {"", F5(4)},
                           {"xz", F5(1)}});
    Polynomial<F5> x, z(y);
    BOOST_TEST(x.o().val().empty());
    BOOST_TEST(z.o().val().empty());
}

BOOST_AUTO_TEST_CASE(test_e) {
    std::vector<Unary5> y({{"xx", F5(2)},
                           {"xy", F5(3)},
                           {"yyy", F5(0)},
                           {"yzy", F5(4)},
                           {"", F5(4)},
                           {"xz", F5(1)}});
    Polynomial<F5> x, z(y);
    std::vector<Unary5> ans = {{"", F5(1)}};
    BOOST_TEST(x.e().val() == ans);
    BOOST_TEST(z.e().val() == ans);
}

BOOST_AUTO_TEST_CASE(test_LT) {
    std::vector<Unary5> xv({{"xx", F5(2)},
                           {"xy", F5(3)},
                           {"yyy", F5(0)},
                           {"yzy", F5(4)},
                           {"", F5(4)},
                           {"xz", F5(1)}});
    std::vector<Unary5> yv({{"abc", F5(2)},
                           {"cb", F5(3)},
                           {"abb", F5(1)},
                           {"cc", F5(4)},
                           {"aaaac", F5(0)},
                           {"c", F5(1)}});
    Polynomial<F5> x(xv), y(yv);
    std::vector<Unary5> ansx = {{"xx", F5(2)}},
                        ansy = {{"abb", F5(1)}};
    BOOST_TEST(x.LT().val() == ansx);
    BOOST_TEST(y.LT().val() == ansy);
}

BOOST_AUTO_TEST_CASE(test_LC) {
    std::vector<Unary5> xv({{"xx", F5(2)},
                           {"xyy", F5(3)},
                           {"xxy", F5(0)},
                           {"yzy", F5(4)},
                           {"", F5(4)},
                           {"xz", F5(1)}});
    std::vector<Unary5> yv({{"abc", F5(2)},
                           {"cb", F5(3)},
                           {"abb", F5(1)},
                           {"cc", F5(0)},
                           {"ac", F5(4)},
                           {"c", F5(2)}});
    Polynomial<F5> x(xv), y(yv);
    BOOST_TEST(x.LC().val() == 2);
    BOOST_TEST(y.LC().val() == 1);
}

BOOST_AUTO_TEST_CASE(test_LM) {
    std::vector<Unary5> xv({{"xx", F5(2)},
                           {"xay", F5(3)},
                           {"zyyyzz", F5(0)},
                           {"yzyz", F5(4)},
                           {"z", F5(4)},
                           {"xz", F5(1)}});
    std::vector<Unary5> yv({{"abc", F5(2)},
                           {"cb", F5(3)},
                           {"abb", F5(1)},
                           {"ccc", F5(0)},
                           {"dc", F5(4)},
                           {"c", F5(2)}});
    Polynomial<F5> x(xv), y(yv);
    BOOST_TEST(x.LM() == "axy");
    BOOST_TEST(y.LM() == "abb");
}

BOOST_AUTO_TEST_CASE(test_Eq) {
    std::vector<Unary5> xv({{"xx", F5(2)},
                           {"xay", F5(3)},
                           {"zyyyzz", F5(0)},
                           {"yzyz", F5(4)},
                           {"z", F5(4)},
                           {"xz", F5(1)}});
    std::vector<Unary5> yv({{"zx", F5(1)},
                           {"zzyy", F5(4)},
                           {"z", F5(4)},
                           {"yxa", F5(3)},
                           {"xx", F5(2)}});
    std::vector<Unary5> zv({{"zx", F5(1)},
                           {"zzyy", F5(4)},
                           {"z", F5(4)},
                           {"yxa", F5(2)},
                           {"ayz", F5(0)},
                           {"xx", F5(2)}});
    std::vector<Unary5> wv({{"zx", F5(1)},
                           {"zzyy", F5(4)},
                           {"z", F5(4)},
                           {"yxa", F5(3)},
                           {"ayz", F5(1)},
                           {"xx", F5(2)}});
    Polynomial<F5> x(xv), y(yv), z(zv), w(wv);
    BOOST_TEST(x == y);
    BOOST_TEST(x != z);
    BOOST_TEST(!(x != y));
    BOOST_TEST(y != w);
}

BOOST_AUTO_TEST_CASE(test_uniMinus) {
    std::vector<Unary5> xv({{"xx", F5(2)},
                           {"xay", F5(3)},
                           {"zyyyzz", F5(0)},
                           {"yzyz", F5(4)},
                           {"z", F5(4)},
                           {"xz", F5(1)}});
    std::vector<Unary5> yv({{"zx", F5(4)},
                           {"zzyy", F5(1)},
                           {"z", F5(1)},
                           {"yxa", F5(2)},
                           {"xx", F5(3)}});
    Polynomial<F5> x(xv), y(yv);
    BOOST_TEST(x == -y);
}

BOOST_AUTO_TEST_CASE(test_plus) {
    std::vector<Unary5> xv({{"xx", F5(4)},
                            {"xy", F5(1)},
                            {"x" , F5(1)},
                            {"y" , F5(2)},
                            {"x" , F5(2)},
                            {""  , F5(3)}});
    std::vector<Unary5> yv({{"xx", F5(1)},
                            {"xy", F5(2)},
                            {"x" , F5(3)},
                            {"y" , F5(4)},
                            {"x" , F5(0)},
                            {""  , F5(1)}});
    std::vector<Unary5> zv({{"xx", F5(0)},
                            {"xy", F5(3)},
                            {"x" , F5(4)},
                            {"y" , F5(1)},
                            {"x" , F5(2)},
                            {""  , F5(4)}});
    std::vector<Unary5> wv({{"xx", F5(1)},
                            {"xy", F5(0)},
                            {"x" , F5(2)},
                            {"y" , F5(0)},
                            {"x" , F5(2)},
                            {""  , F5(0)}});
    Polynomial<F5> x(xv), y(yv), z(zv), w(wv);
    BOOST_TEST(x+y == z);
    z += y;
    BOOST_TEST(w == z);
}

BOOST_AUTO_TEST_CASE(test_minus) {
    std::vector<Unary5> xv({{"xx", F5(4)},
                            {"xy", F5(1)},
                            {"x" , F5(1)},
                            {"y" , F5(2)},
                            {"x" , F5(2)},
                            {""  , F5(3)}});
    std::vector<Unary5> yv({{"xx", F5(1)},
                            {"xy", F5(2)},
                            {"x" , F5(3)},
                            {"y" , F5(4)},
                            {"x" , F5(0)},
                            {""  , F5(1)}});
    std::vector<Unary5> zv({{"xx", F5(0)},
                            {"xy", F5(3)},
                            {"x" , F5(4)},
                            {"y" , F5(1)},
                            {"x" , F5(2)},
                            {""  , F5(4)}});
    std::vector<Unary5> wv({{"xx", F5(1)},
                            {"xy", F5(0)},
                            {"x" , F5(2)},
                            {"y" , F5(0)},
                            {"x" , F5(2)},
                            {""  , F5(0)}});
    Polynomial<F5> x(xv), y(yv), z(zv), w(wv);
    BOOST_TEST(x == z-y);
    w -= y;
    BOOST_TEST(w == z);
}

BOOST_AUTO_TEST_CASE(test_prod_poly1) {
    std::vector<Unary5> xv({{"x" , F5(3)},
                            {"y" , F5(2)}});
    std::vector<Unary5> yv({{"y" , F5(3)},
                            {"z" , F5(2)}});
    std::vector<Unary5> zv({{"z" , F5(3)},
                            {"x" , F5(2)}});
    std::vector<Unary5> wv({{"xxy" , F5(3)},
                            {"xxz" , F5(2)},
                            {"yyz" , F5(3)},
                            {"yyx" , F5(2)},
                            {"xzz" , F5(3)},
                            {"yzz" , F5(2)}});
    Polynomial<F5> x(xv), y(yv), z(zv), w(wv);
    BOOST_TEST(w == x*y*z);
}

BOOST_AUTO_TEST_CASE(test_prod_poly2) {
    std::vector<Unary5> xv({{"xxxyz" , F5(3)},
                            {"yyzzz" , F5(3)}});
    std::vector<Unary5> yv({{"xxxxxy" , F5(1)},
                            {"xxyyzz" , F5(4)}});
    std::vector<Unary5> zv({{"xxxxxxxxyyz" , F5(3)},
                            {"xxyyyyzzzzz" , F5(2)}});
    std::vector<Unary5> wv({{"xxyzz" , F5(2)},
                            {"" , F5(4)}});
    std::vector<Unary5> uv({{"xxxxxxxxyyz" , F5(2)},
                            {"xxyyyyzzzzz" , F5(3)},
                            {"xxxxxxxxxxyyyzzz" , F5(1)},
                            {"xxxxyyyyyzzzzzzz" , F5(4)}});
    Polynomial<F5> x(xv), y(yv), z(zv), w(wv), u(uv);
    x *= y;
    BOOST_TEST(x == z);
    BOOST_TEST(x*w == u);
}

BOOST_AUTO_TEST_CASE(test_prod_field) {
    std::vector<Unary5> xv({{"xx", F5(4)},
                            {"xy", F5(1)},
                            {"x" , F5(1)},
                            {"y" , F5(2)},
                            {"x" , F5(2)},
                            {""  , F5(3)}});
    std::vector<Unary5> yv({{"xx", F5(1)},
                            {"xy", F5(4)},
                            {"x" , F5(4)},
                            {"y" , F5(3)},
                            {"x" , F5(3)},
                            {""  , F5(2)}});
    Polynomial<F5> x(xv), y(yv);
    F5 z(4), w(0);
    BOOST_TEST(x*z == y);
    x *= z;
    BOOST_TEST(x == y);
    BOOST_TEST(x*w == Polynomial<F5>());
}

BOOST_AUTO_TEST_CASE(test_division1) {
    std::vector<Unary5> xv({{"xxxxy", F5(2)},
                            {"xxyyy", F5(2)},
                            {"xxy"  , F5(1)},
                            {"xy"   , F5(3)},
                            {"x"    , F5(1)},
                            {"yyyyy", F5(3)},
                            {"yyy"  , F5(2)},
                            {"y"    , F5(3)},
                            {""     , F5(1)}});
    std::vector<Unary5> yv({{"xx"   , F5(2)},
                            {"yy"   , F5(1)},
                            {"x"    , F5(1)},
                            {""     , F5(4)}});
    std::vector<Unary5> zv({{"xxy"  , F5(1)},
                            {"yyy"  , F5(3)},
                            {"xy"   , F5(2)}});
    std::vector<Unary5> wv({{"x"    , F5(1)},
                            {"y"    , F5(3)},
                            {""     , F5(1)}});
    Polynomial<F5> x(xv), y(yv), z(zv), w(wv);
    auto tmp = x.division(y);
    BOOST_TEST(tmp.first == z);
    BOOST_TEST(tmp.second == w);
    BOOST_TEST(x/y == z);
    BOOST_TEST(x%y == w);
}

BOOST_AUTO_TEST_CASE(test_division2) {
    std::vector<Unary5> xv({{"aabc", F5(2)},
                            {"aabd", F5(2)},
                            {"aab" , F5(3)},
                            {"abbc", F5(3)},
                            {"abbd", F5(1)},
                            {"abb" , F5(1)},
                            {"abcc", F5(1)},
                            {"abd" , F5(1)},
                            {"ab"  , F5(2)},
                            {"accd", F5(3)},
                            {"acdd", F5(3)},
                            {"ac"  , F5(3)},
                            {"add" , F5(3)},
                            {"bbbc", F5(1)},
                            {"bbb" , F5(1)},
                            {"bbcc", F5(3)},
                            {"bbd" , F5(3)},
                            {"bb"  , F5(1)},
                            {"bccd", F5(3)},
                            {"bcd" , F5(1)},
                            {"bc"  , F5(3)},
                            {"bd"  , F5(3)},
                            {"b"   , F5(2)},
                            {"cccd", F5(4)},
                            {"ccd" , F5(4)},
                            {"cc"  , F5(4)},
                            {"cd"  , F5(3)},
                            {"dd"  , F5(4)},
                            {"d"   , F5(2)}});
    std::vector<Unary5> yv({{"ab"  , F5(2)},
                            {"bb"  , F5(1)},
                            {"cd"  , F5(3)},
                            {"d"   , F5(3)},
                            {""    , F5(3)}});
    std::vector<Unary5> zv({{"a"   , F5(4)},
                            {"b"   , F5(1)},
                            {"d"   , F5(3)},
                            {"bc"  , F5(1)},
                            {"ad"  , F5(1)},
                            {"cc"  , F5(3)},
                            {"ac"  , F5(1)},
                            {""    , F5(1)}});
    std::vector<Unary5> wv({{"cdd" , F5(1)},
                            {"a"   , F5(3)},
                            {"b"   , F5(4)},
                            {""    , F5(2)}});
    Polynomial<F5> x(xv), y(yv), z(zv), w(wv);
    auto tmp = x.division(y);
    BOOST_TEST(tmp.first == z);
    BOOST_TEST(tmp.second == w);
    BOOST_TEST(x/y == z);
    BOOST_TEST(x%y == w);
}

BOOST_AUTO_TEST_CASE(test_division3) {
    std::vector<Unary5> xv({{"xxxx", F5(1)},
                            {"xxx" , F5(4)},
                            {"xxyy", F5(1)},
                            {"xxy" , F5(4)},
                            {"xx"  , F5(3)},
                            {"xy"  , F5(1)},
                            {"x"   , F5(3)},
                            {"yy"  , F5(1)},
                            {"y"   , F5(3)},
                            {""    , F5(2)}});
    std::vector<Unary5> yv({{"xx"  , F5(1)},
                            {"y"   , F5(1)},
                            {"xy"  , F5(3)},
                            {""    , F5(2)}});
    std::vector<Unary5> zv({{"xx"  , F5(1)},
                            {"xy"  , F5(2)},
                            {"y"   , F5(1)},
                            {"x"   , F5(4)},
                            {""    , F5(1)}});
    Polynomial<F5> x(xv), y(yv), z(zv);
    auto tmp = x.division(y);
    BOOST_TEST(tmp.first == z);
    BOOST_TEST(tmp.second.is_zero());
    BOOST_TEST(x/y == z);
    BOOST_TEST(x%y == Polynomial<F5>());
}

BOOST_AUTO_TEST_CASE(test_is_zero) {
    std::vector<Unary5> wv({{"z" , F5(3)},
                            {"" , F5(2)}});
    std::vector<Unary5> uv({{"xxy" , F5(3)},
                            {"xxz" , F5(2)},
                            {"yyz" , F5(3)},
                            {"yyx" , F5(2)},
                            {"xzz" , F5(3)},
                            {"yzz" , F5(2)}});
    
    Polynomial<F5> x, y("y"), z(F5(1)), w(wv), u(uv);
    BOOST_TEST(x.is_zero());
    BOOST_TEST(!y.is_zero());
    BOOST_TEST(!z.is_zero());
    BOOST_TEST(!w.is_zero());
    BOOST_TEST(!u.is_zero());
}

BOOST_AUTO_TEST_CASE(test_can_div_term) {
    BOOST_TEST(Polynomial<F5>::can_div_term("xy", "y"));
    BOOST_TEST(Polynomial<F5>::can_div_term("xyz", "xyz"));
    BOOST_TEST(Polynomial<F5>::can_div_term("xxx", "x"));
    BOOST_TEST(Polynomial<F5>::can_div_term("xyyz", "z"));
    BOOST_TEST(!Polynomial<F5>::can_div_term("xyyz", "zz"));
    BOOST_TEST(!Polynomial<F5>::can_div_term("xyyz", "xyzz"));
    BOOST_TEST(!Polynomial<F5>::can_div_term("z", "zz"));
    BOOST_TEST(!Polynomial<F5>::can_div_term("xy", "z"));
}

BOOST_AUTO_TEST_CASE(test_div_term) {
    BOOST_TEST(Polynomial<F5>::div_term("xy", "y") == "x");
    BOOST_TEST(Polynomial<F5>::div_term("xyz", "xyz") == "");
    BOOST_TEST(Polynomial<F5>::div_term("xxx", "x") == "xx");
    BOOST_TEST(Polynomial<F5>::div_term("xyyz", "z") == "xyy");
    BOOST_TEST(Polynomial<F5>::div_term("xyyz", "xy") == "yz");
}

BOOST_AUTO_TEST_CASE(test_div_Field) {
    std::vector<Unary5> xv({{"xx", F5(4)},
                            {"xy", F5(1)},
                            {"x" , F5(1)},
                            {"y" , F5(2)},
                            {"x" , F5(2)},
                            {""  , F5(3)}});
    std::vector<Unary5> yv({{"xx", F5(1)},
                            {"xy", F5(4)},
                            {"x" , F5(4)},
                            {"y" , F5(3)},
                            {"x" , F5(3)},
                            {""  , F5(2)}});
    std::vector<Unary5> uv({{"xx", F5(3)},
                            {"xy", F5(2)},
                            {"x" , F5(2)},
                            {"y" , F5(4)},
                            {"x" , F5(4)},
                            {""  , F5(1)}});
    Polynomial<F5> x(xv), y(yv), u(uv);
    F5 z(4), w(3);
    BOOST_TEST(x/z == y);
    BOOST_TEST(x/w == u);
    x /= z;
    BOOST_TEST(x == y);
}
