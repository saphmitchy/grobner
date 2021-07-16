# ifndef GROBNER_FIELD_FIELD_HPP
#define GROBNER_FIELD_FIELD_HPP 1

namespace grobner {

namespace field {

template<class SelfType>
class Field {
    public:
    virtual ~Field() {};
    virtual SelfType o () const = 0;
    virtual SelfType e () const = 0;
    virtual SelfType inv() const = 0;
    virtual bool is_zero() const = 0;
};

} // namespace field

} // namespace grobner

# endif