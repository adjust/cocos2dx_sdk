//
//  AdjustAppStorePurchase2dx.cpp
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 17th January 2024.
//  Copyright © 2015-Present Adjust GmbH. All rights reserved.
//

#include "AdjustAppStorePurchase2dx.h"

void AdjustAppStorePurchase2dx::initPurchase(
    std::string productId,
    std::string transactionId,
    std::string receipt
) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    purchase = ADJAppStorePurchase2dx(productId, transactionId, receipt);
    isPurchaseSet = true;
#endif
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
ADJAppStorePurchase2dx AdjustAppStorePurchase2dx::getPurchase() {
    return purchase;
}
#endif
