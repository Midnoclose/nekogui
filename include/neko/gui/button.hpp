
/*
 * Nekogui: Dumb ways to do existing things
 * Copyright (C) 2018 Rebekah Rowe
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <functional>

#include "../root.hpp"

namespace ngui {

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
    Vec2d offset = {0, 0};
    Vec2d size = {0, 0};
    Vec2d text_offset = {0,0};
public:
    virtual void Draw() const {
        Vec2d abs = this->GetAbsPos();
        Vec2d size = this->GetSize();
        // box
        draw::RectFilled(abs.first, abs.second, size.first, size.second, GetBackgroundColor());
        draw::Rect(abs.first, abs.second, size.first, size.second, GetOutlineColor());
        // text
        draw::String(this->display_text.c_str(), abs + this->text_offset);
    }
    virtual Vec2d GetOffset() const { return this->offset; }; // Where is it located in relation to the parent
    virtual void SetOffset(const Vec2d& value) { this->offset = value; }
    virtual Vec2d GetSize() const { return size; }
    virtual void SetSize(const Vec2d& value) {
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
