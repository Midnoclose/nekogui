
#include "../libglez/include/glez/draw.hpp"

#include "../gui-mate/nekohook/drawing.hpp"

namespace draw {

//constexpr int default_font = 0;
//constexpr int default_font_size = 0;

// Check drawing.cpp for proper args
void Line(int x, int y, int w, int h, CatColor color){
    glez::draw::line(x, y, w, h, color, 1);
}
void Rect(int x, int y, int w, int h, CatColor color){
    glez::draw::rect_outline(x, y, w, h, color, 1);
}
void RectFilled(int x, int y, int w, int h, CatColor color) {
    glez::draw::rect(x, y, w, h, color);
}

glez::font using_font("res/opensans.ttf", 16);
// Draw string and get length, returns length of widthxheight
void String(const char* text, int x, int y, int font, int font_size, CatColor clr) {
    glez::draw::outlined_string(x, y, text, using_font, clr, colors::black, nullptr, nullptr);
}
std::pair<int, int> GetStringLength(const char* text, int font, int font_size){
    float x, y;
    using_font.stringSize(text, &x, &y);
    return {x, y};
}

}
