
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

#include "element.hpp"

namespace neko::gui {

class Containor : public Element {
public:
    Containor(Element* parent);
    ~Containor() override;
    void Draw(const Vec2d&) const override;

    void OnMouseMove(const Vec2d&, const Vec2d&) override;
    void OnMousePress() override;
    void OnMouseRelease() override;
    void OnKeyPress(Key) override;
    void OnKeyRelease(Key) override;

	void Add(Element*); // inline
    void Add(Element*, const Vec2d&, bool floating); // static and floating
    void Del(Element*);
    void Clear();
    Element* WithinCollision(const Vec2d&, bool floating);
protected:
	Vec2d GetPos(Element*);
	Vec2d FindPos(Element*);
    enum class Positioning {
        kInline,
        kStatic,
        kFloating
    };
    struct ElmInfo {
        Element* element;
        Vec2d pos;
        Positioning state;
    };
    std::vector<ElmInfo> elements;
    Element* hovered = nullptr;
    Element* focused = nullptr;
    Element* pressed = nullptr;
    Vec2d mouse_pos;
};

}
