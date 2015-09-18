LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE     := goengine
LOCAL_CPPFLAGS   := -std=gnu++11 -fexceptions -frtti
LOCAL_C_INCLUDES := ${ANDROID_NDK}/sources/cxx-stl/gnu-libstdc++/4.8/include
LOCAL_SRC_FILES  := ./gtp_game.cc \
                    ./gtp_player.cc

include $(BUILD_SHARED_LIBRARY)
