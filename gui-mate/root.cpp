
#include "root.hpp"

namespace gui {

// TODO: catvar these
static CatColor background_color = CatColor(25, 25, 25, 230);
static CatColor infill_color = CatColor(255, 130, 210);
static CatColor outline_color = CatColor(255, 105, 180);

// Fonts
static std::pair<int, int> max_char_size = {0, 0};
static void RefreshFonts() {
    auto ExpandMaxWithChar = [](char c) {
        std::pair<int, int> size = draw::GetStringSize(std::string(1, c).c_str());
        max_char_size.first = std::max(max_char_size.first, size.first);
        max_char_size.second = std::max(max_char_size.second, size.second);
    };
    for(char i : allowed_chars) {
        ExpandMaxWithChar(i);
        ExpandMaxWithChar(toupper(i));
    }
}

// Element states
static Element* hovered = nullptr;
static Element* pressed = nullptr;
static Element* focused = nullptr;

// psudo overrides
static void Draw() {
    if (focused)
        focused->FocusUpdate();

    GetRoot().Draw();
}

static void MouseEvent(std::pair<int, int> mouse_pos) {
    static std::pair<int, int> prev_mouse_pos;
    hovered = GetRoot().WithinCollision(input::GetMouse());
    // Must be pressed to recieve events
    if (pressed)
        pressed->MouseEvent(mouse_pos, mouse_pos - prev_mouse_pos);
    prev_mouse_pos = mouse_pos;
}

static void KeyEvent(CatKey key, bool state) {

    // Mouse depression and focus handler
    if (key == CatKey::kMouse1) {
        Element* last_focused = focused;
        if (state) { // click
            pressed = hovered;
            if (pressed)
                GetRoot().PutOnTop(pressed);
            focused = nullptr;
        } else { // Unclick
            if (pressed == hovered)
                focused = pressed;
            if (pressed)
                pressed->KeyEvent(key, state);
            pressed = nullptr;
        }
        // focus change
        if (focused != last_focused) {
            if (focused)
                focused->FocusEvent(true);
            if (last_focused)
                last_focused->FocusEvent(false);
        }
        return;
    }

    // Normal
    if (focused)
        return focused->KeyEvent(key, state);
}

// Root fixes
Root Root::instance;
void Root::PutOnTop(Element* element) { // We need to find the parent that exists within us to clearly put on top
    assert(element);
    Element* e = element;
    while(instance.Find(e) == instance.children.end()) {
        e = e->parent;
        if (e == nullptr)
            throw std::runtime_error("Element not in root");
    }
    instance.Containor::PutOnTop(e);
}
void Root::Remove(Element* element) { // We need to do cleanup to prevent segfaults
    Root::Cleanup(element);
    instance.Containor::Remove(element);
}
void Root::Cleanup(Element* element) {
    if (hovered == element)
        hovered = nullptr;
    if (pressed == element)
        pressed = nullptr;
    if (focused == element)
        focused = nullptr;
}

// Getters

// Font
const std::pair<int, int>& GetMaxCharSize() { return max_char_size; }

// Colors
CatColor GetBackgroundColor() { return background_color; }
CatColor GetInFillColor() { return infill_color; }
CatColor GetOutlineColor() { return outline_color; }

// States
Element* GetHovered() { return hovered; }
Element* GetPressed() { return pressed; }
Element* GetFocused() { return focused; }

void Init() {
    RefreshFonts();
    // TODO:, add to event so we refresh fonts when they change

    std::pair<int, int> GetStringLength(const char* text, int font, int font_size);
    events::draw.Listen(Draw);
    input::events::bounds.Listen([](std::pair<int, int> bounds){ GetRoot().SetSize(bounds); });
    input::events::key.Listen(KeyEvent);
    input::events::mouse.Listen(MouseEvent);
}

}
