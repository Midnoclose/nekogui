
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

#include <fontconfig/fontconfig.h>

#include "draw/font.hpp"

namespace neko::gui::draw {

namespace font {
Handle Load(const char* name, std::size_t size) { // Font config name
    // Initialize
    static FcConfig* config = FcInitLoadConfigAndFonts();
    FcPattern* pat = FcNameParse(reinterpret_cast<const FcChar8*>(name));
    FcConfigSubstitute(config, pat, FcMatchPattern);
    FcDefaultSubstitute(pat);

    // Find
    Handle ret = 0;
    FcResult result = FcResultNoMatch;
    FcPattern* font = FcFontMatch(config, pat, &result);
    if (font) {
        FcChar8* path = nullptr;
        if (FcPatternGetString(font, FC_FILE, 0, &path) == FcResultMatch) {
            try {
                ret = Load(fs::path(reinterpret_cast<const char*>(path)), size);
            }catch(...){
                ret = 0;
            }
        }
    // Cleanup
       FcPatternDestroy(font);
    }
    FcPatternDestroy(pat);
    // Error check
    if (!font)
        throw std::runtime_error("Font not found.");
    if (!ret)
        throw std::runtime_error("Unable to load font.");
    return ret;
}

Handle Load(fs::path path, std::size_t size) {
    #if defined(NGUI_OPENGL)
        return new OGLFT::Monochrome(path.c_str(), size);
    #else
        #pragma message("Fonts not avaiable!")
    #endif
}

void Unload(Handle h) {
    #if defined(NGUI_OPENGL)
        delete h;
    #endif
}
}

Font::Font() : Font("Monospace", 15) {};
Font::Font(fs::path p, std::size_t s) {
    this->handle = font::Load(p, s);
}
Font::Font(const char* name, std::size_t s) {
    this->handle = font::Load(name, s);
}
Font::~Font() {
    font::Unload(this->handle);
}

}
