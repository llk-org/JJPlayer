//
// Created by JJLeong on 2023/4/9.
//

#ifndef JJPLAYER_IEGL_H
#define JJPLAYER_IEGL_H

/**
 * 单例类
 */
class IEGL {
public:
    static IEGL *get();
    virtual bool init(void * window) = 0;

protected:
    IEGL(){}
};


#endif //JJPLAYER_IEGL_H
