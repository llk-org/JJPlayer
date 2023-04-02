//
// Created by JJLeong on 2023/4/2.
//

#include "FFDemux.h"
#include "Log.h"

extern "C"{
#include <libavformat/avformat.h>
}

FFDemux::FFDemux() {
    static bool isInit = false;
    if (!isInit){
        isInit = true;
        initFFmpeg();
    }
}

void FFDemux::initFFmpeg() {
    LOGD("FFDemux::initFFmpeg");
    av_register_all(); //注册所有的封装器
    avcodec_register_all(); //注册所有的解码器
    avformat_network_init(); //初始化网络
}

bool FFDemux::Open(const char* url){
    LOGD("FFDemux::Open -> %s", url);

    int openResult = avformat_open_input(&avFormatContext, url, 0, 0);
    if (openResult != 0){
        char buf[1024] = {0};
        av_strerror(openResult, buf, sizeof(buf));
        LOGE("avformat_open_input fail, err=%s", buf);
        return false;
    }

    int findStreamResult = avformat_find_stream_info(avFormatContext, 0);
    if (findStreamResult != 0){
        char buf[1024] = {0};
        av_strerror(findStreamResult, buf, sizeof(buf));
        LOGE("avformat_find_stream_info fail, err=%s", buf);
        return false;
    }

    //TIMER_ABSTIME 是时间单位，表示1秒有多少个时间单位，除以1000单位就变成毫秒
    totalMs = avFormatContext->duration / (TIMER_ABSTIME/1000);
    LOGD("total ms =%d", totalMs);

    return true;
}

bool FFDemux::Close(){
    LOGD("FFDemux::Close");
    return false;
}

XData FFDemux::Read(){
    LOGD("FFDemux::Read");
    XData a;
    return a;
}
