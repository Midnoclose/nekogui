
#pragma once

enum class CatKey {
	kNone,
	k0, k1, k2,
	k3, k4, k5,
	k6, k7, k8,
	k9, kA, kB,
	kC, kD, kE,
	kF, kG, kH,
	kI, kJ, kK,
	kL, kM, kN,
	kO, kP, kQ,
	kR, kS, kT,
	kU, kV, kW,
	kX, kY, kZ,

	kEscape, kLBracket,
	kRBracket, kSemicolon,
	kApostrophe, kBackquote,
	kComma, kPeriod, kSlash,
	kBackslash, kHyphen, kEqual,
	kEnter, kSpace, kBackspace,
	kTab, kCapslock,

	kInsert, kDelete, // cant use delete lol
	kHome, kEnd,
	kPageUp, kPageDown,

	kLShift, kRShift,
	kLAlt, kRAlt,
	kLControl, kRControl,

	kPad0, kPad1, kPad2,
	kPad3, kPad4, kPad5,
	kPad6, kPad7, kPad8,
	kPad9,

	kPadDivide, kPadMultiply,
	kPadMinus,  kPadPlus,
	kPadEnter,  kPadPeriod,

	kUp, kLeft,
	kDown, kRight,

	kF1, kF2, kF3,
	kF4, kF5, kF6,
	kF7, kF8, kF9,
	kF10, kF11, kF12,

	kMouse1, kMouse2,
	kMouse3, kMouse4,
	kMouse5,
	kMWheelUp, kMWheelDown,
	kCount
};

#include <utility>
#include <string_view>

#include "functional.hpp"

namespace input {

    // Holds our cat keys as strings
    static inline std::string_view key_names[] = {

        "NONE",
        "0", "1", "2",
        "3", "4", "5",
        "6", "7", "8",
        "9", "A", "B",
        "C", "D", "E",
        "F", "G", "H",
        "I", "J", "K",
        "L", "M", "N",
        "O", "P", "Q",
        "R", "S", "T",
        "U", "V", "W",
        "X", "Y", "Z",

        "ESCAPE",
        "LBRACKET", "RBRACKET",
        "SEMICOLON", "APOSTROPHE",
        "BACKQUOTE", "COMMA",
        "PERIOD", "SLASH",
        "BACKSLASH", "MINUS",
        "EQUAL", "ENTER",
        "SPACE", "BACKSPACE",
        "TAB", "CAPSLOCK",

        "INSERT", "DELETE",
        "HOME", "END",
        "PAGEUP", "PAGEDOWN",

        "LSHIFT", "RSHIFT",
        "LALT", "RALT",
        "LCONTROL", "RCONTROL",

        "PAD_0", "PAD_1", "PAD_2",
        "PAD_3", "PAD_4", "PAD_5",
        "PAD_6", "PAD_7", "PAD_8",
        "PAD_9",

        "PAD_DIVIDE", "PAD_MULTIPLY",
        "PAD_MINUS", "PAD_PLUS",
        "PAD_ENTER", "PAD_DECIMAL",

        "UP", "LEFT",
        "DOWN", "RIGHT",

        "F1", "F2", "F3",
        "F4", "F5", "F6",
        "F7", "F8", "F9",
        "F10", "F11", "F12",

        "MOUSE_1", "MOUSE_2",
        "MOUSE_3", "MOUSE_4",
        "MOUSE_5",
        "M_WHEEL_UP", "M_WHEEL_DOWN"
    };

// Forward defines, meant to be defined by you
bool GetKey(CatKey k);
std::pair<int, int> GetMouse();
std::pair<int, int> GetBounds();

namespace events {

// These are already defined, just use them like normal
extern cat::FastEvent<std::pair<int, int>> bounds;
extern cat::FastEvent<std::pair<int, int>> mouse;
extern cat::FastEvent<CatKey, bool> key;

}

}
