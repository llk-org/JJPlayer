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
public:
    virtual bool init();
};


#endif //JJPLAYER_GLSHADER_H
