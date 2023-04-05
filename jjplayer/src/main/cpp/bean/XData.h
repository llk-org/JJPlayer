//
// Created by JJLeong on 2023/4/2.
//

#ifndef JJPLAYER_XDATA_H
#define JJPLAYER_XDATA_H


struct XData {
    unsigned char *data = 0;
    int size = 0;
    bool isAudio = false;
    void release();
};


#endif //JJPLAYER_XDATA_H
