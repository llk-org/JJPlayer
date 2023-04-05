cmake_minimum_required(VERSION 3.22.1)

project("jjplayer")

include_directories(include)

set(FF_SO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libs/${ANDROID_ABI})
add_library(avcodec SHARED IMPORTED)
set_target_properties(avcodec PROPERTIES IMPORTED_LOCATION ${FF_SO_PATH}/libavcodec.so)

add_library(avformat SHARED IMPORTED)
set_target_properties(avformat PROPERTIES IMPORTED_LOCATION ${FF_SO_PATH}/libavformat.so)

add_library(avutil SHARED IMPORTED)
set_target_properties(avutil PROPERTIES IMPORTED_LOCATION ${FF_SO_PATH}/libavutil.so)

add_library(swscale SHARED IMPORTED)
set_target_properties(swscale PROPERTIES IMPORTED_LOCATION ${FF_SO_PATH}/libswscale.so)

add_library(swresample SHARED IMPORTED)
set_target_properties(swresample PROPERTIES IMPORTED_LOCATION ${FF_SO_PATH}/libswresample.so)

add_library(jjplayer
        SHARED
        src/main/cpp/native-lib.cpp

        # 接口类
        src/main/cpp/interface/IDemux.cpp
        src/main/cpp/interface/IDecode.cpp
        src/main/cpp/interface/IObserver.cpp

        # 工具类
        src/main/cpp/utils/XThread.cpp

        # 结构体
        src/main/cpp/bean/XData.cpp
        src/main/cpp/bean/XParameter.cpp

        # 实现类
        src/main/cpp/FFDemux.cpp
        src/main/cpp/FFDecode.cpp
        )

find_library(
        log-lib
        log)

target_link_libraries(
        jjplayer

        GLESv2 EGL
        OpenSLES

        avcodec
        avformat
        avutil
        swscale
        swresample

        android
        ${log-lib})