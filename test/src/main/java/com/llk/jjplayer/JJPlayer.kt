package com.llk.jjplayer

import android.content.Context
import android.opengl.GLSurfaceView
import android.util.AttributeSet
import android.view.SurfaceHolder
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

/**
 * author: llk
 * date  : 2023/4/9
 * detail:
 */
class JJPlayer: GLSurfaceView, GLSurfaceView.Renderer {

    constructor(context: Context) : super(context, null){
        init()
    }

    constructor(context: Context, attrs: AttributeSet?) : super(context, attrs){
        init()
    }

    private fun init(){
        setRenderer(this)
    }

    override fun surfaceCreated(holder: SurfaceHolder) {
        NativeUtils.surfaceCreated(holder.surface)
    }

    override fun surfaceChanged(holder: SurfaceHolder, format: Int, w: Int, h: Int) {
        NativeUtils.surfaceChanged(holder.surface, format, w, h)
    }

    override fun surfaceDestroyed(holder: SurfaceHolder) {
        NativeUtils.surfaceDestroyed(holder.surface)
    }

    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
    }

    override fun onDrawFrame(gl: GL10?) {
    }
}