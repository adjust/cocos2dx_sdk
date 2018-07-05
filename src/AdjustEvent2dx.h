//
//  AdjustEvent2dx.h
//  Adjust SDK
//
//  Created by Uglješa Erceg on 16/06/15.
//

#ifndef ADJUST_ADJUSTEVENT2DX_H_
#define ADJUST_ADJUSTEVENT2DX_H_

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "ADJEvent2dx.h"
#else
using namespace AdjustWinRT;
#endif

#include <iostream>

class AdjustEvent2dx {
private:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    jobject event;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    bool isEventSet;
    ADJEvent2dx event;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    bool isEventSet;
    WRTAdjustEvent^ event;
#endif
    void initEvent(std::string eventToken);

public:
    AdjustEvent2dx(std::string eventToken) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        initEvent(eventToken);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        isEventSet = false;
        initEvent(eventToken);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
        isEventSet = false;
        initEvent(eventToken);
#endif
    }

    bool isValid();

    void setRevenue(double amount, std::string currency);
    void setTransactionId(std::string transactionId);
    void addCallbackParameter(std::string key, std::string value);
    void addPartnerParameter(std::string key, std::string value);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    jobject getEvent();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJEvent2dx getEvent();
    void setReceipt(std::string receipt, std::string transactionId);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    WRTAdjustEvent^ getEvent();
#endif
};

#endif /* ADJUST_ADJUSTEVENT2DX_H_ */
