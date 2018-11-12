
#include <X11/Xutil.h> // For xlibs keycodes, window geometry
#include <bitset> // For caching pressed keys

#include "lib/xoverlay.h"

#include "input.hpp"

namespace input {

// Stores potential conversions between xlib's keycodes and cathooks catkeys. Add more as nessesary! /usr/include/X11/keysymdef.h
static const std::pair<int, CatKey> xlibToCatVar[] = {
	{XK_0, CatKey::k0}, {XK_1, CatKey::k1}, {XK_2, CatKey::k2},
	{XK_3, CatKey::k3}, {XK_4, CatKey::k4}, {XK_5, CatKey::k5},
	{XK_6, CatKey::k6}, {XK_7, CatKey::k7}, {XK_8, CatKey::k8},
	{XK_9, CatKey::k9}, {XK_A, CatKey::kA}, {XK_B, CatKey::kB},
	{XK_C, CatKey::kC}, {XK_D, CatKey::kD}, {XK_E, CatKey::kE},
	{XK_F, CatKey::kF}, {XK_G, CatKey::kG}, {XK_H, CatKey::kH},
	{XK_I, CatKey::kI}, {XK_J, CatKey::kJ}, {XK_K, CatKey::kK},
	{XK_L, CatKey::kL}, {XK_M, CatKey::kM}, {XK_N, CatKey::kN},
	{XK_O, CatKey::kO}, {XK_P, CatKey::kP}, {XK_Q, CatKey::kQ},
	{XK_R, CatKey::kR}, {XK_S, CatKey::kS}, {XK_T, CatKey::kT},
	{XK_U, CatKey::kU}, {XK_V, CatKey::kV}, {XK_W, CatKey::kW},
	{XK_X, CatKey::kX}, {XK_Y, CatKey::kY}, {XK_Z, CatKey::kZ},

	{XK_Escape, CatKey::kEscape}, {XK_bracketleft, CatKey::kLBracket},
	{XK_bracketright, CatKey::kRBracket}, {XK_semicolon, CatKey::kSemicolon},
	{XK_apostrophe, CatKey::kApostrophe}, {XK_apostrophe, CatKey::kComma},
	{XK_period, CatKey::kPeriod}, {XK_slash, CatKey::kSlash},
	{XK_backslash, CatKey::kBackslash}, {XK_minus, CatKey::kHyphen},
	{XK_equal, CatKey::kEqual}, {XK_Return, CatKey::kEnter},
	{XK_space, CatKey::kSpace}, {XK_BackSpace, CatKey::kBackspace},
	{XK_Tab, CatKey::kTab}, {XK_Caps_Lock, CatKey::kCapslock},

	{XK_Insert, CatKey::kInsert}, {XK_Delete, CatKey::kDelete},
	{XK_Home, CatKey::kHome}, {XK_End, CatKey::kEnd},
	{XK_Page_Up, CatKey::kPageUp}, {XK_Page_Down, CatKey::kPageDown},

	{XK_Shift_L, CatKey::kLShift}, {XK_Shift_R, CatKey::kRShift},
	{XK_Alt_L, CatKey::kLAlt}, {XK_Alt_R, CatKey::kRAlt},
	{XK_Control_L, CatKey::kLControl}, {XK_Control_R, CatKey::kRControl},

	{XK_KP_0, CatKey::kPad0}, {XK_KP_1, CatKey::kPad1}, {XK_KP_2, CatKey::kPad2},
	{XK_KP_3, CatKey::kPad3}, {XK_KP_4, CatKey::kPad4}, {XK_KP_5, CatKey::kPad5},
	{XK_KP_6, CatKey::kPad6}, {XK_KP_7, CatKey::kPad7}, {XK_KP_8, CatKey::kPad8},
	{XK_KP_9, CatKey::kPad9},

	{XK_KP_Divide, CatKey::kPadDivide}, {XK_KP_Multiply, CatKey::kPadMultiply},
	{XK_KP_Subtract, CatKey::kPadMinus}, {XK_KP_Add, CatKey::kPadPlus},
	{XK_KP_Enter, CatKey::kPadEnter}, {XK_KP_Decimal, CatKey::kPadPeriod},

	{XK_Up, CatKey::kUp}, {XK_Left, CatKey::kLeft},
	{XK_Down, CatKey::kDown}, {XK_Right, CatKey::kRight},

	{XK_F1, CatKey::kF1}, {XK_F2, CatKey::kF2}, {XK_F3, CatKey::kF3},
	{XK_F4, CatKey::kF4}, {XK_F5, CatKey::kF5}, {XK_F6, CatKey::kF6},
	{XK_F7, CatKey::kF7}, {XK_F8, CatKey::kF8}, {XK_F9, CatKey::kF9},
	{XK_F10, CatKey::kF10}, {XK_F11, CatKey::kF11}, {XK_F12, CatKey::kF12},

	{XK_Pointer_DfltBtnPrev, CatKey::kMWheelUp}, {XK_Pointer_DfltBtnNext, CatKey::kMWheelDown}
};

// Used to store depressed keys
static std::bitset<static_cast<int>(CatKey::kCount)> pressed_buttons;

// Mouse info
static std::pair<int, int> mouse(-1, -1);

// Screen height and width
static std::pair<int, int> bounds(-1, -1);

// Request this to update the input system on button, mouse, and window info
void RefreshInput() {
	if (!xoverlay_library.display || !xoverlay_library.window) return;

	// Get window bounds
	if (xoverlay_library.width != bounds.first || xoverlay_library.height != bounds.second) { // Activate on change
		bounds = std::make_pair(xoverlay_library.width, xoverlay_library.height);
		input::events::bounds.Emit(bounds);
	}

	// Update mouse position
	Window root_return, child_return; int root_x, root_y, mousex, mousey; unsigned int mask_return;
	if (XQueryPointer(xoverlay_library.display, xoverlay_library.window, &root_return, &child_return, &root_x, &root_y, &mousex, &mousey, &mask_return)) { // only update the cursor if this returns true
		if ((mousex != mouse.first || mousey != mouse.second) // Activate on change
		 && (mousex >= 0 && mousey >= 0 && mousex <= bounds.first && mousey <= bounds.second)) { // Clamp positions to the window
			mouse = std::make_pair(mousex, mousey);
			input::events::mouse.Emit(mouse);
		}
		// We did a pointer query so check our buttons too!
		bool s = (mask_return & (Button1Mask));
		if (s != pressed_buttons[static_cast<int>(CatKey::kMouse1)]){
			pressed_buttons[static_cast<int>(CatKey::kMouse1)] = s;
			input::events::key.Emit(CatKey::kMouse1, s);
		}
		s = (mask_return & (Button2Mask));
		if (s != pressed_buttons[static_cast<int>(CatKey::kMouse2)]){
			pressed_buttons[static_cast<int>(CatKey::kMouse2)] = s;
			input::events::key.Emit(CatKey::kMouse2, s);
		}
		s = (mask_return & (Button3Mask));
		if (s != pressed_buttons[static_cast<int>(CatKey::kMouse3)]){
			pressed_buttons[static_cast<int>(CatKey::kMouse3)] = s;
			input::events::key.Emit(CatKey::kMouse3, s);
		}
		// Mouse 4-5 dont work for some reason. XLib doesnt like them...
	}

	// Find depressed keys and save them to the stored map
	char keys[32];
	XQueryKeymap(xoverlay_library.display, keys);
	// Recurse through the map looking for depressed keys
	for (const auto& current : xlibToCatVar) {

		// Get the keycode for the key we are looking for...
		int current_key = XKeysymToKeycode(xoverlay_library.display, current.first);

		// Use the keymap with bitwise logic to get state, oof this took forever to make
		bool pressed = (keys[current_key / 8] & (1 << (current_key % 8)));
		if (pressed != pressed_buttons[static_cast<int>(current.second)]){
			pressed_buttons[static_cast<int>(current.second)] = pressed;
			input::events::key.Emit(current.second, pressed);
		}
	}
}


bool GetKey(CatKey k) {
	return pressed_buttons[static_cast<int>(k)];
}
std::pair<int, int> GetMouse() {
	return mouse;
}
std::pair<int, int> GetBounds() {
	return bounds;
}


}
