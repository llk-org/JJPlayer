#include <jni.h>
#include "iostream"
#include <string>

#include "utils/Log.h"
#include "FFDemux.h"
#include "FFDecode.h"

class TestOb : public IObserver{
public:
    void updateData(XData data) override{
//        LOGI("aaaaaaaa %d", data.size);
    }
};

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

    TestOb *ob = new TestOb();

    IDemux *demux = new FFDemux();
    demux->addObserver(ob);
    bool isSuccess = demux->open(env->GetStringUTFChars(url, NULL));
    if (isSuccess){
        //视频解码器
        IDecode *videoDecode = new FFDecode();
        videoDecode->openDecode(demux->getAVParam(false));

        demux->start();

    }

    return isSuccess;
}