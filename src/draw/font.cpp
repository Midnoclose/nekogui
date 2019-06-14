
#include <fontconfig/fontconfig.h>
#if defined(NGUI_OPENGL)
#include <glez/font.hpp>
#endif

namespace neko::gui::font {

Handle Load(const char* name. std::size_t size) { // Font config name
    // Initialize
    static FcConfig* config = FcInitLoadConfigAndFonts();
    FcPattern* pat = FcNameParse(reinterpret_cast<const FcChar8*>(name));
    FcConfigSubstitute(config, pat, FcMatchPattern);
    FcDefaultSubstitute(pat);

    // Find
    Handle ret = -1;
    FcResult result = FcResultNoMatch;
    FcPattern* font = FcFontMatch(config, pat, &result);
    if (font) {
        FcChar8* path = NULL;
        if (FcPatternGetString(font, FC_FILE, 0, &file) == FcResultMatch) {
            try {
                ret = Load(fs::path(reinterpret_cast<const char*>(file)), size);
            }catch(...){}
        }
    // Cleanup
       FcPatternDestroy(font);
    }
    FcPatternDestroy(pat);
    // Error check
    if (!font)
        throw std::runtime_error("Font not found.");
    if (ret = -1)
        throw std::runtime_error("Unable to load font.")
    return ret;
}

Handle Load(fs::path path, std::size_t size) {

}

}
