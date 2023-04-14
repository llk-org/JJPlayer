//
// Created by JJLeong on 2023/4/9.
//

#ifndef JJPLAYER_IVIDEOVIEW_H
#define JJPLAYER_IVIDEOVIEW_H


#include "../bean/XData.h"

class IVideoView {
public:
    virtual void setRender(void *window) = 0;
    virtual void render(XData data) = 0;
    virtual void update(XData data);
};


#endif //JJPLAYER_IVIDEOVIEW_H
