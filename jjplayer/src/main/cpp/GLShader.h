//
// Created by JJLeong on 2023/4/9.
//

#ifndef JJPLAYER_GLSHADER_H
#define JJPLAYER_GLSHADER_H


class GLShader {
protected:
    unsigned int vertexShader = 0;
    unsigned int fragmentShader = 0;
    unsigned int glProgram = 0;
    unsigned int textures[100] = {0};
public:
    virtual bool init();
    //获取材质并映射到内存
    virtual void getTexture(unsigned int textureIndex, int width, int height, unsigned char *buf);
    virtual void draw();
};


#endif //JJPLAYER_GLSHADER_H
