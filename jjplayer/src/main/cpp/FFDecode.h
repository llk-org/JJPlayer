//
// Created by JJLeong on 2023/4/5.
//

#ifndef JJPLAYER_FFDECODE_H
#define JJPLAYER_FFDECODE_H

#include "interface/IDecode.h"

struct AVCodecContext;

class FFDecode : public IDecode{
public:
    virtual bool openDecode(XParameter xParam);
protected:
    AVCodecContext *codecContext = 0;
};


#endif //JJPLAYER_FFDECODE_H
