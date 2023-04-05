//
// Created by JJLeong on 2023/4/4.
//

#ifndef JJPLAYER_IOBSERVER_H
#define JJPLAYER_IOBSERVER_H

#include "../bean/XData.h"
#include "../utils/XThread.h"
#include <vector>
#include <mutex>

//观察者 与 被观察者 封装类
class IObserver : public XThread{
public:
    void addObserver(IObserver *observer); //订阅方法
    void removeObserver(IObserver *observer); //解除订阅
    void notifyDataToAllObserver(XData data); //给观察者发送数据

    virtual void updateData(XData data){} //观察者实现的函数，用来接收数据

protected:
    std::vector<IObserver *> observerList;
    std::mutex listMutex;
};


#endif //JJPLAYER_IOBSERVER_H
