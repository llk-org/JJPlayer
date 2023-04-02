//
// Created by JJLeong on 2023/4/2.
//

#include "IDemux.h"
#include "Log.h"

void IDemux::run() {
    while (!isStopThread){
        XData d = read();
        LOGD("run %d", d.size);
        if (d.size <= 0){
            break;
        }
    }
}
