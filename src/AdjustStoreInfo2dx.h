//
//  AdjustStoreInfo2dx.h
//  Adjust SDK
//
//  Created by Ugljesa Erceg (@uerceg) on 5th June 2025.
//  Copyright © 2025-Present Adjust GmbH. All rights reserved.
//

#ifndef ADJUST_ADJUSTSTOREINFO2DX_H_
#define ADJUST_ADJUSTSTOREINFO2DX_H_

#include "cocos2d.h"
#include <iostream>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "ADJStoreInfo2dx.h"
#endif

class AdjustStoreInfo2dx {
private:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    jobject storeInfo;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    bool isStoreInfoSet;
    ADJStoreInfo2dx storeInfo;
#endif
    void initStoreInfo(std::string storeName);

public:
    AdjustStoreInfo2dx(std::string storeName) {
        initStoreInfo(storeName);
    }

    void setStoreAppId(std::string storeAppId);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    jobject getStoreInfo();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJStoreInfo2dx getStoreInfo();
#endif
};

#endif /* ADJUST_ADJUSTSTOREINFO2DX_H_ */
