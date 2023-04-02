//
// Created by JJLeong on 2023/4/2.
//

#ifndef JJPLAYER_IDEMUX_H
#define JJPLAYER_IDEMUX_H

#include "XData.h"

//解封装接口类
class IDemux {
public:
    //打开文件 或 流媒体（rtmp/http/rtsp）
    virtual bool Open(const char* url) = 0;
    //关闭文件 或 流媒体
    virtual bool Close() = 0;

    //读取一帧数据，数据由调用者清理
    virtual XData Read() = 0;

    int totalMs = 0; //总时长（毫秒）
};


#endif //JJPLAYER_IDEMUX_H
