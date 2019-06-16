
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

#include <cassert>
#include <initializer_list>

namespace neko::gui {

class Vec2d {
public:
    using Type = float;
    inline Vec2d(Type _x = 0, Type _y = 0) : x(_x), y(_y) {}
    inline Vec2d(const std::initializer_list<Type> l) {
		assert(l.size() == 2);
		this->x = *l.begin();
		this->y = *(l.begin() + 1);
	}
    Type x, y;
    inline bool operator=(const Vec2d& i) const { return this->x == i.x && this->y == i.y; }
    inline bool operator==(const Vec2d& i) const { return this->x == i.x && this->y == i.y; }
    inline Vec2d operator+(const Vec2d& i) const { return Vec2d(this->x + i.x, this->y + i.y); }
    inline Vec2d operator-(const Vec2d& i) const { return Vec2d(this->x - i.x, this->y - i.y); }
    inline Vec2d operator/(Type i) const { return Vec2d(this->x / i, this->y / i); }
    inline bool operator>(const Vec2d& i) const { return this->x > i.x && this->y > i.y; }
    inline bool operator<(const Vec2d& i) const { return this->x < i.x && this->y < i.y; }
};

}
