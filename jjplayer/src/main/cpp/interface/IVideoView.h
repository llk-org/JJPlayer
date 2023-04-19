//
// Created by JJLeong on 2023/4/9.
//

#ifndef JJPLAYER_IVIDEOVIEW_H
#define JJPLAYER_IVIDEOVIEW_H


#include "../bean/XData.h"
#include "IObserver.h"

class IVideoView : public IObserver{
public:
    virtual void setRender(void *window) = 0;
    virtual void render(XData data) = 0;
    virtual void updateData(XData data);
};


#endif //JJPLAYER_IVIDEOVIEW_H
