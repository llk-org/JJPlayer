//
// Created by JJLeong on 2023/4/9.
//

#ifndef JJPLAYER_PLAYEREGL_H
#define JJPLAYER_PLAYEREGL_H

#include "interface/IEGL.h"
#include <android/native_window_jni.h>
#include <EGL/egl.h>
#include "utils/Log.h"

class PlayerEGL : public IEGL{
private:
    EGLDisplay eglDisplay = EGL_NO_DISPLAY;
    EGLSurface eglSurface = EGL_NO_SURFACE;
    EGLContext eglContext = EGL_NO_CONTEXT;
public:
    static IEGL *get();
    virtual bool init(void *window);
};


#endif //JJPLAYER_PLAYEREGL_H
