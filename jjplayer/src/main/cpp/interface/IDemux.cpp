//
// Created by JJLeong on 2023/4/2.
//

#include "IDemux.h"
#include "../utils/Log.h"

void IDemux::run() {
    while (!isStopThread){
        XData d = read();
        if (d.size > 0){
            notifyDataToAllObserver(d);
        }
    }
}
