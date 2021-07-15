#include <source/residue_field.hpp>
#define BOOST_TEST_MODULE test_resideue_field
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_add) {
    grobner::field::Residue_Field<5> x(1), y(2);
    auto z = x + y;
    BOOST_TEST(x.val() == 1);
    BOOST_TEST(y.val() == 2);
    BOOST_TEST(z.val() == 3);
    x = z + y;
    BOOST_TEST(x.val() == 0);
    BOOST_TEST(y.val() == 2);
    BOOST_TEST(z.val() == 3);
    y = x + z;
    BOOST_TEST(y.val() == 3);
    z = x + y;
    BOOST_TEST(z.val() == 3);
    x += y + z + y;
    BOOST_TEST(x.val() == 4);
}

BOOST_AUTO_TEST_CASE(test_minus) {
    grobner::field::Residue_Field<5> x(1), y(2);
    auto z = x - y;
    BOOST_TEST(x.val() == 1);
    BOOST_TEST(y.val() == 2);
    BOOST_TEST(z.val() == 4);
    x = y - z;
    BOOST_TEST(x.val() == 3);
    BOOST_TEST(y.val() == 2);
    BOOST_TEST(z.val() == 4);
    y = z - x;
    BOOST_TEST(y.val() == 1);
    z = x - y;
    BOOST_TEST(z.val() == 2);
    x = x - y - z;
    BOOST_TEST(x.val() == 0);
}

BOOST_AUTO_TEST_CASE(test_prod) {
    grobner::field::Residue_Field<5> x(1), y(2), w(0);
    auto z = x * y;
    BOOST_TEST(x.val() == 1);
    BOOST_TEST(y.val() == 2);
    BOOST_TEST(z.val() == 2);
    x = z * y;
    BOOST_TEST(x.val() == 4);
    BOOST_TEST(y.val() == 2);
    BOOST_TEST(z.val() == 2);
    y = z * x;
    BOOST_TEST(y.val() == 3);
    z *= x;
    BOOST_TEST(z.val() == 3);
    z = w * y;
    BOOST_TEST(z.val() == 0);
    x *= w;
    BOOST_TEST(x.val() == 0);
}

BOOST_AUTO_TEST_CASE(test_div) {
    grobner::field::Residue_Field<5> x(1), y(2), w(0);
    auto z = x / y;
    BOOST_TEST(x.val() == 1);
    BOOST_TEST(y.val() == 2);
    BOOST_TEST(z.val() == 3);
    z /= y;
    BOOST_TEST(y.val() == 2);
    BOOST_TEST(z.val() == 4);
    y = z / x;
    BOOST_TEST(y.val() == 4);
    y = w / x;
    BOOST_TEST(y.val() == 0);
}

BOOST_AUTO_TEST_CASE(test_e) {
    grobner::field::Residue_Field<5> x(3);
    grobner::field::Residue_Field<13> y(3);
    grobner::field::Residue_Field<101> z(3);
    BOOST_TEST(x.e().val() == 1);
    BOOST_TEST(y.e().val() == 1);
    BOOST_TEST(z.e().val() == 1);
}

BOOST_AUTO_TEST_CASE(test_o) {
    grobner::field::Residue_Field<5> x(3);
    grobner::field::Residue_Field<13> y(3);
    grobner::field::Residue_Field<101> z(3);
    BOOST_TEST(x.o().val() == 0);
    BOOST_TEST(y.o().val() == 0);
    BOOST_TEST(z.o().val() == 0);
}

BOOST_AUTO_TEST_CASE(test_inv) {
    grobner::field::Residue_Field<5> x(3);
    grobner::field::Residue_Field<13> y(3);
    grobner::field::Residue_Field<101> z(3);
    BOOST_TEST(x.inv().val() == 2);
    BOOST_TEST(y.inv().val() == 9);
    BOOST_TEST(z.inv().val() == 34);
}

BOOST_AUTO_TEST_CASE(test_eq) {
    grobner::field::Residue_Field<5> x(3);
    grobner::field::Residue_Field<5> y(3);
    grobner::field::Residue_Field<5> z(4);
    BOOST_TEST(x == y);
    BOOST_TEST(x != z);
    BOOST_TEST(!(x != y));
    BOOST_TEST(!(x == z));
}