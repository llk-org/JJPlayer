//
// Created by JJLeong on 2023/4/5.
//

#ifndef JJPLAYER_IDECODE_H
#define JJPLAYER_IDECODE_H

#include "../bean/XParameter.h"
#include "IObserver.h"

//解码接口
class IDecode : public IObserver{
public:
    virtual bool openDecode(XParameter xParam) = 0;

    //future模型
    //发送要处理的数据到线程
    virtual bool sendPacket(XData xData) = 0;
    //从线程中获取处理完的数据
    virtual XData recvFrame() = 0;
};


#endif //JJPLAYER_IDECODE_H
