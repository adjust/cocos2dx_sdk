//
//  AdjustAppStorePurchase2dx.h
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 17th January 2024.
//  Copyright © 2024-Present Adjust GmbH. All rights reserved.
//

#ifndef ADJUST_ADJUSTAPPSTOREPURCHASE2DX_H_
#define ADJUST_ADJUSTAPPSTOREPURCHASE2DX_H_

#include "cocos2d.h"
#include <iostream>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "ADJAppStorePurchase2dx.h"
#endif

class AdjustAppStorePurchase2dx {
private:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    bool isPurchaseSet;
    ADJAppStorePurchase2dx purchase;
#endif
    void initPurchase(std::string productId, std::string transactionId);

public:
    AdjustAppStorePurchase2dx(std::string productId, std::string transactionId) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        isPurchaseSet = false;
        initPurchase(productId, transactionId);
#endif
    }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAppStorePurchase2dx getPurchase();
#endif
};

#endif /* ADJUST_ADJUSTAPPSTOREPURCHASE2DX_H_ */
