
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
class Box : public Containor {
public:
    Box(Containor* _parent);
    ~Box() override;

    void Draw() const override;
    void OnMousePress() override;
	void OnMouseRelease() override;
    void OnMouseMove(const Vec2d&, const Vec2d&) override;
private:
    Containor*  parent;
    bool box_pressed;
};

void Box::Draw() {
   Vec2d size = this->GetSize();
   draw::RectFilled(abs, this->draw_api);
   draw::Rect(abs, size, GetOutlineColor());
   this->Containor::Draw();
}

void Box::OnMousePress() {
    if (!WithinCollision(this->mouse_pos))
        this->box_pressed = true;
    else
        this->Containor::OnMousePress();
}

void Box::OnMouseRelease() {
    if (this->box_pressed)
        this->box_pressed = false;
    else
        this->Containor::OnMouseRelease();
}

void Box::OnMouseMove(const Vec2d&, const Vec2d& delta) {

}

}
