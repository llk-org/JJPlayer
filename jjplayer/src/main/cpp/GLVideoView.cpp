//
// Created by JJLeong on 2023/4/9.
//

#include "GLVideoView.h"
#include "GLTexture.h"

void GLVideoView::setRender(void *window) {
    view = window;
}

void GLVideoView::render(XData data) {
    if(!view) return;

    if(!texture){
        texture = GLTexture::makeTexture();
        texture->init(view);
    }
}
