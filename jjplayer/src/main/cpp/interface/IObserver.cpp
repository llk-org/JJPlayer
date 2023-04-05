//
// Created by JJLeong on 2023/4/4.
//

#include "IObserver.h"
#include "../utils/Log.h"

void IObserver::addObserver(IObserver *observer) {
    if (!observer) return;
    listMutex.lock();
    LOGV("IObserver::addObserver %p", observer);
    observerList.push_back(observer);
    listMutex.unlock();
}

void IObserver::removeObserver(IObserver *observer) {
    if (!observer) return;
    listMutex.lock();
    LOGV("IObserver::removeObserver %p", observer);
    auto itr = observerList.begin();
    while (itr != observerList.end()) {
        if (*itr == observer) {
            itr = observerList.erase(itr);//删除元素，返回值指向已删除元素的下一个位置
        } else {
            ++itr;
        }
        listMutex.unlock();
    }
}

void IObserver::notifyDataToAllObserver(XData data) {
    listMutex.lock();
    for (auto &i: observerList) {
        i->updateData(data);
    }
    listMutex.unlock();
}
