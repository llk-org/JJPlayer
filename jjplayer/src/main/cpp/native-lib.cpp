#include <jni.h>
#include "iostream"
#include <string>

#include "utils/Log.h"
#include "FFDemux.h"
#include "FFDecode.h"

jint JNI_OnLoad(JavaVM *vm, void* reserved) {
    JNIEnv *env = nullptr;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }

    return JNI_VERSION_1_6;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_llk_jjplayer_NativeUtils_open(JNIEnv *env, jobject thiz, jstring url) {

    //创建解封装器对象
    IDemux *demux = new FFDemux();
    //对目标文件进行解封装
    bool isSuccess = demux->open(env->GetStringUTFChars(url, NULL));
    if (isSuccess){ //解封装成功
        //创建视频、音频解码器对象
        IDecode *videoDecode = new FFDecode();
        IDecode *audioDecode = new FFDecode();
        //启动解码器
        videoDecode->openDecode(demux->getAVParam(false));
        audioDecode->openDecode(demux->getAVParam(true));

        //解码器订阅解封装器
        //当解封装器解码每读到一帧数据，就会发送给解码器
        demux->addObserver(videoDecode);
        demux->addObserver(audioDecode);

        //启动解封装器线程，生产帧数据
        demux->start();

        //启动解码器线程，
        videoDecode->start();
        audioDecode->start();
    }

    return isSuccess;
}