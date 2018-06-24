
#pragma once

#include "containor.hpp"

class Window : Containor {
    Window(Element* _parent, std::string_view _name = "window") : Containor(_parent, _name) {}
    virtual ~Window(){}

}
