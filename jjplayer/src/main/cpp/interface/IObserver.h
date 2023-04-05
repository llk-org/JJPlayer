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
//观察者订阅之后，当被观察者有数据更新的时候，会通知到观察者
class IObserver : public XThread{
public:
    //被观察者相关的函数==============
    void addObserver(IObserver *observer); //订阅方法
    void removeObserver(IObserver *observer); //解除订阅
    void notifyDataToAllObserver(XData data); //通知观察者，有数据更新

    //观察者相关的函数==============
    virtual void updateData(XData data){} //观察者实现的函数，用来接收数据

protected:
    std::vector<IObserver *> observers;
    std::mutex mutex_observers;
};


#endif //JJPLAYER_IOBSERVER_H
