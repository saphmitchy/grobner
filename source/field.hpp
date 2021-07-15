namespace grobner {

namespace field {

template<class SelfType>
class Field {
    public:
    virtual ~Field() {};
    virtual SelfType o () const = 0;
    virtual SelfType e () const = 0;
    virtual SelfType inv() const = 0;
};

} // namespace field

} // namespace grobner