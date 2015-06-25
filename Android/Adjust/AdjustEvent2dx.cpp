/*
 * AdjustEvent2dx.cpp
 *
 *  Created on: Jun 16, 2015
 *      Author: uerceg
 */

#include "Adjust/AdjustEvent2dx.h"

#include <jni.h>
#include "platform/android/jni/JniHelper.h"


void AdjustEvent2dx::initEvent(std::string eventToken) {
	cocos2d::JniMethodInfo methodInfo;

	if (cocos2d::JniHelper::getMethodInfo(methodInfo, "com/adjust/sdk/AdjustEvent", "<init>", "(Ljava/lang/String;)V")) {
		jclass cls = methodInfo.env->FindClass("com/adjust/sdk/AdjustEvent");
		jmethodID init = methodInfo.env->GetMethodID(cls, "<init>", "(Ljava/lang/String;)V");
		jstring jtoken = methodInfo.env->NewStringUTF(eventToken.c_str());
		event = methodInfo.env->NewObject(cls, init, jtoken);
	}
}

void AdjustEvent2dx::addCallbackParameter(std::string key, std::string value) {
	cocos2d::JniMethodInfo methodInfo;

	if (NULL != event) {
		if (cocos2d::JniHelper::getMethodInfo(methodInfo, "com/adjust/sdk/AdjustEvent", "addCallbackParameter",
				"(Ljava/lang/String;Ljava/lang/String;)V")) {
			jstring jkey = methodInfo.env->NewStringUTF(key.c_str());
			jstring jvalue = methodInfo.env->NewStringUTF(value.c_str());

			methodInfo.env->CallVoidMethod(event, methodInfo.methodID, jkey, jvalue);
		}
	}
}

void AdjustEvent2dx::addPartnerParameter(std::string key, std::string value) {
	cocos2d::JniMethodInfo methodInfo;

	if (NULL != event) {
		if (cocos2d::JniHelper::getMethodInfo(methodInfo, "com/adjust/sdk/AdjustEvent", "addPartnerParameter",
				"(Ljava/lang/String;Ljava/lang/String;)V")) {
			jstring jkey = methodInfo.env->NewStringUTF(key.c_str());
			jstring jvalue = methodInfo.env->NewStringUTF(value.c_str());

			methodInfo.env->CallVoidMethod(event, methodInfo.methodID, jkey, jvalue);
		}
	}
}

void AdjustEvent2dx::setRevenue(double amount, std::string currency) {
	cocos2d::JniMethodInfo methodInfo;

	if (NULL != event) {
		if (cocos2d::JniHelper::getMethodInfo(methodInfo, "com/adjust/sdk/AdjustEvent", "setRevenue",
				"(DLjava/lang/String;)V")) {
			jstring jcurrency = methodInfo.env->NewStringUTF(currency.c_str());

			methodInfo.env->CallVoidMethod(event, methodInfo.methodID, amount, jcurrency);
		}
	}
}

void AdjustEvent2dx::setTransactionId(std::string transactionId) {
	cocos2d::JniMethodInfo methodInfo;

	if (NULL != event) {
		if (cocos2d::JniHelper::getMethodInfo(methodInfo, "com/adjust/sdk/AdjustEvent", "setTransactionId",
				"(Ljava/lang/String;)V")) {
			jstring jtransactionId = methodInfo.env->NewStringUTF(transactionId.c_str());

			methodInfo.env->CallVoidMethod(event, methodInfo.methodID, jtransactionId);
		}
	}
}

void AdjustEvent2dx::setReceipt(std::string receipt, std::string transactionId) {
	cocos2d::JniMethodInfo methodInfo;

	if (NULL != event) {
		if (cocos2d::JniHelper::getMethodInfo(methodInfo, "com/adjust/sdk/AdjustEvent", "setReceipt",
				"(Ljava/lang/String;Ljava/lang/String;)V")) {
			jstring jreceipt = methodInfo.env->NewStringUTF(receipt.c_str());
			jstring jtransactionId = methodInfo.env->NewStringUTF(transactionId.c_str());

			methodInfo.env->CallVoidMethod(event, methodInfo.methodID, jreceipt, jtransactionId);
		}
	}
}

bool AdjustEvent2dx::isValid() {
	cocos2d::JniMethodInfo methodInfo;

	if (NULL != event) {
		if (cocos2d::JniHelper::getMethodInfo(methodInfo, "com/adjust/sdk/AdjustEvent", "isValid", "()Z")) {
			jboolean jisValid = methodInfo.env->CallBooleanMethod(event, methodInfo.methodID);

			return jisValid;
		}
	}

	return false;
}

jobject AdjustEvent2dx::getEvent() {
	return event;
}
