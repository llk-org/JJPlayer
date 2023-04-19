#include <jni.h>
#include <string>
#include <android/native_window_jni.h>

#include "FFDemux.h"
#include "XLog.h"
#include "FFdecode.h"
#include "XEGL.h"
#include "XShader.h"
#include "IVideoView.h"
#include "GLVideoView.h"


IVideoView *view = NULL;

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_llk_jjplayer_NativeUtils_open(JNIEnv *env, jobject thiz, jstring url) {

    ///////////////////////////////////
    ///测试用代码
    IDemux *de = new FFDemux();
    de->Open(env->GetStringUTFChars(url, NULL));

    IDecode *vdecode = new FFDecode();
    vdecode->Open(de->GetVPara());

    IDecode *adecode = new FFDecode();
    adecode->Open(de->GetAPara());
    de->AddObs(vdecode);
    de->AddObs(adecode);

    view = new GLVideoView();
    vdecode->AddObs(view);


    //vdecode->Open();
    de->Start();
    vdecode->Start();
    adecode->Start();

    //XSleep(3000);
    //de->Stop();
    /*for(;;)
    {
        XData d = de->Read();
        XLOGI("Read data size is %d",d.size);


    }*/

    return true;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_llk_jjplayer_NativeUtils_surfaceCreated(JNIEnv *env, jobject thiz, jobject surface) {
    ANativeWindow *win = ANativeWindow_fromSurface(env,surface);
    view->SetRender(win);
    //XEGL::Get()->Init(win);
    //XShader shader;
    //shader.Init();
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