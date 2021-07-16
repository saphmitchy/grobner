#ifndef GREBNER_COMPARE_TERM_COMPARE_CPP
#define GREBNER_COMPARE_TERM_COMPARE_CPP 1

#include <string>

namespace grobner {

namespace compare {

class Lexicograph {
    public:
    bool operator()(const std::string &x, const std::string &y) const {
        auto xitr = x.cbegin();
        auto yitr = y.cbegin();
        while(1) {
            if(xitr == x.cend()) return false;
            else if(yitr == y.cend()) return true;
            else if(*xitr < *yitr) return true;
            else if(*xitr > *yitr) return false;
            ++xitr; ++yitr;
        }
    }
    using first_argument_type  = std::string;
    using second_argument_type = std::string;
    using result_type          = bool;
};

class GrLexicograph : public Lexicograph {
    public:
    bool operator()(const std::string &x, const std::string &y) const {
        if(x.size() == y.size()) { return Lexicograph::operator()(x, y); }
        else return x.size() > y.size();
    }
};
} // namespace compare

} // namespace grobner

#endif