//
// Created by JJLeong on 2023/4/2.
//

#include "IDemux.h"

void IDemux::run() {
    while (!isStopThread){
        XData d = read();
        if (d.size > 0){
            //发送数据给订阅解封装器的那些观察者（解码器）
            notifyDataToAllObserver(d);
        }
    }
}
