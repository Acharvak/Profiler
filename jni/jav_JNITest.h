/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class jav_JNITest */

#ifndef _Included_jav_JNITest
#define _Included_jav_JNITest
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     jav_JNITest
 * Method:    voidMethod
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_jav_JNITest_voidMethod
  (JNIEnv *, jobject);

/*
 * Class:     jav_JNITest
 * Method:    getsAndReturnsInt
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_jav_JNITest_getsAndReturnsInt
  (JNIEnv *, jobject, jint);

/*
 * Class:     jav_JNITest
 * Method:    returnsString
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_jav_JNITest_returnsString
  (JNIEnv *, jobject);

/*
 * Class:     jav_JNITest
 * Method:    getsAndReturnsString
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_jav_JNITest_getsAndReturnsString
  (JNIEnv *, jobject, jstring);

#ifdef __cplusplus
}
#endif
#endif