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

void GLTexture::draw(unsigned char *datas[], int width, int height) {
    glShader.getTexture(0, width, height, datas[0]); //Y
    glShader.getTexture(1, width/2, height/2, datas[1]); //U
    glShader.getTexture(2, width/2, height/2, datas[2]); //V
    glShader.draw();

}
