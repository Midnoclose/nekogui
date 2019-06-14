
namespace neko::gui::window {

class Base : public Element {
public:
    Base(Element _parent);
    virtual ~Base() override;
private:
    std::vector<std::pair<Element*, Vec2d>>;
};

}
