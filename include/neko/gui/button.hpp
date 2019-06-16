
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

#include <functional>

#include "element.hpp"

namespace neko::gui {

class Button : public Element {
public:
    Button(Element* _parent, std::string_view _display_text, std::function<void()> _callback);
    ~Button() override;
    void Draw(const Vec2d&) const override;
    
    void OnMouseEnter() override;
	void OnMouseLeave() override;
	void OnMousePress() override;
	void OnMouseRelease() override;
	
    void SetSize(const Vec2d&) override;
private:
    void UpdateOffsets();
    bool hovered = false;
    bool pressed = false;
    Vec2d text_offset;
    const std::string display_text;
    const std::function<void()> callback;
};

}
