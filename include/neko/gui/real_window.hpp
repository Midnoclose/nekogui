
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

struct xcb_connection_t;
class RealWindow : public Element {
public:
    RealWindow() {
        this->connection = xcb_connect(NULL, NULL);

        const xcb_setup_t* setup  = xcb_get_setup(connection);
        xcb_screen_iterator_t iter = xcb_setup_roots_iterator(setup);
        xcb_screen_t* screen = iter.data;
        this->window = xcb_generate_id (connection);
    }
    ~RealWindow() {
        xcb_disconnect(this->connection);
    }
    void Draw(){

    }
    void Add(Element*) {

    }
private:
    std::unordered_set<Element*> elements;
    xcb_connection_t* connection;
    xcb_window_t window
};


/* Get the first screen */



        /* Create the window */

        xcb_create_window (connection,                    /* Connection          */
                           XCB_COPY_FROM_PARENT,          /* depth (same as root)*/
                           window,                        /* window Id           */
                           screen->root,                  /* parent window       */
                           0, 0,                          /* x, y                */
                           150, 150,                      /* width, height       */
                           10,                            /* border_width        */
                           XCB_WINDOW_CLASS_INPUT_OUTPUT, /* class               */
                           screen->root_visual,           /* visual              */
                           0, NULL );                     /* masks, not used yet */


        /* Map the window on the screen */
        xcb_map_window (connection, window);


        /* Make sure commands are sent before we pause so that the window gets shown */
        xcb_flush (connection);


        pause ();    /* hold client until Ctrl-C */

        xcb_disconnect (connection);
