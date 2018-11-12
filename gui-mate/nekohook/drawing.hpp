
#pragma once

#include "../../libglez/include/glez/color.hpp"
using CatColor = glez::rgba;

#include "functional.hpp"

namespace events {
inline cat::FastEvent<> draw;
}
namespace draw {

constexpr int default_font = 0;
constexpr int default_font_size = 0;

// Check drawing.cpp for proper args
void Line(int x, int y, int w, int h, CatColor);
void Rect(int x, int y, int w, int h, CatColor);
void RectFilled(int x, int y, int w, int h, CatColor);

// Draw string and get length, returns length of widthxheight
void String(const char* text, int x, int y, int font, int font_size, CatColor);
std::pair<int, int> GetStringLength(const char* text, int font, int font_size);

}

namespace colors {
    const CatColor white = CatColor(255, 255, 255);
    const CatColor black = CatColor(0, 0, 0);
    const CatColor pink = CatColor(255, 105, 180);
    const CatColor red = CatColor(237, 42, 42);
    const CatColor blue = CatColor(28, 108, 237);
    const CatColor yellow = CatColor(255, 255, 0);
    const CatColor orange = CatColor(255, 120, 0);
    const CatColor green = CatColor(0, 255, 0);
    const CatColor gray = CatColor(100, 100, 100);
    const CatColor lightgray = CatColor(180, 180, 180);
    const CatColor darkgray = CatColor(50, 50, 50);
    const CatColor empty = CatColor(0, 0, 0, 0);
}
