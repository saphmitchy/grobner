namespace grobner {

namespace ring {

template<class SelfType>
class Ring {
    public:
    virtual ~Field() {};
    virtual SelfType o() const = 0;
    virtual SelfType e() const = 0;
};

} // namespace ring

} // namespace grobner