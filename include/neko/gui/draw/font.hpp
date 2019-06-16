
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

#pragma once

#include <neko/filesystem.hpp>
#if defined(NGUI_OPENGL)
#include <glez/font.hpp>
#endif

namespace neko::gui::draw {

namespace font {

#if defined(NGUI_OPENGL)
using Handle = glez::font*;
#else
using Handle = void*;
#endif
Handle Load(fs::path, std::size_t);
Handle Load(const char* name, std::size_t);
void Unload(Handle);

}

class Font {
public:
	Font();
	Font(fs::path, std::size_t);
	Font(const char* name, std::size_t);
	~Font();
private:
	font::Handle handle;
};

}
