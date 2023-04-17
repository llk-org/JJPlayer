//
// Created by JJLeong on 2023/4/2.
//

#ifndef JJPLAYER_XDATA_H
#define JJPLAYER_XDATA_H


struct XData {
    unsigned char *data = 0;
    unsigned char *datas[8] = {0};
    int size = 0;

    bool isAudio = false;
    //视频才有宽高
    int videoWidth = 0;
    int videoHeight = 0;

    void release();
};


#endif //JJPLAYER_XDATA_H
