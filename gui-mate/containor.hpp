
#pragma once

#include <string>
#include <vector>
#include <algorithm>

#include "element.hpp"

// contains other elements
class Containor : Element {
public:
    Containor(Element* _parent, std::string_view _name = "containor") : Element(_parent), name(_name) {}
    std::string name;
    virtual ~Containor(){}

    virtual void Draw() {
        for(Element* i : this->children)
            i->Draw();
    }
    virtual void UpdatePos() {
        for(Element* i : this->children)
            i->UpdatePos();
    }
    virtual void Move(const std::pair<int, int>& delta) {
        for(Element* i : this->children)
            i->Move(delta);
    }

    std::pair<int, int> offset = {0, 0};
    std::pair<int, int> size = {0, 0};
    virtual std::pair<int, int> GetOffset() { return this->offset; }
    virtual std::pair<int, int> GetSize() { return this->size; }
    virtual void SetOffset(const std::pair<int, int>& value) { this->offset = value; }
    virtual void SetSize(const std::pair<int, int>& value) { this->size = value; }
    virtual bool WithinCollision(const std::pair<int, int>& mouse_pos) {
        for(auto i = this->children.rbegin(); i != this->children.rend(); i++)
            if ((*i)->Within())
                return *i;
        return nullptr;
    }

    // User input
    virtual bool KeyEvent(CatKey k, bool state) { return false; } // return false to not consume event

    // Use for Containors and managing elements
    virtual std::string_view GetName() { return "unknown"; }


    void PutOnTop(Element* e) { // Put an element on top of everything else
        auto find = std::find(this->children.begin(), this->children.end(), e);
        if (find != this->children.end())
            this->children.erase(find);
        this->children.push_back(e);
    }
private:
    std::vector<Element*> children; // Ordering of this is whatever is at the end is on "top"
}
