//
// Created by JJLeong on 2023/4/2.
//

#include "XData.h"

extern "C"{
#include "libavformat/avformat.h"
}

void XData::release() {
    if(!data) return;

    av_packet_free((AVPacket **)&data);
    data = 0;
    size = 0;
}