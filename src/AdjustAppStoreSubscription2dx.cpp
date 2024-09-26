//
//  AdjustAppStoreSubscription2dx.cpp
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 12th June 2020.
//  Copyright © 2020-Present Adjust GmbH. All rights reserved.
//

#include "AdjustAppStoreSubscription2dx.h"

void AdjustAppStoreSubscription2dx::initSubscription(
    std::string price,
    std::string currency,
    std::string transactionId)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    subscription = ADJAppStoreSubscription2dx(price, currency, transactionId);
    isSubscriptionSet = true;
#endif
}

void AdjustAppStoreSubscription2dx::setTransactionDate(std::string transactionDate) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isSubscriptionSet) {
        subscription.setTransactionDate(transactionDate);
    }
#endif
}

void AdjustAppStoreSubscription2dx::setSalesRegion(std::string salesRegion) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isSubscriptionSet) {
        subscription.setSalesRegion(salesRegion);
    }
#endif
}

void AdjustAppStoreSubscription2dx::addCallbackParameter(std::string key, std::string value) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isSubscriptionSet) {
        subscription.addCallbackParameter(key, value);
    }
#endif
}

void AdjustAppStoreSubscription2dx::addPartnerParameter(std::string key, std::string value) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (isSubscriptionSet) {
        subscription.addPartnerParameter(key, value);
    }
#endif
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
ADJAppStoreSubscription2dx AdjustAppStoreSubscription2dx::getSubscription() {
    return subscription;
}
#endif
