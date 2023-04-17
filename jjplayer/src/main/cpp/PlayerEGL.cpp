//
// Created by JJLeong on 2023/4/9.
//

#include "PlayerEGL.h"

IEGL *PlayerEGL::get() {
    static PlayerEGL playerEgl;
    return &playerEgl;
}

bool PlayerEGL::init(void *window) {
    ANativeWindow *nativeWindow = static_cast<ANativeWindow *>(window);

    //初始化EGL
    //1、获取EGLDisplay对象
    eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (eglDisplay == EGL_NO_DISPLAY){
        LOGE("eglGetDisplay fail.");
        return false;
    }

    //2、初始化EGLDisplay对象
    if (EGL_TRUE != eglInitialize(eglDisplay, 0, 0)){
        LOGE("eglInitialize fail.");
        return false;
    }

    //3、获取配置并创建EGLSurface
    EGLint configSpec[] = {
            EGL_RED_SIZE,8,
            EGL_GREEN_SIZE,8,
            EGL_BLUE_SIZE,8,
            EGL_SURFACE_TYPE,EGL_WINDOW_BIT,
            EGL_NONE
    };
    EGLConfig eglConfig = 0;
    EGLint numConfig = 0;
    if (EGL_TRUE != eglChooseConfig(eglDisplay, configSpec, &eglConfig, 1, &numConfig)){
        LOGE("eglChooseConfig fail.");
        return false;
    }
    eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, nativeWindow, NULL);

    //4、创建并打开EGL上下文
    const EGLint attrib[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
    eglContext = eglCreateContext(eglDisplay, eglConfig, EGL_NO_CONTEXT, attrib);
    if (eglConfig == EGL_NO_CONTEXT){
        LOGE("eglCreateContext fail.");
        return false;
    }

    if (EGL_TRUE != eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext)){
        LOGE("eglMakeCurrent fail.");
        return false;
    }

    return true;
}

void PlayerEGL::draw() {
    if (eglDisplay == EGL_NO_DISPLAY || eglSurface == EGL_NO_SURFACE){
        return;
    }
    //把surface数据中的buffer交换到显示设备中来
    eglSwapBuffers(eglDisplay, eglSurface);
}
