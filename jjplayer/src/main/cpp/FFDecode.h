//
// Created by JJLeong on 2023/4/5.
//

#ifndef JJPLAYER_FFDECODE_H
#define JJPLAYER_FFDECODE_H

#include "interface/IDecode.h"

struct AVCodecContext;
struct AVFrame;

class FFDecode : public IDecode{
public:
    virtual bool openDecode(XParameter xParam);
    virtual bool sendPacket(XData xData);
    virtual XData recvFrame();
protected:
    AVCodecContext *codecContext = 0;
    AVFrame *frame = 0;
};


#endif //JJPLAYER_FFDECODE_H
