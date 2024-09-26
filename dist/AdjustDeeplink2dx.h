//
//  AdjustDeeplink2dx.h
//  Adjust SDK
//
//  Created by Pedro Silva (@nonelse) on 30th August 2024.
//  Copyright © 2024-Present Adjust GmbH. All rights reserved.
//

#ifndef ADJUST_ADJUSTDEEPLINK2DX_H_
#define ADJUST_ADJUSTDEEPLINK2DX_H_

#include "cocos2d.h"
#include <iostream>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "ADJDeeplink2dx.h"
#endif

class AdjustDeeplink2dx {
private:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    jobject deeplink;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    bool isDeeplinkSet;
    ADJDeeplink2dx deeplink;
#endif
    void initDeeplink(std::string deeplinkStr);

public:
    AdjustDeeplink2dx(std::string deeplinkStr) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        initDeeplink(deeplinkStr);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        isDeeplinkSet = false;
        initDeeplink(deeplinkStr);
#endif
    }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    jobject getDeeplink();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJDeeplink2dx getDeeplink();
#endif
};

#endif /* ADJUST_ADJUSTDEEPLINK2DX_H_ */
