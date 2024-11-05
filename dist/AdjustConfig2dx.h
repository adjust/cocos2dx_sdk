//
//  AdjustConfig2dx.h
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 16th June 2015.
//  Copyright © 2015-Present Adjust GmbH. All rights reserved.
//

#ifndef ADJUST_ADJUSTCONFIG2DX_H_
#define ADJUST_ADJUSTCONFIG2DX_H_

#include "cocos2d.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include "AdjustAttribution2dx.h"
#include "AdjustEventFailure2dx.h"
#include "AdjustEventSuccess2dx.h"
#include "AdjustSessionSuccess2dx.h"
#include "AdjustSessionFailure2dx.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "ADJConfig2dx.h"
#endif

extern const std::string AdjustSdkPrefix2dx;

enum AdjustLogLevel2dx {
    AdjustLogLevel2dxVerbose = 1,
    AdjustLogLevel2dxDebug = 2,
    AdjustLogLevel2dxInfo = 3,
    AdjustLogLevel2dxWarn = 4,
    AdjustLogLevel2dxError = 5,
    AdjustLogLevel2dxAssert = 6,
    AdjustLogLevel2dxSuppress = 7
};

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

    void enableSendingInBackground();
    void enableCostDataInAttribution();
    void setProcessName(std::string processName);
    void setDefaultTracker(std::string defaultTracker);
    void setExternalDeviceId(std::string externalDeviceId);
    void setUrlStrategy(std::vector<std::string> urlStrategyDomains,
                        bool useSubdomains,
                        bool isDataResidency);
    void setLogLevel(AdjustLogLevel2dx logLevel, void(*logCallback)(const char* log) = NULL);
    void setAttributionCallback(void(*attributionCallback)(AdjustAttribution2dx attribution));
    void setEventSuccessCallback(void(*eventSuccessCallback)(AdjustEventSuccess2dx eventSuccess));
    void setEventFailureCallback(void(*eventFailureCallback)(AdjustEventFailure2dx eventFailure));
    void setSessionSuccessCallback(void(*sessionSuccessCallback)(AdjustSessionSuccess2dx sessionSuccess));
    void setSessionFailureCallback(void(*sessionFailureCallback)(AdjustSessionFailure2dx sessionFailure));
    void setDeferredDeeplinkCallback(bool(*deferredDeeplinkCallback)(std::string deeplink));
    void enableDeviceIdsReadingOnce();
    void enableCoppaCompliance();
    void setEventDeduplicationIdsMaxSize(int eventDeduplicationIdsMaxSize);
    void disableSkanAttribution();
    void disableIdfaReading();
    void disableIdfvReading();
    void disableAdServices();
    void setSkanUpdatedCallback(void (*skanUpdatedCallback)(std::unordered_map<std::string, std::string> data));
    void enableLinkMe();
    void setAttConsentWaitingInterval(int numberOfSeconds);
    // Android only
    void enablePreinstallTracking();
    void setPreinstallFilePath(std::string filePath);
    void enablePlayStoreKidsCompliance();
    void setFbAppId(std::string fbAppId);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    jobject getConfig();
};
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJConfig2dx getConfig();
};
#endif

#endif /* ADJUST_ADJUSTCONFIG2DX_H_ */
