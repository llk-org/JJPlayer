//
// Created by JJLeong on 2023/4/14.
//

#include "GLTexture.h"
#include "utils/Log.h"
#include "PlayerEGL.h"

ITexture *GLTexture::makeTexture() {
    return new GLTexture();
}

bool GLTexture::init(void *window) {
    if(!window){
        LOGE("GLTexture::init fail, window is NULL");
        return false;
    }
    if(PlayerEGL::get()->init(window)) return false;

    glShader.init();

    return true;
}
