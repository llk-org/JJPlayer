//
// Created by JJLeong on 2023/4/2.
//

#include "XThread.h"
#include "Log.h"
#include <thread>

using namespace std;

void x_thread_sleep(int ms){
    chrono::milliseconds ms_obj(ms);
    this_thread::sleep_for(ms_obj);
}

void XThread::start() {
    LOGD("XThread::start");
    isStopThread = false;
    thread t(&XThread::thread_run, this);
    t.detach(); //放弃对这个线程的控制，让线程结束的时候释放相关资源。
}

void XThread::thread_run() {
    LOGD("XThread::thread_run start");
    isRunning = true;
    run();
    isRunning = false;
    LOGD("XThread::thread_run end");
}

void XThread::stop() {
    LOGD("XThread::stop");
    isStopThread = true;

    //继续等待200ms，确保线程真正退出（因为我们将stop变量置为true，循环体内可能仍然在执行。）
    for (int i = 0; i < 200; ++i) {
        if (!isRunning){
            LOGD("XThread::stop success.");
            return;
        }
        x_thread_sleep(1);
    }
    LOGW("XThread::stop timeout.");
}
