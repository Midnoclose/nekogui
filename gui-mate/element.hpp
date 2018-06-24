
#pragma once

#include <utility>
#include <string_view>

// Make pairs easier to use
inline std::pair<int, int> operator+(const std::pair<int, int>& v1, const std::pair<int, int>& v2) {
    return {v1.first + v2.first, v1.second + v2.second};
}
inline std::pair<int, int>& operator+=(const std::pair<int, int>& v1, const std::pair<int, int>& v2) {
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
    virtual ~Element() = 0; // THIS IS AN ABSOLUTE MUST FOR DELETING ELEMENTS!
    const Element* parent; // Who owns the element, only root is allowed nullptr

    // General use goodies
    virtual void Draw() = 0;
    // Called when a move happens, just apply the delta to your cached abs positions
    // Cache all your positions, string sizes, etc
    virtual void Move(const std::pair<int, int>& delta) {}
    virtual void UpdatePos(){} // A complete update on positions, for when move isnt enough

    // For positioning, bounds checking etc
    virtual std::pair<int, int> GetOffset() = 0; // Where is it located in relation to the parent
    virtual std::pair<int, int> GetSize() = 0; // How big
    virtual void SetOffset(const std::pair<int, int>&) = 0; // Where is it located in relation to the parent
    virtual void SetSize(const std::pair<int, int>&) = 0; // How big
    // get element inside "collision"
    // You should really use this to cache your abs pos
    virtual Element* WithinCollision(const std::pair<int, int>& pos) {
        std::pair<int, int> abs = this->GetAbsPos();
        return (pos > abs && pos < abs + this->GetOffset()) ? this : nullptr
    }

    // User input
    virtual bool KeyEvent(CatKey k, bool state) { return false; } // return true to  consume event

    // Use for Containors and managing elements
    virtual std::string_view GetName() {return "unknown";}

    // Utility functions
    virtual std::pair<int, int> GetAbsPos() { // Get absolute positioning based on parental offsets, cache this please
        return this->parent->GetAbsPos() + this->GetOffset();
    }
};
