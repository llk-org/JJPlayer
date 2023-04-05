//
// Created by JJLeong on 2023/4/5.
//

#include "IDecode.h"

void IDecode::updateData(XData pkt) {
    //判断是否为对应解码器的数据
    if (pkt.isAudio != isAudioDecode){
        return;
    }

    while (!isStopThread){
        mutex_packets.lock();

        //队列没满，就加入队列，跳出循环
        if (packets.size() < maxPacketsSize){
            packets.push_back(pkt);
            mutex_packets.unlock();
            break;
        }

        //队列满了，继续走循环，让其阻塞。让解码线程消费队列中的数据。
        //注意，Demux的线程的notifyObs才会走到这里的updateData函数，所有这里阻塞，也会让Demux线程阻塞
        mutex_packets.unlock();
        x_thread_sleep(1);
    }
}

void IDecode::run() {
    while (!isStopThread){
        mutex_packets.lock();
        if (packets.empty()){
            mutex_packets.unlock();
            x_thread_sleep(1);
            continue;
        }

        //从队列头取出一个数据
        XData packet = packets.front();
        packets.pop_front();//删掉队列头的一个数据，因为我们已经取出来了

        //发送pkt数据给解码器，进行解码
        //一个数据包，可能解码多个结果
        if (sendPacketToDecoder(packet)){
            while (!isStopThread){
                //接收解码后的数据
                XData frame = receiveFrameFromDecoder();
                if (!frame.data) break;
                //发送数据给观察者
                notifyDataToAllObserver(frame);
            }
        }

        //释放数据
        packet.release();

        mutex_packets.unlock();
    }
}
