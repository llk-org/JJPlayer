#include <jni.h>
#include "iostream"
#include <string>
#include <android/native_window_jni.h>

#include "utils/Log.h"
#include "FFDemux.h"
#include "FFDecode.h"
#include "PlayerEGL.h"
#include "GLShader.h"
#include "interface/IVideoView.h"
#include "GLVideoView.h"

IVideoView *videoView = NULL;

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
        IDecode *videoDecode = new FFDecode("VideoFFDecode");
        IDecode *audioDecode = new FFDecode("AudioFFDecode");
        //启动解码器
        videoDecode->openDecode(demux->getAVParam(false));
        audioDecode->openDecode(demux->getAVParam(true));

        //解码器订阅解封装器
        //当解封装器解码每读到一帧数据，就会发送给解码器
        demux->addObserver(videoDecode);
        demux->addObserver(audioDecode);

        videoView = new GLVideoView();
        videoDecode->addObserver(videoView);

        //启动解封装线程，生产帧数据
        demux->start();
        //启动解码线程，生产解码后的帧数据
        videoDecode->start();
        audioDecode->start();
    }

    return isSuccess;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_llk_jjplayer_NativeUtils_surfaceCreated(JNIEnv *env, jobject thiz, jobject surface) {
    ANativeWindow *nativeWindow = ANativeWindow_fromSurface(env, surface);
    videoView->setRender(nativeWindow);
//    PlayerEGL::get()->init(nativeWindow);
//    GLShader glShader;
//    glShader.init();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_llk_jjplayer_NativeUtils_surfaceChanged(JNIEnv *env, jobject thiz, jobject surface,
                                                 jint format, jint w, jint h) {
    // TODO: implement surfaceChanged()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_llk_jjplayer_NativeUtils_surfaceDestroyed(JNIEnv *env, jobject thiz, jobject surface) {
    // TODO: implement surfaceDestroyed()
}