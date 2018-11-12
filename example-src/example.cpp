
/*
 *
 * Example to make gui work by emulating nekohook
 *
 */

//Stuff for use in example
#include "lib/xoverlay.h"
#include "../libglez/include/glez/glez.hpp"
#include "../libglez/include/glez/draw.hpp"
#include "../gui-mate/nekohook/drawing.hpp"

// GUI SHIT
#include "../gui-mate/root.hpp"
#include "../gui-mate/base/box_window.hpp"
#include "../gui-mate/base/text_box.hpp"
#include "../gui-mate/base/real_window.hpp"

#include "input.hpp"

int main() {
    // Init example drawing platform
    xoverlay_init();
    glez::preInit();
    glez::init(xoverlay_library.width, xoverlay_library.height);

    // INIT GUI!!!
    gui::Init();

    std::function<void()> MakeWindow = [&](){
        // Make our window
        gui::RealWindow* test_window = new gui::RealWindow("test1", true);
        test_window->SetSize({400, 200});
        test_window->SetOffset({200,200});

        //Button* twinks = new Button(test_window, "twiddles", MakeWindow);
        //test_window->contents.PutOnTop(twinks);
    };
    MakeWindow();

    // Make our window
    gui::BoxWindow test_window2{"diks uwu"};
    test_window2.SetSize({200, 100});
    test_window2.SetOffset({100,100});

    std::string diks = "cuntnuggs";
    gui::TextInputBox box(&test_window2, diks);
    test_window2.Add(&box);
    box.SetSize({200, 100});

    xoverlay_show();
    for(;;) {
        xoverlay_draw_begin();
        glez::begin(); {

            // Run the events
            input::RefreshInput();
            events::draw.Emit();

        } glez::end();
        xoverlay_draw_end();
    }
    return 0;
}
