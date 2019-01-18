//
//  AdjustEvent2dx.h
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 16th June 2015.
//  Copyright © 2015-2019 Adjust GmbH. All rights reserved.
//

#ifndef ADJUST_ADJUSTEVENT2DX_H_
#define ADJUST_ADJUSTEVENT2DX_H_

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "ADJEvent2dx.h"
#endif

#include <iostream>

class AdjustEvent2dx {
private:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    jobject event;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    bool isEventSet;
    ADJEvent2dx event;
#endif
    void initEvent(std::string eventToken);

public:
    AdjustEvent2dx(std::string eventToken) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        initEvent(eventToken);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        isEventSet = false;
        initEvent(eventToken);
#endif
    }

    bool isValid();
    void setRevenue(double amount, std::string currency);
    void setTransactionId(std::string transactionId);
    void setCallbackId(std::string callbackId);
    void addCallbackParameter(std::string key, std::string value);
    void addPartnerParameter(std::string key, std::string value);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    jobject getEvent();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJEvent2dx getEvent();
    void setReceipt(std::string receipt, std::string transactionId);
#endif
};

#endif /* ADJUST_ADJUSTEVENT2DX_H_ */
