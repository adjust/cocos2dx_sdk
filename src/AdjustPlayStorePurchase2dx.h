//
//  AdjustPlayStorePurchase2dx.h
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 17th January 2024.
//  Copyright © 2024-Present Adjust GmbH. All rights reserved.
//

#ifndef ADJUST_ADJUSTPLAYSTOREPURCHASE2DX_H_
#define ADJUST_ADJUSTPLAYSTOREPURCHASE2DX_H_

#include "cocos2d.h"
#include <iostream>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#endif

class AdjustPlayStorePurchase2dx {
private:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    jobject purchase;
#endif
    void initPurchase(std::string productId, std::string purchaseToken);

public:
    AdjustPlayStorePurchase2dx(std::string productId, std::string purchaseToken) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        initPurchase(productId, purchaseToken);
#endif
    }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    jobject getPurchase();
#endif
};

#endif /* ADJUST_ADJUSTPLAYSTOREPURCHASE2DX_H_ */
