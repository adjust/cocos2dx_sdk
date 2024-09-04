//
//  Adjust2dx.h
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 16th June 2015.
//  Copyright © 2015-2020 Adjust GmbH. All rights reserved.
//

#ifndef ADJUST_ADJUST2DX_H_
#define ADJUST_ADJUST2DX_H_

#include <map>
#include <iostream>
#include "AdjustEvent2dx.h"
#include "AdjustConfig2dx.h"
#include "AdjustAttribution2dx.h"
#include "AdjustAppStoreSubscription2dx.h"
#include "AdjustPlayStoreSubscription2dx.h"
#include "AdjustThirdPartySharing2dx.h"
#include "AdjustAdRevenue2dx.h"
#include "AdjustPlayStorePurchase2dx.h"
#include "AdjustAppStorePurchase2dx.h"
#include "AdjustDeeplink2dx.h"

extern const std::string AdjustEnvironmentSandbox2dx;
extern const std::string AdjustEnvironmentProduction2dx;

class Adjust2dx {
public:
    static void start(AdjustConfig2dx adjustConfig);
    static void trackEvent(AdjustEvent2dx event);
    static void enable();
    static void disable();
    static void isEnabledCallback(void(*callbackMethod)(bool isEnabled));
    static void switchToOfflineMode();
    static void switchBackToOnlineMode();
    static void processDeeplink(AdjustDeeplink2dx deeplink);
    static void setPushTokenAsString(std::string pushToken);
    static void gdprForgetMe();
    static void addGlobalCallbackParameter(std::string key, std::string value);
    static void addGlobalPartnerParameter(std::string key, std::string value);
    static void removeGlobalCallbackParameter(std::string key);
    static void removeGlobalPartnerParameter(std::string key);
    static void removeGlobalCallbackParameters();
    static void removeGlobalPartnerParameters();
    static void trackThirdPartySharing(AdjustThirdPartySharing2dx thirdPartySharing);
    static void trackMeasurementConsent(bool measurementConsent);
    static void adidCallback(void(*callbackMethod)(std::string adid));
    static void sdkVersionCallback(void(*callbackMethod)(std::string sdkVersion));
    static void attributionCallback(void(*callbackMethod)(AdjustAttribution2dx attribution));
    static void trackAdRevenueNew(AdjustAdRevenue2dx adRevenue);
    static void processAndResolveDeeplink(AdjustDeeplink2dx deeplink,
                                          void (*resolvedLinkCallback)(std::string resolvedLink));
    // Android specific methods.
    static void setReferrer(std::string referrer);
    static void getGoogleAdId(void (*callbackMethod)(std::string adId));
    static void getAmazonAdId(void (*callbackMethod)(std::string adId));
    static void onResume();
    static void onPause();
    static void trackPlayStoreSubscription(AdjustPlayStoreSubscription2dx subscription);
    static void verifyPlayStorePurchase(AdjustPlayStorePurchase2dx purchase, void (*verificationCallback)(std::string verificationStatus, int code, std::string message));
    static void verifyAndTrackPlayStorePurchase(AdjustEvent2dx event, void (*verificationCallback)(std::string verificationStatus, int code, std::string message));
    // iOS specific methods.
    static void idfaCallback(void(*callbackMethod)(std::string idfa));
    static void trackAppStoreSubscription(AdjustAppStoreSubscription2dx subscription);
    static void requestAppTrackingAuthorizationWithCompletionHandler(void (*trackingStatusCallback)(int status));
    static int getAppTrackingAuthorizationStatus();
    static void updateSkanConversionValue(int conversionValue,
                                          std::string coarseValue,
                                          bool* optionalLockWindow,
                                          void (*errorCallback)(std::string error));
    static void lastDeeplinkCallback(void(*callbackMethod)(std::string lastDeeplink));
    static void verifyAppStorePurchase(AdjustAppStorePurchase2dx purchase, void (*verificationCallback)(std::string verificationStatus, int code, std::string message));
    static void verifyAndTrackAppStorePurchase(AdjustEvent2dx event, void (*verificationCallback)(std::string verificationStatus, int code, std::string message));
    static void idfvCallback(void(*callbackMethod)(std::string idfv));
    // For testing purposes only.
    static void setTestOptions(std::map<std::string, std::string> stringTestOptions, std::map<std::string, int> intTestOptions);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    static void teardown();
#endif
};

#endif /* ADJUST_ADJUST2DX_H_ */
