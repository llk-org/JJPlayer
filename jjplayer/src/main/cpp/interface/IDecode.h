//
// Created by JJLeong on 2023/4/5.
//

#ifndef JJPLAYER_IDECODE_H
#define JJPLAYER_IDECODE_H

#include "../bean/XParameter.h"
#include "IObserver.h"

//解码接口
class IDecode : public IObserver{
public:
    virtual bool openDecode(XParameter xParam) = 0;
};


#endif //JJPLAYER_IDECODE_H
