//
// Created by JJLeong on 2023/4/2.
//

#include "XThread.h"
#include "Log.h"
#include <thread>

using namespace std;

void XThread::start() {
    LOGD("XThread::start");
    thread t(&XThread::thread_run, this);
    t.detach(); //放弃对这个线程的控制，让线程结束的时候释放相关资源。
}

void XThread::stop() {
    LOGD("XThread::stop");
}

void XThread::thread_run() {
    LOGD("XThread::thread_run start");
    run();
    LOGD("XThread::thread_run end");
}
