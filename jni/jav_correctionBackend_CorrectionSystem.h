/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class jav_correctionBackend_CorrectionSystem */

#ifndef _Included_jav_correctionBackend_CorrectionSystem
#define _Included_jav_correctionBackend_CorrectionSystem
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     jav_correctionBackend_CorrectionSystem
 * Method:    readConfiguration
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_jav_correctionBackend_CorrectionSystem_readConfiguration
  (JNIEnv *, jobject, jstring);

/*
 * Class:     jav_correctionBackend_CorrectionSystem
 * Method:    getDocumentPointer
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_jav_correctionBackend_CorrectionSystem_getDocumentPointer
  (JNIEnv *, jobject);

/*
 * Class:     jav_correctionBackend_CorrectionSystem
 * Method:    initCorrectionSystem
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_jav_correctionBackend_CorrectionSystem_initCorrectionSystem
  (JNIEnv *, jobject);

/*
 * Class:     jav_correctionBackend_CorrectionSystem
 * Method:    native_loadDocument
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_jav_correctionBackend_CorrectionSystem_native_1loadDocument
  (JNIEnv *, jobject, jstring);

/*
 * Class:     jav_correctionBackend_CorrectionSystem
 * Method:    native_newDocument
 * Signature: (Ljava/lang/String;Ljava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_jav_correctionBackend_CorrectionSystem_native_1newDocument
  (JNIEnv *, jobject, jstring, jstring, jint);

#ifdef __cplusplus
}
#endif
#endif
