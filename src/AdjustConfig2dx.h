//
//  AdjustConfig2dx.h
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 16th June 2015.
//  Copyright © 2015-2019 Adjust GmbH. All rights reserved.
//

#ifndef ADJUST_ADJUSTCONFIG2DX_H_
#define ADJUST_ADJUSTCONFIG2DX_H_

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "ADJConfig2dx.h"
#endif

#include <iostream>
#include "AdjustAttribution2dx.h"
#include "AdjustEventFailure2dx.h"
#include "AdjustEventSuccess2dx.h"
#include "AdjustSessionSuccess2dx.h"
#include "AdjustSessionFailure2dx.h"

extern const std::string AdjustSdkPrefix2dx;

enum AdjustLogLevel2dx {
    AdjustLogLevel2dxVerbose = 1,
    AdjustLogLevel2dxDebug = 2,
    AdjustLogLevel2dxInfo = 3,
    AdjustLogLevel2dxWarn = 4,
    AdjustLogLevel2dxError = 5,
    AdjustLogLevel2dxAssert = 6,
    AdjustLogLevel2dxSuppress = 7 };

class AdjustConfig2dx {
private:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    jobject config;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    bool isConfigSet;
    ADJConfig2dx config;
#endif
    void initConfig(std::string appToken, std::string environment, bool allowSuppressLogLevel);

public:
    AdjustConfig2dx() {}

    AdjustConfig2dx(std::string appToken, std::string environment) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        initConfig(appToken, environment, false);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        isConfigSet = false;
        initConfig(appToken, environment, false);
#endif
    }

    AdjustConfig2dx(std::string appToken, std::string environment, bool allowSuppressLogLevel) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        initConfig(appToken, environment, allowSuppressLogLevel);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        isConfigSet = false;
        initConfig(appToken, environment, allowSuppressLogLevel);
#endif
    }

    void setDeviceKnown(bool isDeviceKnown);
    void setSendInBackground(bool isEnabled);
    void setEventBufferingEnabled(bool isEnabled);
    void setReadMobileEquipmentIdentity(bool readMobileEquipmentIdentity);
    void setUserAgent(std::string userAgent);
    void setProcessName(std::string processName);
    void setDefaultTracker(std::string defaultTracker);
    void setDelayStart(double delayStart);    
    void setLogLevel(AdjustLogLevel2dx logLevel, void(*logCallback)(const char* log) = NULL);
    void setAppSecret(unsigned long long secretId, unsigned long long info1, unsigned long long info2, unsigned long long info3, unsigned long long info4);
    void setAttributionCallback(void(*attributionCallback)(AdjustAttribution2dx attribution));
    void setEventSuccessCallback(void(*eventSuccessCallback)(AdjustEventSuccess2dx eventSuccess));
    void setEventFailureCallback(void(*eventFailureCallback)(AdjustEventFailure2dx eventFailure));
    void setSessionSuccessCallback(void(*sessionSuccessCallback)(AdjustSessionSuccess2dx sessionSuccess));
    void setSessionFailureCallback(void(*sessionFailureCallback)(AdjustSessionFailure2dx sessionFailure));
    void setDeferredDeeplinkCallback(bool(*deferredDeeplinkCallback)(std::string deeplink));

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    jobject getConfig();
};
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJConfig2dx getConfig();
};
#endif

#endif /* ADJUST_ADJUSTCONFIG2DX_H_ */
