
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

#include "containor.hpp"

namespace neko::gui {

Containor::Containor(Element* _parent) {
    this->draw_api = _parent->draw_api;
}
Containor::~Containor(){}

void Containor::Draw(const Vec2d& abs) const {
    for (const ElmInfo& i : this->elements)
        i.element->Draw(abs + i.pos);
}
void Containor::OnMouseMove(const Vec2d& mouse_pos, const Vec2d& move_delta) {
	this->mouse_pos = mouse_pos;
    Element* within = this->WithinCollision(mouse_pos, true);
    if (this->hovered != within) {
		this->hovered->OnMouseLeave();
		this->hovered = nullptr;
	}
	if (within && !this->hovered) {
		this->hovered = within;
        this->hovered->OnMouseEnter();
    }
    if (this->hovered)
		this->hovered->OnMouseMove(mouse_pos - this->GetPos(this->hovered), move_delta);
}
void Containor::OnMousePress() {
	this->pressed = this->WithinCollision(this->mouse_pos, true);
	if (this->pressed)
		this->pressed->OnMousePress();
}
void Containor::OnMouseRelease() {
	if (this->pressed) {
		 this->pressed->OnMouseRelease();
	}
	Element* within = this->WithinCollision(this->mouse_pos, true);
	if (within == this->pressed)
		this->focused = this->pressed;
	this->pressed = nullptr;
}
void Containor::OnKeyPress(Key key) { if (this->focused) this->focused->OnKeyPress(key); }
void Containor::OnKeyRelease(Key key) { if (this->focused) this->focused->OnKeyRelease(key); }

void Containor::Add(Element* e) {
	ElmInfo data;
	data.pos = this->FindPos(e);
	data.element = e;
	data.state = Positioning::kInline;
    this->elements.push_back(data);
}
void Containor::Add(Element* e, const Vec2d& _pos, bool floating) {
	ElmInfo data;
	data.pos = _pos;
	data.element = e;
	data.state = floating ? Positioning::kFloating : Positioning::kStatic;
    this->elements.push_back(data);
}
void Containor::Clear() {
    for (auto& i : this->elements)
        delete i.element;
    this->elements.clear();
}

Element* Containor::WithinCollision(const Vec2d&, bool floating) {
	for (auto i = this->elements.rbegin(); i != this->elements.rend(); i++)
		if (floating || i->state != Positioning::kFloating)
			if (i->pos > mouse_pos && i->pos + i->element->GetSize() < mouse_pos)
				return i->element;
	return nullptr;
}
Vec2d Containor::GetPos(Element* e) {
	auto find = std::find_if(this->elements.begin(), this->elements.end(), [&](auto i){
		return i.element == e;
	});
	if (find == this->elements.end())
		throw std::runtime_error("Containor: unable to find element");
	return find->pos;
}
Vec2d Containor::FindPos(Element*e) {
	Vec2d end = this->GetSize() - e->GetSize();
	Vec2d i;
	for(i.x = 0; i.x < end.x; i.x++)
		for(i.y = 0; i.y < end.y; i.y++)
			if (!this->WithinCollision(i, false))
				return i;
	throw std::runtime_error("Containor: unable to find position for element");
}

}
