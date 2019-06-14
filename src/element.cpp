

#pragma once

#include <utility>
#include <string_view>

#include "element.hpp"

namespace neko::gui {

Element(Element* _parent) : {
    if (_parent)
        this->draw_api = this->_parent->draw_api;
}

Element::~Element();

void Element::OnMouseEnter() {}
void Element::OnMouseLeave() {}
void Element::OnMousePress() {}
void Element::OnMouseRelease() {}
void Element::OnKeyPress(Key key) {}
void Element::OnKeyRelease(Key key) {}
void Element::OnFocusGain() {}
void Element::OnFocusLose() {}

void Element:SetSize(const Vec2d& new_size) {
    this->size.x = std::clamp(new_size.x, 0, max_size.x);
    this->size.y = std::clamp(new_size.y, 0, max_size.y);
}
void Element:SetMaxSize(const Vec2d& new_size) {
    this->max_size = new_size;
    this->SetSize(this->size);
}


virtual Vec2d GetSize() { return this->size; }
virtual Vec2d GetMaxSize() { return this->MaxSize; }


}
