
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

#include <algorithm>

#include "element.hpp"

namespace neko::gui {

Element::~Element(){}

void Element::OnMouseMove(const Vec2d&, const Vec2d&){}
void Element::OnMouseEnter() {}
void Element::OnMouseLeave() {}
void Element::OnMousePress() {}
void Element::OnMouseRelease() {}
void Element::OnKeyPress(Key key) {}
void Element::OnKeyRelease(Key key) {}

void Element::SetSize(const Vec2d& new_size) {
    this->size.x = std::clamp<Vec2d::Type>(new_size.x, 0, max_size.x);
    this->size.y = std::clamp<Vec2d::Type>(new_size.y, 0, max_size.y);
}
void Element::SetMaxSize(const Vec2d& new_size) {
    this->max_size = new_size;
    this->SetSize(this->size);
}


Vec2d Element::GetSize() const { return this->size; }
Vec2d Element::GetMaxSize() const { return this->max_size; }

}
