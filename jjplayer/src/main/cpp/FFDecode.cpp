//
// Created by JJLeong on 2023/4/5.
//

#include "FFDecode.h"
#include "utils/Log.h"

extern "C"{
#include <libavcodec/avcodec.h>
}

bool FFDecode::openDecode(XParameter xParam) {
    if(!xParam.parameters) return false;

    AVCodecParameters *parameters = xParam.parameters;

    //寻找解码器
    AVCodec *codec = avcodec_find_decoder(parameters->codec_id);
    if (!codec){
        LOGE("avcodec_find_decoder fail, codec_id=%d", parameters->codec_id);
        return false;
    }

    //创建上下文，复制参数
    codecContext = avcodec_alloc_context3(codec);
    avcodec_parameters_to_context(codecContext, parameters);

    //打开解码器
    int openResult = avcodec_open2(codecContext, 0, 0);
    if (openResult != 0){
        char buf[1024] = {0};
        av_strerror(openResult, buf, sizeof(buf));
        LOGE("avcodec_open2 fail, err=%s", buf);
        return false;
    }

    LOGI("FFDecode::openDecode success");
    return true;
}
