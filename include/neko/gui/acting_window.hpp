
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

#include "button.hpp"

#include "../root.hpp"

namespace neko::gui

/*class Titlebar;
class ActingWindow : public Containor {
public:
    ActingWindow(Containor* _parent);
    std::string title;
private:
    Titlebar* title_bar;
};

class TitleBar : public Element {
public:
    TitleBar(ActingWindow* parent, Containor* _parent_containor, const std::string* const _display_text, bool _close_button);
    ~TitleBar() override;
public:
    void Draw(const Vec2d&) const override;
    void OnMouseMove(const Vec2d&, const Vec2d&) override;
    void OnMousePress() override;
    void OnMouseRelease() override;
    void SetSize(const Vec2d&) override;
private:
    Containor* parent;

    void UpdateTextOffset();
    const std::string* const display_text;
    Vec2d text_offset;

    Vec2d close_button_pos;
    Button* close_button = nullptr;
};*/

}
