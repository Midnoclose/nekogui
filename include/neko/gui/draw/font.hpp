
/*
 * nGui: Dumb ways to do existing things
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

namespace neko::gui::font {

#if defined(NGUI_HEADLESS)
using Handle = void*;
#elif defined(NGUI_OPENGL)
using Handle = glez::font*;
#endif
Handle Load(fs::path, std::size_t);
Handle Load(const char* name);
void Unload(Handle);

}
