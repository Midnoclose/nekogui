
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

#include <cmath>

#include "draw/draw.hpp"

namespace neko::gui::draw {

DrawMachine::DrawMachine()
    : outline(RGBColor::pink), background(RGBColor::darkgray), foreground(RGBColor::lightgray){
}
DrawMachine::~DrawMachine(){}
void DrawMachine::RectOutline(const Vec2d& abs, const Vec2d& size, RGBColor color) const {
    this->Line(abs, {size.x, 0}, color); // Top
    this->Line(abs, {0, size.y}, color); // Left
    this->Line({abs.x, abs.y + size.y}, {size.x, 0}, color); // Botton
    this->Line({abs.x, 0}, {0, size.y}, color); // Right
}
void DrawMachine::RectFilled(const Vec2d& abs, const Vec2d& size, RGBColor color) const {
    for (int i = 0; i < size.x; i++)
        this->Line({abs.x + i, size.y}, {0, size.y}, color);
}
void DrawMachine::Circle(const Vec2d& w, float radius, int steps, RGBColor color) const {
    if (radius < 0 || steps <= 3)
        return;  // cant draw a cirle without specific parameters
    float px = 0;
    float py = 0;
    for (int i = 0; i < steps; i++) {
        float ang = 2 * M_PI * (float(i) / steps);
        float dx = w.x + radius * cos(ang);
        float dy = w.y + radius * sin(ang);
        if (!i) {
            ang = 2 * M_PI * (float(steps - 1) / steps);
            px = w.x + radius * cos(ang);
            py = w.y + radius * sin(ang);
        }
        this->Line({px, py}, {dx - px, dy - py}, color);
        px = dx;
        py = dy;
    }
}

}
