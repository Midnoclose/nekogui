
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

#include "../nekohook/drawing.hpp"

#include "../root.hpp"

namespace neko::gui::window {

// TODO: we need a way to do pressed, how do we get what is pressed
class Box : public Base {
public:

    virtual void Draw() const {
        Vec2d size = this->GetSize();
        draw::RectFilled(abs, this->draw_api);
        draw::Rect(abs, size, GetOutlineColor());
        this->Base::Draw();
    }

    virtual void MouseEvent(const Vec2d& mouse_pos, const Vec2d& move_delta) {
        this->SetOffset(this->GetOffset() + move_delta);
    }

    virtual Element* WithinCollision(const Vec2d& mouse_pos) {
        if (Element* ret = this->Containor::WithinCollision(mouse_pos))
            return ret;
        return this->Element::WithinCollision(mouse_pos);
    }
};

}
