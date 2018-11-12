
/*
 *
 * THe root element of the gui
 *
 */

#pragma once

#include "nekohook/drawing.hpp"

#include "base/containor.hpp"

namespace gui {

static inline std::string_view allowed_chars = "abcdefghijklmnopqrstuvwxyz123456789 ";
const std::pair<int, int>& GetMaxCharSize();

void Init();

// The root element
class Root : public Containor {
    Root() : Containor(nullptr) {}
    virtual ~Root(){}
    static Root instance;
public:
    static Root& GetInstance() { return instance; }

    static void PutOnTop(Element* element);
    static void Add(Element* element) { instance.Containor::Add(element); }
    static void Remove(Element*);
    static void Cleanup(Element*); // Cleanup from deletion

    virtual std::string_view GetName() const { return "root"; }
    virtual std::pair<int, int> GetOffset() const { return {0, 0}; }
    virtual std::pair<int, int> GetAbsPos() const { return {0, 0}; }
};
inline Root& GetRoot() { return Root::GetInstance(); }

// Colors
CatColor GetBackgroundColor();
CatColor GetInFillColor();
CatColor GetOutlineColor();

// States
Element* GetHovered();
Element* GetPressed();
Element* GetFocused();

// Drawing to use the gui font
namespace draw {
using namespace ::draw;
static void String(const char* str, std::pair<int, int> pnt) { ::draw::String(str, pnt.first, pnt.second, 0, 8, colors::white); }
static std::pair<int, int> GetStringSize(const char* str){ return ::draw::GetStringLength(str, 0, 8); }
}

}
