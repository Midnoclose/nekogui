
#include <cmath>
#include <algorithm>

#include "../nekohook/chrono.hpp"
#include "../nekohook/drawing.hpp"

#include "../root.hpp"

namespace gui {

class TextInputBox : public Element {
public:
    TextInputBox(Element* _parent, std::string& _content) : Element(_parent), content(_content) {
        this->SetSize({_content.size() * GetMaxCharSize().first, 1});

        // Initialize text
        this->pos = _content.size();
        this->UpdateDrawString();
    }
    virtual ~TextInputBox(){}
private:

    std::pair<int, int> offset = {0, 0};
    std::pair<int, int> size = {0, 0};
    // draw cache
    std::pair<int, int> pos_offset = {3, 0};// start(and end if any)
    std::string draw_string;
    // Curser
    bool pos_blink = false;
    CatTimer pos_timer;
public:
    virtual void Draw() const {
        std::pair<int, int> abs = this->GetAbsPos();
        std::pair<int, int> size = this->GetSize();
        // box
        draw::RectFilled(abs.first, abs.second, size.first, size.second, GetBackgroundColor());
        draw::Rect(abs.first, abs.second, size.first, size.second, GetOutlineColor());
        // text
        draw::String(this->draw_string.c_str(), {abs.first + 2, abs.second + 2});
        // Pos marker
        if (GetFocused() == this) {
            if (this->end_pos != -1)
                draw::RectFilled(abs.first + pos_offset.first, abs.second + 3, pos_offset.second, size.second - 6, CatColor(230, 230, 230, 100));
            if (pos_blink)
                draw::RectFilled(abs.first + pos_offset.first, abs.second + 3, 2, size.second - 6, GetOutlineColor());
        }
    }
    virtual void FocusUpdate() {
        if (this->pos_timer.ResetAfter(std::chrono::milliseconds(400)))
            this->pos_blink = !this->pos_blink;
    }

    virtual std::pair<int, int> GetOffset() const { return this->offset; };
    virtual void SetOffset(const std::pair<int, int>& value) { this->offset = value; }
    virtual std::pair<int, int> GetSize() const { return size; }
    virtual void SetSize(const std::pair<int, int>& value) {
        const std::pair<int, int>& max_char_size = GetMaxCharSize();
        this->size.first = std::min(value.first, (this->parent->GetSize().first - this->GetOffset().first) + 4);
        this->size.second = max_char_size.second + 4;
    }

    // User input
    virtual void MouseEvent(const std::pair<int, int>& mouse_pos, const std::pair<int, int>& move_delta) {
        // TODO, selection
    }
    virtual void KeyEvent(CatKey key, bool state) {
        if (!state)
            return;

        // Reset blink for key
        this->pos_timer.Reset();
        this->pos_blink = true;

        // TODO, fix this it looks ugly
        switch(key) {
        // Selection
        case CatKey::kMouse1:
            // TODO, selection
            return;
        // Deletion
        case CatKey::kBackspace:
            if (this->end_pos != -1) { // selection
                this->content.erase(this->pos, this->end_pos - this->pos);
                this->end_pos = -1;
            } else if (pos != 0) // one char
                this->content.erase(pos - 1, 1);
            this->pos--;
            break;
        case CatKey::kDelete:
            if (this->end_pos != -1) { // selection
                this->content.erase(this->pos, this->end_pos - this->pos);
                this->end_pos = -1;
            } else if (this->pos != this->content.size()) // one char
                this->content.erase(pos, 1);
            break;
        // Movement
        case CatKey::kLeft:
            this->pos--;
            this->end_pos = -1;
            break;
        case CatKey::kRight:
            this->pos++;
            this->end_pos = -1;
            break;
        case CatKey::kHome:
            this->pos = 0;
            this->end_pos = -1;
            break;
        case CatKey::kEnd:
            this->pos = this->content.size();
            this->end_pos = -1;
            break;
        default:
            char c;
            if (key == CatKey::kSpace)
                c = ' ';
            else {
                std::string_view key_name = input::key_names[static_cast<size_t>(key)];
                if (key_name.size() != 1)
                    return;

                c = tolower(key_name[0]);
                if (allowed_chars.find(c) == std::string_view::npos)
                    return;

                // Caps stuff
                if (input::GetKey(CatKey::kLShift) || input::GetKey(CatKey::kRShift))
                    c = toupper(c);
            }

            if (this->end_pos != std::string::npos) {
                this->content.erase(this->pos, this->end_pos - this->pos);
                this->end_pos = -1;
            }

            this->content.insert(pos, 1, c);
            this->pos++;
        }
        this->UpdateDrawString();
    }
    virtual std::string_view GetName() const { return "text_input_box"; }
    void UpdateDrawString() {
        // clamp our pos to prevent issues
        this->pos = std::clamp(this->pos, 0, static_cast<int>(this->content.size()));

        int max_length = this->GetSize().first - 3;
        if (draw::GetStringSize(this->content.c_str()).first > max_length) {
            // Get the largest string we can fit with the shift
            auto GetMaxString = [&](int shift){
                std::string cur = this->content.substr(shift);
                while (draw::GetStringSize(cur.c_str()).first > max_length)
                    cur.pop_back();
                return cur;
            };
            this->draw_string = GetMaxString(this->text_shift);

            // No selection == auto shift
            if (this->end_pos == -1) {
                // Shift right
                if (this->pos < this->text_shift)
                    this->text_shift = this->pos;
                // TODO, fix autoshift
                // Shift left
                while (this->pos > this->text_shift + this->draw_string.size())
                    this->draw_string = GetMaxString(this->text_shift++);
            }
            // Reclamp the text shift
            //this->text_shift = std::clamp(this->text_shift, 0, static_cast<int>(this->content.size()) - 3);

            this->draw_string = GetMaxString(this->text_shift);
        } else {
            draw_string = content;
            text_shift = 0;
        }
        // Drawing curser cache
        this->pos_offset.first = std::max(3, draw::GetStringSize(this->draw_string.substr(0, pos - this->text_shift).c_str()).first);
    }
private:
    std::string& content; // string the text box changes
    int pos = 0;
    int end_pos = -1; // for selection
    int text_shift = 0;
};

}
