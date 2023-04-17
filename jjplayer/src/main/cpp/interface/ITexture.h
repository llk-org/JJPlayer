//
// Created by JJLeong on 2023/4/14.
//

#ifndef JJPLAYER_ITEXTURE_H
#define JJPLAYER_ITEXTURE_H

class ITexture {
public:
    static ITexture *makeTexture();
    virtual bool init(void *window) = 0;
    virtual void draw(unsigned char *datas[], int width, int height) = 0;

protected:
    ITexture(){}
};


#endif //JJPLAYER_ITEXTURE_H
