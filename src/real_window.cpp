
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
#include <iostream>
#include <neko/string.hpp>

#include "real_window.hpp"

namespace neko::gui {

#if defined(__linux__)
// https://www.khronos.org/opengl/wiki/Tutorial:_OpenGL_3.0_Context_Creation_(GLX)
RealWindow::RealWindow(const Vec2d& size) : Containor(this) {

    this->display = XOpenDisplay(nullptr);
    if (!this->display)
        throw std::runtime_error("unable to retrieve display");
    Window root = DefaultRootWindow(this->display);

    // Pick the FB config/visual with the most samples per pixel
    GLXFBConfig fb_config = this->GetFBConfig();
    XVisualInfo* visual_info = glXGetVisualFromFBConfig(this->display, fb_config);

    // Create our window
    Colormap color_map = XCreateColormap(this->display, root, visual_info->visual, AllocNone);
    XSetWindowAttributes window_attr;
    window_attr.colormap          = color_map;
    window_attr.background_pixmap = None;
    window_attr.border_pixel      = 0;
    window_attr.event_mask        = StructureNotifyMask;
    this->window = XCreateWindow(this->display, root,
                                  0, 0, 100, 100, 0, visual_info->depth, InputOutput,
                                  visual_info->visual,
                                  CWBorderPixel|CWColormap|CWEventMask, &window_attr );
    XFree(visual_info);
    if (!this->window)
        throw std::runtime_error("Failed to create window");
    XMapWindow(this->display, this->window);

    // Setup context
    this->context = this->GetContext(&fb_config);
    if (!this->context)
        throw std::runtime_error("Failed to get gl context");

    glXMakeCurrent(this->display, this->window, this->context);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    //glXSwapIntervalEXT(this->display, this->window, 0);
    glXSwapBuffers(this->display, this->window);
}


RealWindow::~RealWindow() {
    XDestroyWindow(this->display, this->window);
    XCloseDisplay(this->display);
}

void RealWindow::Draw() {
    this->Draw({0, 0});
}
void RealWindow::Draw(const Vec2d& offset) const {
    //glXMakeCurrent(this->display, this->window, glx_state.context);
    glClear(GL_COLOR_BUFFER_BIT);
    this->Containor::Draw(offset);
    glXSwapBuffers(this->display, this->window);
}

GLXFBConfig RealWindow::GetFBConfig() {
    static GLint visual_attr[] = { GLX_X_RENDERABLE,  GL_TRUE,
                 GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
                 GLX_RENDER_TYPE,   GLX_RGBA_BIT,
                 GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
                 GLX_DEPTH_SIZE,   24,
                 GLX_STENCIL_SIZE, 8,
                 GLX_RED_SIZE,     8,
                 GLX_GREEN_SIZE,   8,
                 GLX_BLUE_SIZE,    8,
                 GLX_ALPHA_SIZE,   8,
                 GLX_DOUBLEBUFFER, GL_TRUE,
                 None };
    // Get a list of avaiable configs
    int end;
    GLXFBConfig* fb_configs = glXChooseFBConfig(this->display, DefaultScreen(this->display), visual_attr, &end);
    if (!fb_configs)
        throw std::runtime_error("Failed to retrieve a framebuffer configs");

    // Pick the FB config/visual with the most samples per pixel
    int best_config = -1, best_samples = -1;
    for (int i = 0; i < end; i++) {
        XVisualInfo* vi = glXGetVisualFromFBConfig(this->display, fb_configs[i]);
        if (!vi || vi->depth != 32)
            continue;
        int samples;
        glXGetFBConfigAttrib(this->display, fb_configs[i], GLX_SAMPLES, &samples);
        if (samples > best_samples || best_config < 0)
          best_config = i, best_samples = samples;
        XFree(vi);
    }
    if (best_config == -1)
        throw std::runtime_error("Failed to find a valid framebuffer config");

    GLXFBConfig ret = fb_configs[best_config];
    XFree(fb_configs);
    return ret;
}

GLXContext RealWindow::GetContext(GLXFBConfig* fb_config){
    auto extentions = sepstr(glXQueryExtensionsString(this->display, DefaultScreen(this->display)));
    for(auto& i : extentions) {
        std::cout << i << std::endl;
    }
    auto find = std::find(extentions.begin(), extentions.end(), "GLX_ARB_create_context");
    if (find != extentions.end())
        return glXCreateNewContext(this->display, *fb_config, GLX_RGBA_TYPE, NULL, GL_TRUE);
    else {
        find = std::find(extentions.begin(), extentions.end(), "glXCreateContextAttribsARB");
        if (find != extentions.end()) {

            using CreateCtxAttrARBFn = GLXContext(*)(Display*, GLXFBConfig, GLXContext, Bool, const int*);
            CreateCtxAttrARBFn glXCreateContextAttribsARB
                = reinterpret_cast<CreateCtxAttrARBFn>(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glXCreateContextAttribsARB")));
            int ctx_attribs[] = { GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
                                  GLX_CONTEXT_MINOR_VERSION_ARB, 0, None };
            GLXContext ret = glXCreateContextAttribsARB(this->display, *fb_config, NULL, GL_TRUE, ctx_attribs);
            XSync(this->display, GL_FALSE);
            return ret;
        }
    }
    throw std::runtime_error("Unable to create gl context");
}

#endif

}
