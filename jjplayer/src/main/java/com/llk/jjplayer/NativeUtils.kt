package com.llk.jjplayer

import android.view.Surface
import android.view.SurfaceHolder

/**
 * author: llk
 * date  : 2023/4/2
 * detail:
 */
object NativeUtils {
    init {
        System.loadLibrary("jjplayer")
    }

    external fun open(url: String): Boolean

    external fun surfaceCreated(surface: Surface)

    external fun surfaceChanged(surface: Surface, format: Int, w: Int, h: Int)

    external fun surfaceDestroyed(surface: Surface)
}