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

extern const std::string AdjustEnvironmentSandbox2dx;
extern const std::string AdjustEnvironmentProduction2dx;

class Adjust2dx {
public:
    static void start(AdjustConfig2dx adjustConfig);
    static void trackEvent(AdjustEvent2dx event);
    static void setEnabled(bool isEnabled);
    static bool isEnabled();
    static void setOfflineMode(bool isOffline);
    static void appWillOpenUrl(std::string url);
    static void setDeviceToken(std::string deviceToken);
    static void sendFirstPackages();
    static void gdprForgetMe();
    static void addSessionCallbackParameter(std::string key, std::string value);
    static void addSessionPartnerParameter(std::string key, std::string value);
    static void removeSessionCallbackParameter(std::string key);
    static void removeSessionPartnerParameter(std::string key);
    static void resetSessionCallbackParameters();
    static void resetSessionPartnerParameters();
    static void trackAdRevenue(std::string source, std::string payload);
    static void disableThirdPartySharing();
    static void trackThirdPartySharing(AdjustThirdPartySharing2dx thirdPartySharing);
    static void trackMeasurementConsent(bool measurementConsent);
    static std::string getAdid();
    static std::string getSdkVersion();
    static AdjustAttribution2dx getAttribution();
    static void trackAdRevenueNew(AdjustAdRevenue2dx adRevenue);
    static void processDeeplink(std::string url, void (*resolvedLinkCallback)(std::string resolvedLink));
    // Android specific methods.
    static void setReferrer(std::string referrer);
    static void getGoogleAdId(void (*adIdCallback)(std::string adId));
    static std::string getAmazonAdId();
    static void onResume();
    static void onPause();
    static void trackPlayStoreSubscription(AdjustPlayStoreSubscription2dx subscription);
    static void verifyPlayStorePurchase(AdjustPlayStorePurchase2dx purchase, void (*verificationCallback)(std::string verificationStatus, int code, std::string message));
    // iOS specific methods.
    static std::string getIdfa();
    static void trackAppStoreSubscription(AdjustAppStoreSubscription2dx subscription);
    static void requestTrackingAuthorizationWithCompletionHandler(void (*trackingStatusCallback)(int status));
    static int getAppTrackingAuthorizationStatus();
    static void updateConversionValue(int conversionValue);
    static void updatePostbackConversionValue(int conversionValue, void (*errorCallback)(std::string error));
    static void updatePostbackConversionValue(int conversionValue, std::string coarseValue, void (*errorCallback)(std::string error));
    static void updatePostbackConversionValue(int conversionValue, std::string coarseValue, bool lockWindow, void (*errorCallback)(std::string error));
    static void checkForNewAttStatus();
    static std::string getLastDeeplink();
    static void verifyAppStorePurchase(AdjustAppStorePurchase2dx purchase, void (*verificationCallback)(std::string verificationStatus, int code, std::string message));
    static std::string getIdfv();
    // For testing purposes only.
    static void setTestOptions(std::map<std::string, std::string> testOptions);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    static void teardown();
#endif
};

#endif /* ADJUST_ADJUST2DX_H_ */
