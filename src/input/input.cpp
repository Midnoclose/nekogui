
namespace neko::gui {

static xcb_connection_t* xconnection = xcb_connect(NULL, NULL);
static void __attribute__((destructor)) DeInit() {
    xcb_disconnect(xconnection);
}

Key::Key(char _k) : k(_k) {}
Key::Key(char _k, std::string_view special) : Key(_k) {
    for (char s : special) {
        if (c == 'c')
            this->ctrl = true;
        else if (c == 's')
            this->shift = true;
        else if (c == 'a')
            this->alt = true;
    }
}
}
Key::Key(char _k, std::initializer_list<std::string_view> special) : Key(_k){
    for (std::string_view s : special) {
        if (s == "ctrl")
            this->ctrl = true;
        else if (s == "shift")
            this->shift = true;
        else if (s == "alt")
            this->alt = true;
    }
}
Key::Key(char _k, std::string_view special) : Key(_k) {}
Key::Key(char _k, std::initializer_list<std::string_view> special) : Key(_k){
    for (std::string_view s : special) {
        if (s == "ctrl")
            this->ctrl = true;
        else if (s == "shift")
            this->shift = true;
        else if (s == "alt")
            this->alt = true;
    }
}

bool Key::Test() {
    xcb_query_keymap_cookie_t cookie  = xcb_query_keymap(xconnection);
    xcb_generic_error_t* err;
    xcb_query_keymap_reply_t *xcb_query_keymap_reply(xconnection, cookie, &err);
}
