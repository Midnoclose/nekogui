
#include "lib/xoverlay.h"
#include "../libglez/include/glez/glez.hpp"
#include "../libglez/include/glez/draw.hpp"

#include "input.hpp"

namespace draw = glez::draw;
int main() {
    xoverlay_init();
    glez::preInit();
    glez::init(xoverlay_library.width, xoverlay_library.height);

    xoverlay_show();
    while (1) {
        input::RefreshInput();
        // Must be called in that order.
        xoverlay_draw_begin();
        glez::begin(); {

            draw::rect(100, 300, 200, 100, glez::rgba(255, 0, 128, 255));
            auto mouse = input::GetMouse();
            draw::rect(mouse.first - 6, mouse.second - 6, 12, 12, glez::rgba(255, 0, 128, 255));

        } glez::end();
        xoverlay_draw_end();
    }
    return 0;
}
