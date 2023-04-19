//
// Created by JJLeong on 2023/4/5.
//

#include "FFDecode.h"
#include "utils/Log.h"

extern "C"{
#include <libavcodec/avcodec.h>
}

FFDecode::FFDecode(const char *clazzName) {
    className = clazzName;
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

    //todo 开启多线程解码(这个后续自行参数配置)
    codecContext->thread_count = 8;

    //打开解码器
    int openResult = avcodec_open2(codecContext, 0, 0);
    if (openResult != 0){
        char buf[1024] = {0};
        av_strerror(openResult, buf, sizeof(buf));
        LOGE("avcodec_open2 fail, err=%s", buf);
        return false;
    }

    if (codecContext->codec_type == AVMEDIA_TYPE_AUDIO){
        isAudioDecode = true;
    } else{
        isAudioDecode = false;
    }

    LOGI("%s::openDecode success", className);
    return true;
}

bool FFDecode::sendPacketToDecoder(XData packet){
    if (!packet.data || packet.size<=0) return false;

    if (!codecContext) return false;
    int sendResult = avcodec_send_packet(codecContext, (AVPacket*)packet.data);
    if (sendResult != 0){ //发送失败
        LOGE("ffffffff %s %d", className, sendResult);
        return false;
    }

    LOGE("ttttttt %s", className);
    return false;
}

XData FFDecode::receiveFrameFromDecoder() {
    if (!codecContext) return {};

    //创建帧对象
    if (!frame){
        frame = av_frame_alloc();
    }

    int recvResult = avcodec_receive_frame(codecContext, frame);
    if (recvResult != 0){ //接收失败
        return {};
    }

    XData data;
    data.data = (unsigned char*)frame;
    if (codecContext->codec_type == AVMEDIA_TYPE_VIDEO){ //视频 大小=单个YUV大小*数据量
        //linesize最大8位的一个空间，如果是YUV，linesize就表示每一路一行数据的大小
        //linesize[0]就是Y数据大小，linesize[1]就是U数据大小，linesize[2]就是V数据大小
        data.size = (frame->linesize[0] + frame->linesize[1] + frame->linesize[2]) * frame->height;

        data.videoWidth = frame->width;
        data.videoHeight = frame->height;
    }else{ //音频 大小=单个样本大小*数据量*通道数
        //av_get_bytes_per_sample 获取单个样本大小
        //frame->nb_samples 样本数量
        data.size = av_get_bytes_per_sample((AVSampleFormat)frame->format) * frame->nb_samples * 2;
    }

    memcpy(data.datas, frame->data, sizeof(data.datas));

    return data;
}
