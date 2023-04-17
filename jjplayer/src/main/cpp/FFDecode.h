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
    FFDecode(const char *clazzName);
    virtual bool openDecode(XParameter xParam);
    virtual bool sendPacketToDecoder(XData packet);
    virtual XData receiveFrameFromDecoder();
protected:
    const char *className = 0;
    AVCodecContext *codecContext = 0;
    AVFrame *frame = 0;
};


#endif //JJPLAYER_FFDECODE_H
