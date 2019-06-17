
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

#include "button.hpp"

namespace neko::gui {

Button::Button(Element* _parent, std::string_view _display_text, std::function<void()> _callback)
    : display_text(_display_text), callback(_callback) {
    this->draw_api = _parent->draw_api;
    this->UpdateOffsets();
}
Button::~Button() {}

void Button::Draw(const Vec2d& abs) const {
    Vec2d size = this->GetSize();
    this->draw_api->RectFilled(abs, size, this->draw_api->background);
    if (this->pressed)
        this->draw_api->RectFilled(abs, size, this->draw_api->foreground.Transparent(30));
    this->draw_api->RectOutline(abs, size, this->draw_api->outline);
    this->draw_api->String(abs + this->text_offset, this->display_text, RGBColor::white);
}

void Button::SetSize(const Vec2d& value) {
	Vec2d size;
    size.x = value.x;
    size.y = this->draw_api->GetLength(this->display_text).y + 4;
    this->Element::SetSize(size);
    this->UpdateOffsets();
}

void Button::OnMouseEnter() { this->hovered = true; }
void Button::OnMouseLeave() { this->hovered = false; }
void Button::OnMousePress() { this->pressed = true; }
void Button::OnMouseRelease() {
    if (this->hovered)
        this->callback();
}
void Button::UpdateOffsets() {
    this->text_offset = (this->GetSize() - this->draw_api->GetLength(display_text)) / 2;
}

}
