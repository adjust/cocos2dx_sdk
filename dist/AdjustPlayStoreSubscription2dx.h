//
//  AdjustPlayStoreSubscription2dx.h
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 12th June 2020.
//  Copyright © 2020-Present Adjust GmbH. All rights reserved.
//

#ifndef ADJUST_ADJUSTPLAYSTORESUBSCRIPTION2DX_H_
#define ADJUST_ADJUSTPLAYSTORESUBSCRIPTION2DX_H_

#include "cocos2d.h"
#include <iostream>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#endif

class AdjustPlayStoreSubscription2dx {
private:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    jobject subscription;
#endif
    void initSubscription(
        std::string price,
        std::string currency,
        std::string sku,
        std::string orderId,
        std::string signature,
        std::string purchaseToken
    );

public:
    AdjustPlayStoreSubscription2dx(
        std::string price,
        std::string currency,
        std::string sku,
        std::string orderId,
        std::string signature,
        std::string purchaseToken
    ) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        initSubscription(price, currency, sku, orderId, signature, purchaseToken);
#endif
    }

    void setPurchaseTime(std::string purchaseTime);
    void addCallbackParameter(std::string key, std::string value);
    void addPartnerParameter(std::string key, std::string value);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    jobject getSubscription();
#endif
};

#endif /* ADJUST_ADJUSTPLAYSTORESUBSCRIPTION2DX_H_ */
