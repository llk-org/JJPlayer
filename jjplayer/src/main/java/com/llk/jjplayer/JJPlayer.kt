package com.llk.jjplayer

import android.content.Context
import android.opengl.GLSurfaceView
import android.util.AttributeSet
import android.view.SurfaceHolder

/**
 * author: llk
 * date  : 2023/4/9
 * detail:
 */
class JJPlayer: GLSurfaceView{

    constructor(context: Context) : super(context, null){ }

    constructor(context: Context, attrs: AttributeSet?) : super(context, attrs){ }

    override fun surfaceCreated(holder: SurfaceHolder) {
        NativeUtils.surfaceCreated(holder.surface)
    }

    override fun surfaceChanged(holder: SurfaceHolder, format: Int, w: Int, h: Int) {
        NativeUtils.surfaceChanged(holder.surface, format, w, h)
    }

    override fun surfaceDestroyed(holder: SurfaceHolder) {
        NativeUtils.surfaceDestroyed(holder.surface)
    }
}