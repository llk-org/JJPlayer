//
// Created by JJLeong on 2023/4/2.
//

#ifndef JJPLAYER_IDEMUX_H
#define JJPLAYER_IDEMUX_H

#include "../bean/XData.h"
#include "../utils/XThread.h"
#include "IObserver.h"
#include "../bean/XParameter.h"

//解封装接口类
class IDemux : public IObserver{
public:
    virtual bool open(const char* url) = 0; //打开文件 或 流媒体（rtmp/http/rtsp）
    virtual bool close() = 0; //关闭文件 或 流媒体

    virtual XParameter getVideoParam() = 0; //获取视频参数

    virtual XData read() = 0; //读取一帧数据，数据由调用者清理

    int totalMs = 0; //总时长（毫秒）

protected:
    virtual void run();
};


#endif //JJPLAYER_IDEMUX_H
