
#pragma once

#include <utility>

class Element {

    virtual void Draw() = 0;
    virtual void UpdatePos() = 0; // Cache all your positions, string sizes, etc

    virtual std::pair<int, int> GetOffset() = 0; // Where is it located in relation to the parent
    virtual std::pair<int, int> GetSize() = 0; // How big
    virtual void SetOffset(const std::pair<int, int>&) = 0; // Where is it located in relation to the parent
    virtual void SetSize(const std::pair<int, int>&) = 0; // How big
};
