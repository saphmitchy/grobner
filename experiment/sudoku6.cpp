#include <source/term_compare.hpp>
#include <source/Polynomial.hpp>
#include <source/buchberger.hpp>
#include <source/residue_field.hpp>
#include <vector>
#include <string>
#include <iostream>

using namespace grobner;

const int N = 6;
const int H = 2;
const int W = 3;
static_assert(N == H*W);

const char TERMS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
using FG = field::Residue_Field<N+1>;
using Poly = Polynomial<FG>;

Poly is_different(char x, char y) {
    std::vector<std::pair<Term, FG>> tmp(N+1);
    for(int i = 0; i < N+1; i++) {
        Term term;
        for(int j = 0; j < i; j++) term += x;
        for(int j = 0; j < N-i; j++) term += y;
        tmp[i] = {term, FG(1)};
    }
    tmp.push_back({"", -FG(1)});
    return Poly(tmp);
}

Poly is_nonzero(char x) {
    Term tmp;
    for(int i = 0; i < N; i++) {
        tmp += x;
    }
    return Poly({{tmp, FG(1)}});
}

Poly is_n(char x,int n) {
    Term tmp;
    tmp += x;
    return Poly({{tmp, -FG(n)}});
}

char to_char(int x, int y) { return TERMS[x*N+y]; }

int main() {
    std::vector<std::vector<int>> sudoku = {{0, 0, 3, 0, 1, 0},
                                            {0, 0, 0, 6, 0, 2},
                                            {1, 0, 0, 0, 4, 0},
                                            {0, 4, 0, 0, 0, 1},
                                            {3, 0, 5, 0, 0, 0},
                                            {0, 1, 0, 2, 0, 0}};
    std::vector<Poly> polys;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            for(int k = 0; k < j; k++) {
                polys.push_back(is_different(to_char(i, j), to_char(i, k)));
                polys.push_back(is_different(to_char(j, i), to_char(k, i)));
            }
        }
    }
    for(int i = 0; i < N/H; i++) {
        for(int j = 0; j < N/W; j++) {
            std::vector<char> tmp;
            for(int ii = 0; ii < H; ii++) {
                for(int jj = 0; jj < W; jj++) {
                    tmp.push_back(to_char(i*H+ii, j*W+jj));
                }
            }
            for(int ii = 0; ii < N; ii++) {
                for(int jj = 0; jj < ii; jj++) {
                    polys.push_back(is_different(tmp[ii], tmp[jj]));
                }
            }
        }
    }
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(sudoku[i][j] == 0) polys.push_back(is_nonzero(to_char(i, j)));
            else polys.push_back(is_n(to_char(i, j), sudoku[i][j]));
        }
    }
    for(auto &p : polys) {
        std::cout << p << std::endl;
    }
    std::cout << "ans=\n";
    auto g = buchberger(polys);
    for(auto &p : g) {
        std::cout << p << std::endl;
    }
}