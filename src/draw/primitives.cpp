
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

#include <glez/draw.hpp>
#include <glez/font.hpp>

#include "draw/primitives.hpp"

namespace neko::gui::draw {

static inline glez::rgba ToRgbf(const RGBColor& c) {
    return glez::rgba(c.r, c.g, c.b, c.a);
}
void Line(const Vec2d& w, const Vec2d& s, RGBColor c) {
    glez::draw::line(w.x, w.y, s.x, s.y, ToRgbf(c), 1);
}
void RectOutline(const Vec2d& w, const Vec2d& s, RGBColor c) {
    glez::draw::rect_outline(w.x, w.y, s.x, s.y, ToRgbf(c), 1);
}
void RectFilled(const Vec2d& w, const Vec2d& s, RGBColor c){
    glez::draw::rect(w.x, w.y, s.x, s.y, ToRgbf(c));
}
void Circle(const Vec2d& w, float radius, int steps, RGBColor c){
    glez::draw::circle(w.x, w.y, radius, ToRgbf(c), 1, steps);
}
void String(const Vec2d w, std::string_view s, const Font& f, RGBColor _c){
    glez::rgba c = ToRgbf(_c);
    f.GetHandle()->setForegroundColor(c.r, c.g, c.b, c.a);
    f.GetHandle()->draw(w.x, w.y, std::string(s).c_str());
}
Vec2d GetLength(std::string_view s, const Font& f){
    OGLFT::BBox bbox = f.GetHandle()->measure(std::string(s).c_str());
    return Vec2d(bbox.x_max_, bbox.y_max_);
}

}
