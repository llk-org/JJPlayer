//
// Created by JJLeong on 2023/4/5.
//

#ifndef JJPLAYER_IDECODE_H
#define JJPLAYER_IDECODE_H

#include "../bean/XParameter.h"
#include "IObserver.h"
#include <list>

//解码接口
class IDecode : public IObserver{
public:
    virtual bool openDecode(XParameter xParam) = 0;

    //future模型
    //发生pkt数据给真正的解码器，进行解码
    virtual bool sendPacketToDecoder(XData xData) = 0;
    //从解码器中，接收解码后的帧数据，并进行封装。
    //再次调用会复用上次的空间 - 线程不安全
    virtual XData receiveFrameFromDecoder() = 0;

    //接收被观察者发送过来的数据（Decode会订阅Demux）- 存在阻塞（当队列满的时候）
    //生产者模式 - 生产数据到队列
    virtual void updateData(XData pkt);

    bool isAudioDecode = false; //区分解码器类型
    int maxPacketsSize = 100; //待解码的帧数据队列的最大缓存大小
protected:
    //线程启动后就会执行这个函数
    //生产者模式 - 消费队列中的数据
    virtual void run();

    std::list<XData> packets; //保存所有的待解码的帧数据
    std::mutex mutex_packets;
};


#endif //JJPLAYER_IDECODE_H
