//
// Created by JJLeong on 2023/4/2.
//

#ifndef JJPLAYER_FFDEMUX_H
#define JJPLAYER_FFDEMUX_H

#include "interface/IDemux.h"
//声明为结构体，就不需要引入头文件了（因为指针也只是一种类型，并不用管它内部实现）
//这样做的好处是不需要引入相关的头文件
struct AVFormatContext;

class FFDemux : public IDemux{
public:
    FFDemux();
    virtual bool open(const char* url);
    virtual bool close();
    virtual XParameter getAVParam(bool isGetAudio);
    virtual XData read();
private:
    virtual void initFFmpeg();
    //c++开始支持默认赋值，但是只有在执行无参构造函数的时候才会执行的（走了有参构造函数，是不会赋值的），这里需要注意。
    AVFormatContext *avFormatContext = 0;
    int videoStreamIndex = 0;
    int audioStreamIndex = 1;
};


#endif //JJPLAYER_FFDEMUX_H
