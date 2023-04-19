//
// Created by JJLeong on 2023/4/9.
//

#include "GLVideoView.h"
#include "GLTexture.h"
#include "utils/Log.h"

void GLVideoView::setRender(void *window) {
    LOGD("GLVideoView::setRender");
    view = window;
}

void GLVideoView::render(XData data) {
    LOGD("GLVideoView::render size=%d w=%d h=%d", data.size, data.videoWidth, data.videoHeight);
    if(!view) return;

    if(!texture){
        texture = GLTexture::makeTexture();
        texture->init(view);
    }

    texture->draw(data.datas, data.videoWidth, data.videoHeight);
}
