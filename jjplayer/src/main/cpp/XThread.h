//
// Created by JJLeong on 2023/4/2.
//

#ifndef JJPLAYER_XTHREAD_H
#define JJPLAYER_XTHREAD_H

//c++ 11线程
class XThread {
public:
    //启动线程
    virtual void start();

    //关闭线程
    virtual void stop();

    virtual void run(){}

private:
    void thread_run();
};


#endif //JJPLAYER_XTHREAD_H
