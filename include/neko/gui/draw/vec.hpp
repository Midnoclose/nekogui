
/*
 * nGui: Dumb ways to do existing things
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

namespace neko::gui {
namespace internal {

template<typename T>
class Vec2d {
public:
    using ThisT = Vec2d<T>;
    Vec2d(T _x, T _y) : x(_x), y(_y) {}
    T x, y;
    bool operator=(const ThisT& i) { return this->x == i.x && this->y == i.y; }
    ThisT operator+(const ThisT& i) { return ThisT(this->x + i.x, this->y + i.y); }
    ThisT operator-(const ThisT& i) { return ThisT(this->x - i.x, this->y - i.y); }
};
}
#if !defined(NGUI_HEADLESS)
using Vec2d = internal::Vec2d<float>;
#else
using Vec2d = internal::Vec2d<int>;
#endif
}
