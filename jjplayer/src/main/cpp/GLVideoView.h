//
// Created by JJLeong on 2023/4/9.
//

#ifndef JJPLAYER_GLVIDEOVIEW_H
#define JJPLAYER_GLVIDEOVIEW_H


#include "interface/IVideoView.h"

class ITexture;

class GLVideoView : public IVideoView{
public:
    virtual void setRender(void *window);
    virtual void render(XData data);
protected:
    void *view = 0;
    ITexture *texture = 0;
};


#endif //JJPLAYER_GLVIDEOVIEW_H
