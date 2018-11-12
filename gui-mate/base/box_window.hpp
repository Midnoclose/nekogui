
#pragma once

#include "../nekohook/drawing.hpp"

#include "../root.hpp"

namespace gui {

// TODO: we need a way to do pressed, how do we get what is pressed
class BoxWindow : public Containor {
public:
    BoxWindow(std::string_view _name = "box_window") : Containor(&GetRoot()) {
        Root::Add(this);
    }
    virtual ~BoxWindow(){
        Root::Remove(this);
    }

    virtual void Draw() const {
        std::pair<int, int> abs = this->GetAbsPos();
        std::pair<int, int> size = this->GetSize();
        draw::RectFilled(abs.first, abs.second, size.first, size.second, GetBackgroundColor());
        draw::Rect(abs.first, abs.second, size.first, size.second, GetOutlineColor());

        this->Containor::Draw();
    }

    virtual void MouseEvent(const std::pair<int, int>& mouse_pos, const std::pair<int, int>& move_delta) {
        this->SetOffset(this->GetOffset() + move_delta);
    }

    virtual Element* WithinCollision(const std::pair<int, int>& mouse_pos) {
        if (Element* ret = this->Containor::WithinCollision(mouse_pos))
            return ret;
        return this->Element::WithinCollision(mouse_pos);
    }
};

}
