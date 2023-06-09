//
// Created by JJLeong on 2023/4/14.
//

#ifndef JJPLAYER_GLTEXTURE_H
#define JJPLAYER_GLTEXTURE_H


#include "interface/ITexture.h"
#include "GLShader.h"

class GLTexture : public ITexture{
public:
    GLShader glShader;
    static ITexture *makeTexture();
    virtual bool init(void *window);
    virtual void draw(unsigned char *datas[], int width, int height);
};


#endif //JJPLAYER_GLTEXTURE_H
