
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
    using Base::Base;
    ~Box() override;

    virtual void Draw() const {
        Vec2d size = this->GetSize();
        draw::RectFilled(abs, this->draw_api);
        draw::Rect(abs, size, GetOutlineColor());
        this->Base::Draw();
    }
};

class Base : public Element {
public:
    using Element::Element;
    ~Base() override;

    void KeyEvent(Key k, bool state) override;
    void MouseEvent(const Vec2d& mouse_pos, const Vec2d& move_delta);
    void OnMouseEnter() override;
    void OnMouseLeave() override;
    void OnMousePress() override;
    void OnMouseRelease() override;
    void OnKeyPress(Key key) override;
    void OnKeyRelease(Key key) override;

    void Add(Element*);
    void Clear();
private:
    struct PosInfo {
        Element* element;
        Vec2d pos;
        enum State {
            kInline,
            kStatic,
            kFloating
        } state;
    }
    Element* hovered = nullptr;
    std::vector<PosInfo> elements;
};

}
