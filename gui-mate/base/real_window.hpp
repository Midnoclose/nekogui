
#include "button.hpp"

#include "../root.hpp"

namespace gui {

class RealWindow : public Element {
    class TitleBar : public Element {
    public:
        TitleBar(RealWindow* _parent, std::string_view _display_text, bool _close_button = false)
            : Element(_parent), display_text(_display_text) {
            if (_close_button)
                close_button = new Button(this, "X", [&](){ delete this->parent; });
        }
        virtual ~TitleBar(){
            if (this->close_button)
                delete this->close_button;
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
            draw::Line(abs.first, abs.second + size.second - 1, size.first, 0, GetOutlineColor());
            // text
            draw::String(this->display_text.c_str(), abs + this->text_offset);
            // Button
            if (this->close_button)
                this->close_button->Draw();
        }
        virtual void MouseEvent(const std::pair<int, int>& mouse_pos, const std::pair<int, int>& move_delta) {
            this->parent->SetOffset(this->parent->GetOffset() + move_delta);
        }
        virtual std::pair<int, int> GetOffset() const { return this->offset; }; // Where is it located in relation to the parent
        virtual void SetOffset(const std::pair<int, int>& value) { this->offset = value; }
        virtual std::pair<int, int> GetSize() const { return size; }
        virtual void SetSize(const std::pair<int, int>& value) {
            this->size.first = value.first;
            this->size.second = GetMaxCharSize().second + 4;
            this->UpdateTextOffset();

            if (this->close_button) {
                this->close_button->SetOffset({this->size.first - this->size.second, 0});
                this->close_button->SetSize({this->size.second, this->size.second});
            }
        }
        virtual std::string_view GetName() const { return "title_bar"; }
        virtual Element* WithinCollision(const std::pair<int, int>& mouse_pos) {
            if (close_button)
                if (Element* ret = this->close_button->WithinCollision(mouse_pos))
                    return ret;
            return this->Element::WithinCollision(mouse_pos);
        }
    private:
        void UpdateTextOffset() { this->text_offset = (this->GetSize() - draw::GetStringSize(display_text.c_str())) / 2; }
        const std::string display_text;
        Element* close_button = nullptr;
    };
public:
    RealWindow(std::string_view display_text, bool close_button, std::string_view _name = "box_window")
        : Element(&GetRoot()), title_bar(this, display_text, close_button), contents(this) {
        Root::Add(this);
    }
    virtual ~RealWindow(){
        Root::Remove(this);
    }
private:
    std::pair<int, int> offset = {0, 0};
    std::pair<int, int> size = {0, 0};
public:
    virtual void Draw() const {
        std::pair<int, int> abs = this->GetAbsPos();
        std::pair<int, int> size = this->GetSize();
        draw::RectFilled(abs.first, abs.second, size.first, size.second, GetBackgroundColor());
        draw::Rect(abs.first, abs.second, size.first, size.second, GetOutlineColor());

        this->title_bar.Draw();
        this->contents.Draw();
    }
    virtual std::pair<int, int> GetOffset() const { return this->offset; }; // Where is it located in relation to the parent
    virtual void SetOffset(const std::pair<int, int>& value) { this->offset = value; }
    virtual std::pair<int, int> GetSize() const { return size; }
    virtual void SetSize(const std::pair<int, int>& value) {
        this->size = value;
        this->title_bar.SetSize({this->size.first, 0});
        // Move containor down an amount that is taken by the title bar
        int title_bar_height = this->title_bar.GetSize().second;
        this->contents.SetOffset({0, title_bar_height});
        this->contents.SetSize({this->size.first, this->size.second - title_bar_height});
    }
    virtual Element* WithinCollision(const std::pair<int, int>& mouse_pos) {
        if (Element* ret = this->title_bar.WithinCollision(mouse_pos))
            return ret;
        if (Element* ret = this->contents.WithinCollision(mouse_pos))
            return ret;
        return this->Element::WithinCollision(mouse_pos);
    }

    // Containor like functions
private:
    TitleBar title_bar;
    Containor contents;
};

}
