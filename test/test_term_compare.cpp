#include <source/term_compare.hpp>
#define BOOST_TEST_MODULE test_term_compare
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_lexicograph) {
    typedef grobner::compare::Lexicograph Comp;
    BOOST_TEST(Comp()("abc", "a"));
    BOOST_TEST(Comp()("abc", "ac"));
    BOOST_TEST(Comp()("abcc", "abcd"));
    BOOST_TEST(!Comp()("abc", "aa"));
    BOOST_TEST(!Comp()("bc", "a"));
    BOOST_TEST(!Comp()("abc", "abc"));
    BOOST_TEST(!Comp()("a", "abc"));
}

BOOST_AUTO_TEST_CASE(test_grLexicograph) {
    typedef grobner::compare::GrLexicograph Comp;
    BOOST_TEST(Comp()("abc", "a"));
    BOOST_TEST(Comp()("abcc", "abcd"));
    BOOST_TEST(Comp()("abc", "aa"));
    BOOST_TEST(Comp()("bc", "a"));
    BOOST_TEST(!Comp()("ac", "abc"));
    BOOST_TEST(!Comp()("abc", "abc"));
    BOOST_TEST(!Comp()("a", "abc"));
    BOOST_TEST(!Comp()("abc", "abb"));
}