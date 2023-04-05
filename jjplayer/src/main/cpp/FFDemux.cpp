//
// Created by JJLeong on 2023/4/2.
//

#include "FFDemux.h"
#include "utils/Log.h"

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

XParameter FFDemux::getAVParam(bool isGetAudio) {
    if (!avFormatContext){
        LOGW("FFDemux::getAVParam fail, avFormatContext is NULL");
        return {};
    }

    //获取流索引
    int streamIndex = av_find_best_stream(avFormatContext,
                                          isGetAudio ? AVMEDIA_TYPE_AUDIO : AVMEDIA_TYPE_VIDEO,
                                          -1, -1, 0, 0);
    LOGD("FFDemux::getAVParam isGetAudio=%d streamIndex=%d", isGetAudio, streamIndex);
    if (isGetAudio){
        audioStreamIndex = streamIndex;
    } else{
        videoStreamIndex = streamIndex;
    }
    if (streamIndex < 0){
        LOGW("av_find_best_stream fail, not found stream.");
        return {};
    }

    XParameter xP;
    xP.parameters = avFormatContext->streams[streamIndex]->codecpar;
    return xP;
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
    //LOGD("total ms =%d", totalMs);

    //提前获取一下流索引，缓存起来
    getAVParam(false);
    getAVParam(true);

    return true;
}

XData FFDemux::read(){
    if (!avFormatContext) return {};

    AVPacket *avPacket = av_packet_alloc();
    int readResult = av_read_frame(avFormatContext, avPacket);
    if (readResult != 0){
        av_packet_free(&avPacket);
        return {};
    }

    XData d;
    d.data = (unsigned char *)avPacket;
    d.size = avPacket->size;
    if (avPacket->stream_index == audioStreamIndex){
        d.isAudio = true;
    } else if(avPacket->stream_index == videoStreamIndex){
        d.isAudio = false;
    } else{ //既不是音频也不是视频，就释放掉avPacket
        av_packet_free(&avPacket);
        return {};
    }

    return d;
}

bool FFDemux::close(){
    LOGD("FFDemux::Close");
    return false;
}
