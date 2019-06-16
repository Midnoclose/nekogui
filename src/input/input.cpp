
/*
 * Nekogui: Dumb ways to do existing things
 * Copyright (C) 2018 Rebekah Rowe
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <cassert>
#include <iostream>
#include <bitset>
#if __linux__
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#endif

#include "input/input.hpp"

namespace neko::gui::keys {

static const std::string_view key_names[] = {
    "NONE",        "0",
    "1",           "2",
    "3",           "4",
    "5",           "6",
    "7",           "8",
    "9",           "A",
    "B",           "C",
    "D",           "E",
    "F",           "G",
    "H",           "I",
    "J",           "K",
    "L",           "M",
    "N",           "O",
    "P",           "Q",
    "R",           "S",
    "T",           "U",
    "V",           "W",
    "X",           "Y",
    "Z",

    "ESCAPE",      "LBRACKET",
    "RBRACKET",    "SEMICOLON",
    "APOSTROPHE",  "BACKQUOTE",
    "COMMA",       "PERIOD",
    "SLASH",       "BACKSLASH",
    "MINUS",       "EQUAL",
    "ENTER",       "SPACE",
    "BACKSPACE",   "TAB",
    "CAPSLOCK",

    "INSERT",      "DELETE",
    "HOME",        "END",
    "PAGEUP",      "PAGEDOWN",

    "LSHIFT",      "RSHIFT",
    "LALT",        "RALT",
    "LCONTROL",    "RCONTROL",

    "PAD_0",       "PAD_1",
    "PAD_2",       "PAD_3",
    "PAD_4",       "PAD_5",
    "PAD_6",       "PAD_7",
    "PAD_8",       "PAD_9",

    "PAD_DIVIDE",  "PAD_MULTIPLY",
    "PAD_MINUS",   "PAD_PLUS",
    "PAD_ENTER",   "PAD_DECIMAL",

    "UP",          "LEFT",
    "DOWN",        "RIGHT",

    "F1",          "F2",
    "F3",          "F4",
    "F5",          "F6",
    "F7",          "F8",
    "F9",          "F10",
    "F11",         "F12",

    "MOUSE_1",     "MOUSE_2",
    "MOUSE_3",     "MOUSE_4",
    "MOUSE_5",
    "M_WHEEL_UP", "M_WHEEL_DOWN"
};

std::string_view GetName(Key k){
    std::size_t pos = static_cast<std::size_t>(k);
    assert(pos > 0 && pos < static_cast<std::size_t>(Key::kCount));
    return key_names[pos];
}

// xlib
#if __linux__

static Display* xconnection;
static void __attribute__((constructor)) Init() {
     xconnection = XOpenDisplay(nullptr);
     if (!xconnection)
        std::cerr << "Nekogui: Unable to retrieve display" << std::endl;
}
static void __attribute__((destructor)) DeInit() {
    if (xconnection)
        XCloseDisplay(xconnection);
}

// /usr/include/X11/keysymdef.h
static const std::pair<int, Key> key_map[] = {
    {XK_0, Key::k0},
    {XK_1, Key::k1},
    {XK_2, Key::k2},
    {XK_3, Key::k3},
    {XK_4, Key::k4},
    {XK_5, Key::k5},
    {XK_6, Key::k6},
    {XK_7, Key::k7},
    {XK_8, Key::k8},
    {XK_9, Key::k9},
    {XK_A, Key::kA},
    {XK_B, Key::kB},
    {XK_C, Key::kC},
    {XK_D, Key::kD},
    {XK_E, Key::kE},
    {XK_F, Key::kF},
    {XK_G, Key::kG},
    {XK_H, Key::kH},
    {XK_I, Key::kI},
    {XK_J, Key::kJ},
    {XK_K, Key::kK},
    {XK_L, Key::kL},
    {XK_M, Key::kM},
    {XK_N, Key::kN},
    {XK_O, Key::kO},
    {XK_P, Key::kP},
    {XK_Q, Key::kQ},
    {XK_R, Key::kR},
    {XK_S, Key::kS},
    {XK_T, Key::kT},
    {XK_U, Key::kU},
    {XK_V, Key::kV},
    {XK_W, Key::kW},
    {XK_X, Key::kX},
    {XK_Y, Key::kY},
    {XK_Z, Key::kZ},

    {XK_Escape, Key::kEscape},
    {XK_bracketleft, Key::kLBracket},
    {XK_bracketright, Key::kRBracket},
    {XK_semicolon, Key::kSemicolon},
    {XK_apostrophe, Key::kApostrophe},
    {XK_apostrophe, Key::kComma},
    {XK_period, Key::kPeriod},
    {XK_slash, Key::kSlash},
    {XK_backslash, Key::kBackslash},
    {XK_minus, Key::kHyphen},
    {XK_equal, Key::kEqual},
    {XK_Return, Key::kEnter},
    {XK_space, Key::kSpace},
    {XK_BackSpace, Key::kBackspace},
    {XK_Tab, Key::kTab},
    {XK_Caps_Lock, Key::kCapslock},

    {XK_Insert, Key::kInsert},
    {XK_Delete, Key::kDelete},
    {XK_Home, Key::kHome},
    {XK_End, Key::kEnd},
    {XK_Page_Up, Key::kPageUp},
    {XK_Page_Down, Key::kPageDown},

    {XK_Shift_L, Key::kLShift},
    {XK_Shift_R, Key::kRShift},
    {XK_Alt_L, Key::kLAlt},
    {XK_Alt_R, Key::kRAlt},
    {XK_Control_L, Key::kLControl},
    {XK_Control_R, Key::kRControl},

    {XK_KP_0, Key::kPad0},
    {XK_KP_1, Key::kPad1},
    {XK_KP_2, Key::kPad2},
    {XK_KP_3, Key::kPad3},
    {XK_KP_4, Key::kPad4},
    {XK_KP_5, Key::kPad5},
    {XK_KP_6, Key::kPad6},
    {XK_KP_7, Key::kPad7},
    {XK_KP_8, Key::kPad8},
    {XK_KP_9, Key::kPad9},

    {XK_KP_Divide, Key::kPadDivide},
    {XK_KP_Multiply, Key::kPadMultiply},
    {XK_KP_Subtract, Key::kPadMinus},
    {XK_KP_Add, Key::kPadPlus},
    {XK_KP_Enter, Key::kPadEnter},
    {XK_KP_Decimal, Key::kPadPeriod},

    {XK_Up, Key::kUp},
    {XK_Left, Key::kLeft},
    {XK_Down, Key::kDown},
    {XK_Right, Key::kRight},

    {XK_F1, Key::kF1},
    {XK_F2, Key::kF2},
    {XK_F3, Key::kF3},
    {XK_F4, Key::kF4},
    {XK_F5, Key::kF5},
    {XK_F6, Key::kF6},
    {XK_F7, Key::kF7},
    {XK_F8, Key::kF8},
    {XK_F9, Key::kF9},
    {XK_F10, Key::kF10},
    {XK_F11, Key::kF11},
    {XK_F12, Key::kF12},

    {XK_Pointer_DfltBtnPrev, Key::kMWheelUp},
    {XK_Pointer_DfltBtnNext, Key::kMWheelDown}};
#endif

std::unordered_set<Key> GetKeymap() {

#if __linux__
    std::bitset<32 * 8> key_states;
    XQueryKeymap(xconnection, reinterpret_cast<char*>(&key_states));

    std::unordered_set<Key> ret;
	for (const auto& i : key_map) {
        int key_code = XKeysymToKeycode(xconnection, i.first);
        if (key_states[key_code])
            ret.insert(i.second);
    }
    return ret;
#endif
}
bool Test(Key k) {
    auto keymap = GetKeymap();
    return keymap.find(k) != keymap.end();
}

}
