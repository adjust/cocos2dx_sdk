//
//  AdjustAppStoreSubscription2dx.h
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 12th June 2020.
//  Copyright © 2020-Present Adjust GmbH. All rights reserved.
//

#ifndef ADJUST_ADJUSTAPPSTORESUBSCRIPTION2DX_H_
#define ADJUST_ADJUSTAPPSTORESUBSCRIPTION2DX_H_

#include "cocos2d.h"
#include <iostream>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "ADJAppStoreSubscription2dx.h"
#endif

class AdjustAppStoreSubscription2dx {
private:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    bool isSubscriptionSet;
    ADJAppStoreSubscription2dx subscription;
#endif
    void initSubscription(std::string price, std::string currency, std::string transactionId);

public:
    AdjustAppStoreSubscription2dx(std::string price, std::string currency, std::string transactionId) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        isSubscriptionSet = false;
        initSubscription(price, currency, transactionId);
#endif
    }

    void setTransactionDate(std::string transactionDate);
    void setSalesRegion(std::string salesRegion);
    void addCallbackParameter(std::string key, std::string value);
    void addPartnerParameter(std::string key, std::string value);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAppStoreSubscription2dx getSubscription();
#endif
};

#endif /* ADJUST_ADJUSTAPPSTORESUBSCRIPTION2DX_H_ */
