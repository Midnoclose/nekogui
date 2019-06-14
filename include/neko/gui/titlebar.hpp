
#include "button.hpp"

class TitleBar : public Element {
public:
    TitleBar(ActingWindow* _parent, const std::string* _display_text, bool _close_button)
        : Element(_parent), display_text(_display_text) {
        if (_close_button)
            close_button = new Button(this, "X", [this](){
                delete this->parent;
            });
    }
    virtual ~TitleBar(){
        if (this->close_button)
            delete this->close_button;
    }
private:
    Vec2d size = {0, 0};
    Vec2d text_offset = {0,0};
public:
    virtual void Draw(Vec2d abs) const {
        Vec2d size = this->GetSize();
        draw::Line({abs.first, abs.second + size.second - 1}, {size.first, 0}, GetOutlineColor());
        draw::String(this->display_text, abs + this->text_offset);
        // Button
        if (this->close_button)
            this->close_button->Draw();
    }
    virtual void MouseEvent(const Vec2d& mouse_pos, const Vec2d& move_delta) {
        this->parent->SetOffset(this->parent->GetOffset() + move_delta);
    }
    virtual Vec2d GetOffset() const { return this->offset; }; // Where is it located in relation to the parent
    virtual void SetOffset(const Vec2d& value) { this->offset = value; }
    virtual Vec2d GetSize() const { return size; }
    virtual void SetSize(const Vec2d& value) {
        this->size.first = value.first;
        this->size.second = GetMaxCharSize().second + 4;
        this->UpdateTextOffset();

        if (this->close_button) {
            this->close_button->SetOffset({this->size.first - this->size.second, 0});
            this->close_button->SetSize({this->size.second, this->size.second});
        }
    }
    virtual Element* WithinCollision(const Vec2d& mouse_pos) {
        if (this->close_button)
            if (this->close_button->WithinCollision(mouse_pos))
                return this->close_button;
        return this->Element::WithinCollision(mouse_pos);
    }
private:
    void UpdateTextOffset() { this->text_offset = (this->GetSize() - draw::GetStringSize(display_text.c_str())) / 2; }
    const std::string* const display_text;
    Button* close_button = nullptr;
};
