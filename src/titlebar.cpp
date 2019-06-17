
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

//#include "titlebar.hpp"

namespace neko::gui {

/*TitleBar::Titlebar(ActingWindow* _parent, const std::string* const _display_text, bool _close_button)
        : Element(_parent), display_text(_display_text) {
        if (_close_button) {
            close_button = new Button(this, "X", [this](){
                delete this->parent;
            });
        }
        this->SetSize(this->_parent.GetSize());
    }

TitleBar::~TitleBar(){
    if (this->close_button)
        delete this->close_button;
}

void Titlebar::Draw(const Vec2d& abs) {
    Vec2d size = this->GetSize();
    draw::Line({abs.first, abs.second + size.second - 1}, {size.first, 0}, GetOutlineColor());
    draw::String(this->display_text, abs + this->text_offset);
    // Button
    if (this->close_button) {
        Vec2d butt_size = this->close_button->GetSize();
        this->close_button->Draw();
    }
}

void TitleBar::UpdateOffsets() {
    this->text_offset = (this->GetSize() - this->draw_api->GetLength(display_text) / 2;
    if (this->close_button) {
        Vec2d butt_size = this->close_button->GetSize();
        this->close_button_pos = {size.x - butt_size.x, 0};
    }
}

void Titlebar::SetSize(const Vec2d& value) {
    this->Element::SetSize({value.first, this->draw_api->GetLength(this->display_text).y + 4})

    if (this->close_button)
        this->close_button->SetSize({this->size.y, this->size.y});
    this->UpdateOffsets();
}*/

}
