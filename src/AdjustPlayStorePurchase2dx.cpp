//
//  AdjustPlayStorePurchase2dx.cpp
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 17th January 2024.
//  Copyright © 2024-Present Adjust GmbH. All rights reserved.
//

#include "AdjustPlayStorePurchase2dx.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif

void AdjustPlayStorePurchase2dx::initPurchase(std::string productId, std::string purchaseToken) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo jmiInit;
    if (!cocos2d::JniHelper::getMethodInfo(jmiInit, "com/adjust/sdk/AdjustPlayStorePurchase", "<init>", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        return;
    }

    jclass jclsAdjustPurchase = jmiInit.env->FindClass("com/adjust/sdk/AdjustPlayStorePurchase");
    jmethodID jmidInit = jmiInit.env->GetMethodID(jclsAdjustPurchase, "<init>", "(Ljava/lang/String;Ljava/lang/String;)V");
    jstring jProductId = jmiInit.env->NewStringUTF(productId.c_str());
    jstring jPurchaseToken = jmiInit.env->NewStringUTF(purchaseToken.c_str());
    purchase = jmiInit.env->NewObject(jclsAdjustPurchase, jmidInit, jProductId, jPurchaseToken);
    jmiInit.env->DeleteLocalRef(jProductId);
    jmiInit.env->DeleteLocalRef(jPurchaseToken);
#endif
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
jobject AdjustPlayStorePurchase2dx::getPurchase() {
    return purchase;
}
#endif
