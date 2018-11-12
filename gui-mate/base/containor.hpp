
#pragma once

#include <assert.h>
#include <string>
#include <vector>
#include <algorithm>

#include "element.hpp"

namespace gui {

// contains other elements
class Containor : public Element {
public:
    using Element::Element;
    virtual ~Containor(){
        for(Element* i : this->children)
            delete i;
    }

    virtual void Draw() const {
        for(const Element* i : this->children)
            i->Draw();
    }

    std::pair<int, int> offset = {0, 0};
    std::pair<int, int> size = {0, 0};
    virtual std::pair<int, int> GetOffset() const { return this->offset; }
    virtual std::pair<int, int> GetSize() const { return this->size; }
    virtual void SetOffset(const std::pair<int, int>& value) { this->offset = value; }
    virtual void SetSize(const std::pair<int, int>& value) { this->size = value; }
    virtual Element* WithinCollision(const std::pair<int, int>& mouse_pos) {
        for(auto i = this->children.rbegin(); i != this->children.rend(); i++)
            if (Element* col = (*i)->WithinCollision(mouse_pos))
                return col;
        return nullptr;
    }


    virtual std::string_view GetName() const { return "containor"; }


    // Use for Containors and managing elements
    void Add(Element* element) { // Simply add an element
        assert(element);
        auto find = this->Find(element);
        if (find != this->children.end())
            throw std::runtime_error("Element already exists within the containor");
        this->children.push_back(element);
    }
    void Remove(Element* element) { // Remove an element
        assert(element);
        auto find = this->Find(element);
        if (find == this->children.end())
            throw std::runtime_error("Unable to find specified element");
        this->children.erase(find);
    }
    void Remove(std::string_view element_name){
        auto find = this->Find(element_name);
        if (find == this->children.end())
            throw std::runtime_error("Unable to find specified element");
        this->children.erase(find);
    }
    void PutOnTop(Element* element) { // Put an element on top of everything else
        assert(element);
        this->Remove(element);
        this->children.push_back(element);
    }
    std::vector<Element*>::iterator Find(Element* element){
        return std::find(this->children.begin(), this->children.end(), element);
    }
    std::vector<Element*>::iterator Find(std::string_view element_name){
        return std::find_if(this->children.begin(), this->children.end(), [&](Element* element) { return element->GetName() == element_name; });
    }
protected:
    std::vector<Element*> children; // Ordering of this is whatever is at the end is on "top"
};

}
