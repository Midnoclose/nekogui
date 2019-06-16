
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

#if defined(__linux__)
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#endif

#include "containor.hpp"

namespace neko::gui {

class RealWindow : public Containor {
public:
    RealWindow(const Vec2d& size);
    ~RealWindow() override;
private:
    void Draw();
    void Draw(const Vec2d&) const override;
#if defined(__linux__)
    Display *display;
    Window window;
    GLXContext context;
    GLXFBConfig GetFBConfig();
    GLXContext GetContext(GLXFBConfig* fb_config);
#endif
};


}
