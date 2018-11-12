
#include <functional>

#include "../root.hpp"

namespace gui {

class Button : public Element {
public:
    Button(Element* _parent, std::string_view _display_text, std::function<void()> _callback)
        : Element(_parent), display_text(_display_text), callback(_callback) {
        this->UpdateTextOffset();
    }
    virtual ~Button(){
        // in case we get pressed and removed
        Root::Cleanup(this);
    }
private:
    std::pair<int, int> offset = {0, 0};
    std::pair<int, int> size = {0, 0};
    std::pair<int, int> text_offset = {0,0};
public:
    virtual void Draw() const {
        std::pair<int, int> abs = this->GetAbsPos();
        std::pair<int, int> size = this->GetSize();
        // box
        draw::RectFilled(abs.first, abs.second, size.first, size.second, GetBackgroundColor());
        draw::Rect(abs.first, abs.second, size.first, size.second, GetOutlineColor());
        // text
        draw::String(this->display_text.c_str(), abs + this->text_offset);
    }
    virtual std::pair<int, int> GetOffset() const { return this->offset; }; // Where is it located in relation to the parent
    virtual void SetOffset(const std::pair<int, int>& value) { this->offset = value; }
    virtual std::pair<int, int> GetSize() const { return size; }
    virtual void SetSize(const std::pair<int, int>& value) {
        this->size.first = std::min(value.first, (this->parent->GetSize().first - this->GetOffset().first) + 4);
        this->size.second = GetMaxCharSize().second + 4;
        this->UpdateTextOffset();
    }
    virtual void KeyEvent(CatKey key, bool state) {
        if (!state && key == CatKey::kMouse1)
            this->callback();

    }
    virtual std::string_view GetName() const { return "button"; }
private:
    void UpdateTextOffset() { this->text_offset = (this->GetSize() - draw::GetStringSize(display_text.c_str())) / 2; }
    const std::string display_text;
    const std::function<void()> callback;
};

}
