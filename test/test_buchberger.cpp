#include <source/Polynomial.hpp>
#include <source/buchberger.hpp>
#include <source/real_number.hpp>
#include <source/residue_field.hpp>
#include <random>
#include <iostream>
#define BOOST_TEST_MODULE test_buchberger
#include <boost/test/included/unit_test.hpp>
using namespace grobner;

// using F5 = field::Real_number;
using F5 = field::Residue_Field<5>;
// using F5 = field::Residue_Field<2017>;
using Poly5 = Polynomial<F5>;

F5 f50(0);
F5 f51(1);
F5 f52(2);
F5 f53(3);
F5 f54(4);

BOOST_AUTO_TEST_CASE(test_reduction) {
    Poly5 f({{"xxxy", f51},
              {"xy" , f51}}),
          g1({{"xxx", f51},
              {"xxyy" , f54}}),
          g2({{"xy" , f51},
              {"yy" , f54}}),
          h1({{"yyyyy", f51},
              {"yy" , f51}}),
          h2({{"yyyy" , f51},
              {"yy" , f51}});
    std::vector<Poly5> g({g1, g2});
    BOOST_TEST(reduction(f, g) == h1);
    std::swap(g[0], g[1]);
    BOOST_TEST(reduction(f, g) == h2);
}
/*
BOOST_AUTO_TEST_CASE(test_buchberger_main1) {
    Poly5 f1({{"aabbbc", f51},
              {"abcc"  , f51},
              {"ab"    , f53},
              {"bcc"   , f52},
              {"d"     , f51},
              {""      , f54}}),
          f2({{"abccd" , f53},
              {"abcd"  , f52},
              {"ab"    , f51},
              {"bcd"   , f54},
              {"cd"    , f52},
              {"c"     , f54}}),
          f3({{"acdd"  , f51},
              {"ccc"   , f51},
              {"ac"    , f53},
              {"bdc"   , f52},
              {"dd"    , f54},
              {""      , f52}});
    std::vector<Poly5> f = {f1, f2, f3};
    auto g = buchberger_main(f);
    Poly5 g1({{"aaaaa", f51},
              {"aaaabbcc" , f54}}),
          g2({{"aaaacc" , f51},
              {"bcc" , f54}}),
          h1({{"aaaaabb", f51},
              {"abc" , f51}}),
          h2({{"aaaabbcc" , f51},
              {"" , f51}});
    std::vector<Poly5> h = {g1, g2, h1, h2}, tmp;
    std::default_random_engine engine(1234);
    for(int i = 0; i < 10; i++) {
        for(auto &p : f) {
            BOOST_TEST(reduction(p, g).is_zero());
        }
        std::shuffle(g.begin(), g.end(), engine);
    }
    for(int i = 0; i < 4; i++) tmp.push_back(reduction(h[i], g));
    for(int j = 0; j < 10; j++) {
        std::shuffle(g.begin(), g.end(), engine);
        for(int i = 0; i < 4; i++) {
            BOOST_TEST(reduction(h[i], g) == tmp[i]);
        }
    }
    for(auto &p : g) std::cout << p << std::endl;
}
*/

BOOST_AUTO_TEST_CASE(test_buchberger_main2) {
    Poly5 f1({{"xxx", f51},
              {"xy" , f54},
              {"yyy", f51}}),
          f2({{"xxx", f51},
              {"yy",  f54}});
    std::vector<Poly5> f = {f1, f2};
    auto g = buchberger_main(f);
    Poly5 g1({{"xxxyy", f51},
              {"xy" , f54}}),
          g2({{"yyyyyyyyyy" , f51},
              {"xxxxyyyy" , f54}}),
          h1({{"xxxxxxxxyyyyyy", f51},
              {"yy" , f51}}),
          h2({{"xxxyy" , f51},
              {"" , f51}});
    std::vector<Poly5> h = {g1, g2, h1, h2}, tmp;
    std::default_random_engine engine(1234);
    for(int i = 0; i < 10; i++) {
        for(auto &p : f) {
            BOOST_TEST(reduction(p, g).is_zero());
        }
        std::shuffle(g.begin(), g.end(), engine);
    }
    for(int i = 0; i < 4; i++) tmp.push_back(reduction(h[i], g));
    for(int j = 0; j < 10; j++) {
        std::shuffle(g.begin(), g.end(), engine);
        for(int i = 0; i < 4; i++) {
            BOOST_TEST(reduction(h[i], g) == tmp[i]);
        }
    }
    // for(auto &p : g) std::cout << p << std::endl;
}


BOOST_AUTO_TEST_CASE(test_buchberger1) {
    Poly5 f1({{"xxx", f51},
              {"xy" , f54},
              {"yyy", f51}}),
          f2({{"xxx", f51},
              {"yy",  f54}});
    std::vector<Poly5> f = {f1, f2};
    auto g = buchberger(f);
    Poly5 g1({{"xxxyy", f51},
              {"xy" , f54}}),
          g2({{"yyyyyyyyyy" , f51},
              {"xxxxyyyy" , f54}}),
          h1({{"xxxxxxxxyyyyyy", f51},
              {"yy" , f51}}),
          h2({{"xxxyy" , f51},
              {"" , f51}});
    std::vector<Poly5> h = {g1, g2, h1, h2}, tmp;
    std::default_random_engine engine(1234);
    for(int i = 0; i < 10; i++) {
        for(auto &p : f) {
            BOOST_TEST(reduction(p, g).is_zero());
        }
        std::shuffle(g.begin(), g.end(), engine);
    }
    for(int i = 0; i < 4; i++) tmp.push_back(reduction(h[i], g));
    for(int j = 0; j < 10; j++) {
        std::shuffle(g.begin(), g.end(), engine);
        for(int i = 0; i < 4; i++) {
            BOOST_TEST(reduction(h[i], g) == tmp[i]);
        }
    }
    // for(auto &p : g) std::cout << p << std::endl;
}

BOOST_AUTO_TEST_CASE(test_buchberger2) {
    Poly5 f1({{"xx", f51},
              {"yy", f51},
              {"zz", f51},
              {"",   f54}}),
          f2({{"xy", f51},
              {"z",  f54},
              {"",   f52}}),
          f3({{"zz", f51},
              {"x",  f53},
              {"y",  f53}});
    std::vector<Poly5> f = {f1, f2, f3};
    auto g = buchberger(f);
    // for(auto &p : g) std::cout << p << std::endl;
    Poly5 g1({{"xxxyy", f51},
              {"xy" , f54}}),
          g2({{"yyyyyyyyyy" , f51},
              {"zz" , f51},
              {"xxxxyyyy" , f54}}),
          h1({{"xxyyyzz", f51},
              {"yy" , f51}}),
          h2({{"xyyz" , f51},
              {"" , f51}});
    std::vector<Poly5> h = {g1, g2, h1, h2}, tmp;
    std::default_random_engine engine(1234);
    for(int i = 0; i < 10; i++) {
        for(auto &p : f) {
            auto rd = reduction(p, g);
            BOOST_TEST(rd.is_zero());
        }
        std::shuffle(g.begin(), g.end(), engine);
    }
    for(int i = 0; i < 4; i++) tmp.push_back(reduction(h[i], g));
    for(int j = 0; j < 10; j++) {
        std::shuffle(g.begin(), g.end(), engine);
        for(int i = 0; i < 4; i++) {
            BOOST_TEST(reduction(h[i], g) == tmp[i]);
        }
    }
}

BOOST_AUTO_TEST_CASE(test_buchberger3) {
    Poly5 f1({{"xx", f51},
              {"yy", f51},
              {"zz", f51},
              {"",   f54}}),
          f2({{"xy", f51},
              {"z",  f54},
              {"",   f52}}),
          f3({{"zz", f51},
              {"x",  f53},
              {"y",  f53}});
    std::vector<Poly5> f = {f1, f2, f3};
    auto g = buchberger(f);
    Poly5 g1({{"xxxyy", f51},
              {"xy" , f54}}),
          g2({{"yyyyyyyyyy", f51},
              {"zz" , f51},
              {"xxxxyyyy" , f54}}),
          h1({{"xxyyyzz", f51},
              {"yy" , f51}}),
          h2({{"xyyz" , f51},
              {"" , f51}});
    std::vector<Poly5> h = {g1, g2, h1, h2}, tmp;
    std::default_random_engine engine(1234);
    for(int i = 0; i < 10; i++) {
        for(auto &p : f) {
            auto rd = reduction(p, g);
            BOOST_TEST(rd.is_zero());
        }
        std::shuffle(g.begin(), g.end(), engine);
    }
    for(int i = 0; i < 4; i++) tmp.push_back(reduction(h[i], g));
    for(int j = 0; j < 10; j++) {
        std::shuffle(g.begin(), g.end(), engine);
        for(int i = 0; i < 4; i++) {
            auto rd = reduction(h[i], g);
            BOOST_TEST(rd == tmp[i]);
        }
    }
    // std::cout << "ans=\n";
    // for(auto &p : g) std::cout << p << std::endl;
}