
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

#pragma once

#include <neko/color.hpp>

#include "vec.hpp"

#include "font.hpp"

namespace neko::gui::draw {

class DrawMachine {
public:
	DrawMachine();
	virtual ~DrawMachine();
    virtual void Line(const Vec2d&, const Vec2d&, RGBColor) const = 0;
    virtual void RectOutline(const Vec2d&, const Vec2d&, RGBColor) const;
    virtual void RectFilled(const Vec2d&, const Vec2d&, RGBColor) const;
    virtual void Circle(const Vec2d& w, float radius, int steps, RGBColor) const;
    virtual void String(const Vec2d& w, std::string_view, RGBColor) const = 0;
    virtual Vec2d GetLength(std::string_view) const = 0;
    RGBColor outline;
    RGBColor background;
    RGBColor foreground;
    Font font;
};

}
