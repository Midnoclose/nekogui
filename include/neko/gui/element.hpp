
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

#include <utility>
#include <string_view>

#include "draw/draw.hpp"
#include "input/input.hpp"

namespace neko::gui {

class Element {
public:
    virtual ~Element();

    draw::DrawMachine* draw_api;
    virtual void Draw(const Vec2d&) const = 0;

    virtual void OnMouseMove(const Vec2d& mouse_pos, const Vec2d& move_delta);
	virtual void OnMouseEnter();
	virtual void OnMouseLeave();
	virtual void OnMousePress();
	virtual void OnMouseRelease();
	virtual void OnKeyPress(Key);
	virtual void OnKeyRelease(Key);

    virtual void SetSize(const Vec2d&);
	void SetMaxSize(const Vec2d&);
	Vec2d GetSize() const;
    Vec2d GetMaxSize() const;
private:
    Vec2d size;
    Vec2d max_size = {1080, 1080};
};

}
