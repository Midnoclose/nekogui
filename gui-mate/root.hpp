
#pragma once

#include "containor.hpp"

// Things you need to do for root, use SetSize to set the size of the display


// Root is a singleton that handles and manages the elements in the gui
class Root : Containor {
public:
    Root(std::pair<int, int> screen_size) Containor(nullptr, "root") { this->SetSize(screen_size); }
    static Root root; // The singleton instance

    // Static functions not meant to be used by elements thus are static
    static void Draw() { root.Draw(); }
    static void KeyEvent(CatKey k, bool state) { root.KeyEvent(k, state); }

    virtual std::pair<int, int> GetOffset() final { return 0; }
    virtual std::pair<int, int> GetAbsPos() final { return 0; }
}
