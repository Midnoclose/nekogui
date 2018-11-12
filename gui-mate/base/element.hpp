
#pragma once

#include <utility>
#include <string_view>

#include "../nekohook/input.hpp"

namespace gui {

// Make pairs easier to use
inline std::pair<int, int> operator+(const std::pair<int, int>& v1, const std::pair<int, int>& v2) {
    return {v1.first + v2.first, v1.second + v2.second};
}
inline std::pair<int, int> operator-(const std::pair<int, int>& v1, const std::pair<int, int>& v2) {
    return {v1.first - v2.first, v1.second - v2.second};
}
inline std::pair<int, int> operator/(const std::pair<int, int>& v1, const std::pair<int, int>& v2) {
    return {v1.first / v2.first, v1.second / v2.second};
}
inline std::pair<int, int> operator/(const std::pair<int, int>& v1, int v2) {
    return {v1.first / v2, v1.second / v2};
}
inline std::pair<int, int>& operator+=(std::pair<int, int>& v1, const std::pair<int, int>& v2) {
    v1.first += v2.first;
    v1.second += v2.second;
    return v1;
}
inline bool operator>(const std::pair<int, int>& v1, const std::pair<int, int>& v2) {
    return v1.first > v2.first && v1.second > v2.second;
}
inline bool operator<(const std::pair<int, int>& v1, const std::pair<int, int>& v2) {

    return v1.first < v2.first && v1.second < v2.second;
}

class Element {
public:
    Element(Element* _parent) : parent(_parent){}
    virtual ~Element() {} // THIS IS AN ABSOLUTE MUST FOR DELETING ELEMENTS!
    Element* const parent; // Who owns the element, only root is allowed nullptr

    // General use goodies
    // draw is const, do updates from events or in the FocusUpdate
    virtual void Draw() const = 0;
    virtual void FocusUpdate(){} // Recieve an update call since you are focused

    // For positioning, bounds checking etc
    virtual std::pair<int, int> GetOffset() const = 0; // Where is it located in relation to the parent
    virtual std::pair<int, int> GetSize() const = 0; // How big
    virtual void SetOffset(const std::pair<int, int>&) = 0; // Where is it located in relation to the parent
    virtual void SetSize(const std::pair<int, int>&) = 0; // How big

    // User input
    virtual void KeyEvent(CatKey k, bool state) {}
    virtual void MouseEvent(const std::pair<int, int>& mouse_pos, const std::pair<int, int>& move_delta) {} // do mouse stuff
    virtual void FocusEvent(bool focus_state){}
    // get element inside "collision"
    // You should really use this to cache your abs pos
    virtual Element* WithinCollision(const std::pair<int, int>& pos) {
        std::pair<int, int> abs = this->GetAbsPos();
        return (pos > abs && pos < abs + this->GetSize()) ? this : nullptr;
    }

    // Use for saving gui position info
    virtual std::string_view GetName() const { return "unknown"; }

    // Utility functions
    virtual std::pair<int, int> GetAbsPos() const { // Get absolute positioning based on parental offsets, cache this please
        return this->parent->GetAbsPos() + this->GetOffset();
    }

    // Get a clamped size
    std::pair<int, int> ClampSize(const std::pair<int, int>& value){
        std::pair<int, int> offset = this->GetOffset();
        std::pair<int, int> size = this->parent->GetSize();
        return {
            std::min(value.first, size.first - offset.first),
            std::min(value.second, size.second - offset.second)};
    }
    // Use for parents
    void ApplyClamp() {
        this->SetSize(this->ClampSize(this->GetSize()));
    }
};

}
