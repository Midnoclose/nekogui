
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

#include "draw/primitives.hpp"
#include "draw/draw.hpp"

namespace neko::gui::draw {

class APIMachine : public DrawMachine{
public:
	APIMachine(){}
	~APIMachine() override {}
	void Line(const Vec2d& w, const Vec2d& s, RGBColor c) const override {
		draw::Line(w, s, c);
	}
	void RectOutline(const Vec2d& w, const Vec2d& s, RGBColor c) const override {
		draw::RectOutline(w, s, c);
	}
	void RectFilled(const Vec2d& w, const Vec2d& s, RGBColor c) const override {
		draw::RectFilled(w, s,c);
	}
	void Circle(const Vec2d& w, float radius, int steps, RGBColor c) const override {
		draw::Circle(w, radius, steps, c);
	}
	void String(const Vec2d& w, std::string_view s, RGBColor c) const override {
		draw::String(w, s, this->font, c);
	}
	Vec2d GetLength(std::string_view s) const override {
		return draw::GetLength(s, this->font);
	}
};

DrawMachine* api_machine = new APIMachine();

}
