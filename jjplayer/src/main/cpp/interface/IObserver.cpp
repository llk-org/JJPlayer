//
// Created by JJLeong on 2023/4/4.
//

#include "IObserver.h"
#include "../utils/Log.h"

void IObserver::addObserver(IObserver *observer) {
    if (!observer) return;
    mutex_observers.lock();
    LOGV("IObserver::addObserver %p", observer);
    observers.push_back(observer);
    mutex_observers.unlock();
}

void IObserver::removeObserver(IObserver *observer) {
    if (!observer) return;
    mutex_observers.lock();
    LOGV("IObserver::removeObserver %p", observer);
    auto itr = observers.begin();
    while (itr != observers.end()) {
        if (*itr == observer) {
            itr = observers.erase(itr);//删除元素，返回值指向已删除元素的下一个位置
        } else {
            ++itr;
        }
    }
    mutex_observers.unlock();
}

void IObserver::notifyDataToAllObserver(XData data) {
    mutex_observers.lock();
    for (auto &i: observers) {
        i->updateData(data);
    }
    mutex_observers.unlock();
}
