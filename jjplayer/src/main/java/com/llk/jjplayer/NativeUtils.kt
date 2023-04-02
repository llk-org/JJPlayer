package com.llk.jjplayer

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
}