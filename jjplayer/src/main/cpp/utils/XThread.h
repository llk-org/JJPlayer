//
// Created by JJLeong on 2023/4/2.
//

#ifndef JJPLAYER_XTHREAD_H
#define JJPLAYER_XTHREAD_H

//线程sleep函数，单位是毫秒
void x_thread_sleep(int ms);

//c++ 11线程
class XThread {
public:
    virtual void start(); //启动线程
    virtual void stop(); //关闭线程
    virtual void run(){} //线程执行函数
protected:
    bool isStopThread = false; //是否停止线程
    bool isRunning = false; //线程是否运行中
private:
    void thread_run();
};


#endif //JJPLAYER_XTHREAD_H
