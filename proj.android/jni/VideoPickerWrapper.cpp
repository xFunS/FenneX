/****************************************************************************
Copyright (c) 2013-2014 Auticiel SAS

http://www.fennex.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************///

#include "Logs.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include "VideoPickerWrapper.h"

#define CLASS_NAME_RECORDER "com/fennex/modules/VideoRecorder"
#define CLASS_NAME_PICKER "com/fennex/modules/VideoPicker"

void startVideoRecordPreview(CCPoint position, CCSize size)
{
	JniMethodInfo minfo;
	CCAssert(JniHelper::getStaticMethodInfo(minfo,CLASS_NAME_RECORDER,"startRecordPreview", "(FFFF)V"), "Function doesn't exist");
	minfo.env->CallStaticVoidMethod(
			minfo.classID,
			minfo.methodID,
			(jfloat)position.x,
			(jfloat)position.y,
			(jfloat)size.width,
			(jfloat)size.height);
    minfo.env->DeleteLocalRef(minfo.classID);
}

void stopVideoRecordPreview()
{
	JniMethodInfo minfo;
	CCAssert(JniHelper::getStaticMethodInfo(minfo,CLASS_NAME_RECORDER,"stopRecordPreview", "()V"), "Function doesn't exist");
	minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    minfo.env->DeleteLocalRef(minfo.classID);
}

void startVideoRecording()
{
	JniMethodInfo minfo;
	CCAssert(JniHelper::getStaticMethodInfo(minfo, CLASS_NAME_RECORDER, "startRecording", "()V"), "Function doesn't exist");
	minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    minfo.env->DeleteLocalRef(minfo.classID);
}

void stopVideoRecording()
{
	JniMethodInfo minfo;
	CCAssert(JniHelper::getStaticMethodInfo(minfo,CLASS_NAME_RECORDER,"stopRecording", "()V"), "Function doesn't exist");
	minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    minfo.env->DeleteLocalRef(minfo.classID);
}

bool cancelRecording(bool notify)
{
	JniMethodInfo minfo;
	CCAssert(JniHelper::getStaticMethodInfo(minfo,CLASS_NAME_RECORDER,"cancelRecording", "(Z)Z"), "Function doesn't exist");
	bool result = minfo.env->CallStaticBooleanMethod(minfo.classID, minfo.methodID, (jboolean)notify);
    minfo.env->DeleteLocalRef(minfo.classID);
    return result;
}

bool pickVideoFromLibrary()
{
	JniMethodInfo minfo;
	CCAssert(JniHelper::getStaticMethodInfo(minfo, CLASS_NAME_PICKER, "pickVideoFromLibrary", "()Z"), "Function doesn't exist");
	bool result = minfo.env->CallStaticBooleanMethod(minfo.classID, minfo.methodID);
    minfo.env->DeleteLocalRef(minfo.classID);
    return result;
}

void getAllVideos()
{
	JniMethodInfo minfo;
	CCAssert(JniHelper::getStaticMethodInfo(minfo, CLASS_NAME_PICKER, "getAllVideos", "()V"), "Function doesn't exist");
	minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    minfo.env->DeleteLocalRef(minfo.classID);
}

extern "C"
{
	//extension for long name : __Ljava_lang_String_2Ljava_lang_String_2
	void Java_com_fennex_modules_VideoPicker_notifyVideoPickedWrap(JNIEnv* env, jobject thiz, jstring name)
	{
		const char* nameC = env->GetStringUTFChars(name, 0);
		if(nameC != NULL)
		{
			notifyVideoPicked(nameC);
		}
		env->ReleaseStringUTFChars(name, nameC);
	}

	void Java_com_fennex_modules_VideoPicker_notifyVideoFound(JNIEnv* env, jobject thiz, jstring name)
	{
		const char* nameC = env->GetStringUTFChars(name, 0);
		if(nameC != NULL)
		{
			notifyVideoFound(nameC);
		}
		env->ReleaseStringUTFChars(name, nameC);
	}

	void Java_com_fennex_modules_VideoPicker_notifyVideoName(JNIEnv* env, jobject thiz, jstring path, jstring name)
	{
		const char* pathC = env->GetStringUTFChars(path, 0);
		const char* nameC = env->GetStringUTFChars(name, 0);
		if(nameC != NULL && pathC != NULL)
		{
			notifyVideoName(pathC, nameC);
		}
		env->ReleaseStringUTFChars(path, pathC);
		env->ReleaseStringUTFChars(name, nameC);
	}

	void Java_com_fennex_modules_VideoRecorder_notifyRecordingCancelled(JNIEnv* env, jobject thiz)
	{
		notifyRecordingCancelled();
	}

	void Java_com_fennex_modules_VideoPicker_notifyGetAllVideosFinished(JNIEnv* env, jobject thiz)
	{
		notifyGetAllVideosFinished();
	}
}
