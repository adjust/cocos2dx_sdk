//
//  AdjustAdRevenue2dx.h
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 14th October 2022.
//  Copyright © 2022-Present Adjust GmbH. All rights reserved.
//

#ifndef ADJUST_ADJUSTADREVENUE2DX_H_
#define ADJUST_ADJUSTADREVENUE2DX_H_

#include "cocos2d.h"
#include <iostream>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "ADJAdRevenue2dx.h"
#endif

class AdjustAdRevenue2dx {
private:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    jobject adRevenue;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    bool isAdRevenueSet;
    ADJAdRevenue2dx adRevenue;
#endif
    void initAdRevenue(std::string source);

public:
    AdjustAdRevenue2dx(std::string source) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        initAdRevenue(source);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        isAdRevenueSet = false;
        initAdRevenue(source);
#endif
    }

    void setRevenue(double amount, std::string currency);
    void setAdImpressionsCount(int transactionId);
    void setAdRevenueNetwork(std::string adRevenueNetwork);
    void setAdRevenueUnit(std::string adRevenueUnit);
    void setAdRevenuePlacement(std::string adRevenuePlacement);
    void addCallbackParameter(std::string key, std::string value);
    void addPartnerParameter(std::string key, std::string value);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    jobject getAdRevenue();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJAdRevenue2dx getAdRevenue();
#endif
};

#endif /* ADJUST_ADJUSTADREVENUE2DX_H_ */
