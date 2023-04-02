//
// Created by JJLeong on 2023/4/2.
//

#include "FFDemux.h"
#include "Log.h"

extern "C"{
#include <libavformat/avformat.h>
}

void FFDemux::initFFmpeg() {
    LOGD("FFDemux::initFFmpeg");
    av_register_all(); //注册所有的封装器
    avcodec_register_all(); //注册所有的解码器
    avformat_network_init(); //初始化网络
}

FFDemux::FFDemux() {
    static bool isInit = false;
    if (!isInit){
        isInit = true;
        initFFmpeg();
    }
}

bool FFDemux::open(const char* url){
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

XData FFDemux::read(){
    if (!avFormatContext) return XData();

    AVPacket *avPacket = av_packet_alloc();
    int readResult = av_read_frame(avFormatContext, avPacket);
    if (readResult != 0){
        LOGE("av_read_frame fail, result=%d", readResult);
        av_packet_free(&avPacket);
        return XData();
    }

    XData d;
    d.data = (unsigned char *)avPacket;
    d.size = avPacket->size;
    LOGD("aaa size=%d pts=%lld", avPacket->size, avPacket->pts);
    return d;
}

bool FFDemux::close(){
    LOGD("FFDemux::Close");
    return false;
}
