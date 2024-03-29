//
//  AdjustConfig2dx.h
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 16th June 2015.
//  Copyright © 2015-2019 Adjust GmbH. All rights reserved.
//

#ifndef ADJUST_ADJUSTCONFIG2DX_H_
#define ADJUST_ADJUSTCONFIG2DX_H_

#include "cocos2d.h"
#include <iostream>
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
extern const std::string AdjustUrlStrategyChina;
extern const std::string AdjustUrlStrategyIndia;
extern const std::string AdjustUrlStrategyCn;
extern const std::string AdjustUrlStrategyCnOnly;
extern const std::string AdjustDataResidencyEU;
extern const std::string AdjustDataResidencyTR;
extern const std::string AdjustDataResidencyUS;
extern const std::string AdjustAdRevenueSourceAppLovinMAX;
extern const std::string AdjustAdRevenueSourceMopub;
extern const std::string AdjustAdRevenueSourceAdMob;
extern const std::string AdjustAdRevenueSourceIronSource;
extern const std::string AdjustAdRevenueSourceAdMostSource;
extern const std::string AdjustAdRevenueSourceUnity;
extern const std::string AdjustAdRevenueSourceHeliumChartboost;
extern const std::string AdjustAdRevenueSourcePublisher;
extern const std::string AdjustAdRevenueSourceTopOn;
extern const std::string AdjustAdRevenueSourceAdx;

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

    void setDeviceKnown(bool isDeviceKnown);
    void setSendInBackground(bool isEnabled);
    void setEventBufferingEnabled(bool isEnabled);
    void setNeedsCost(bool needsCost);
    void setUserAgent(std::string userAgent);
    void setProcessName(std::string processName);
    void setDefaultTracker(std::string defaultTracker);
    void setExternalDeviceId(std::string externalDeviceId);
    void setUrlStrategy(std::string urlStrategy);
    void setDelayStart(double delayStart);    
    void setLogLevel(AdjustLogLevel2dx logLevel, void(*logCallback)(const char* log) = NULL);
    void setAppSecret(unsigned long long secretId, unsigned long long info1, unsigned long long info2, unsigned long long info3, unsigned long long info4);
    void setAttributionCallback(void(*attributionCallback)(AdjustAttribution2dx attribution));
    void setEventSuccessCallback(void(*eventSuccessCallback)(AdjustEventSuccess2dx eventSuccess));
    void setEventFailureCallback(void(*eventFailureCallback)(AdjustEventFailure2dx eventFailure));
    void setSessionSuccessCallback(void(*sessionSuccessCallback)(AdjustSessionSuccess2dx sessionSuccess));
    void setSessionFailureCallback(void(*sessionFailureCallback)(AdjustSessionFailure2dx sessionFailure));
    void setDeferredDeeplinkCallback(bool(*deferredDeeplinkCallback)(std::string deeplink));
    void setCoppaCompliantEnabled(bool isEnabled);
    void setReadDeviceInfoOnceEnabled(bool isEnabled);
    // iOS only
    void deactivateSkAdNetworkHandling();
    void setAllowIdfaReading(bool isAllowed);
    void setAllowiAdInfoReading(bool isAllowed);
    void setAllowAdServicesInfoReading(bool isAllowed);
    void setConversionValueUpdatedCallback(void(*conversionValueUpdatedCallback)(int conversionValue));
    void setPostbackConversionValueUpdatedCallback(void(*postbackConversionValueUpdatedCallback)(int conversionValue, std::string coarseValue, bool lockWindow));
    void setLinkMeEnabled(bool isEnabled);
    void setAttConsentWaitingInterval(int numberOfSeconds);
    // Android only
    void setReadMobileEquipmentIdentity(bool readMobileEquipmentIdentity);
    void setPreinstallTrackingEnabled(bool isEnabled);
    void setPreinstallFilePath(std::string filePath);
    void setPlayStoreKidsAppEnabled(bool isEnabled);
    void setFinalAttributionEnabled(bool isEnabled);
    void setFbAppId(std::string fbAppId);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    jobject getConfig();
};
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJConfig2dx getConfig();
};
#endif

#endif /* ADJUST_ADJUSTCONFIG2DX_H_ */
