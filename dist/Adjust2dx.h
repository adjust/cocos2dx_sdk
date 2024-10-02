//
//  Adjust2dx.h
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 16th June 2015.
//  Copyright © 2015-Present Adjust GmbH. All rights reserved.
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
#include "AdjustPurchaseVerificationResult2dx.h"

extern const std::string AdjustEnvironmentSandbox2dx;
extern const std::string AdjustEnvironmentProduction2dx;

class Adjust2dx {
public:
    static void initSdk(AdjustConfig2dx adjustConfig);
    static void trackEvent(AdjustEvent2dx event);
    static void enable();
    static void disable();
    static void isEnabled(void(*callback)(bool isEnabled));
    static void switchToOfflineMode();
    static void switchBackToOnlineMode();
    static void processDeeplink(AdjustDeeplink2dx deeplink);
    static void setPushToken(std::string pushToken);
    static void gdprForgetMe();
    static void addGlobalCallbackParameter(std::string key, std::string value);
    static void addGlobalPartnerParameter(std::string key, std::string value);
    static void removeGlobalCallbackParameter(std::string key);
    static void removeGlobalPartnerParameter(std::string key);
    static void removeGlobalCallbackParameters();
    static void removeGlobalPartnerParameters();
    static void trackThirdPartySharing(AdjustThirdPartySharing2dx thirdPartySharing);
    static void trackMeasurementConsent(bool measurementConsent);
    static void getAdid(void(*callback)(std::string adid));
    static void getSdkVersion(void(*callback)(std::string sdkVersion));
    static void getAttribution(void(*callback)(AdjustAttribution2dx attribution));
    static void trackAdRevenue(AdjustAdRevenue2dx adRevenue);
    static void processAndResolveDeeplink(AdjustDeeplink2dx deeplink,
                                          void (*resolvedLinkCallback)(std::string resolvedLink));
    // Android specific methods.
    static void getGoogleAdId(void (*callback)(std::string googleAdId));
    static void getAmazonAdId(void (*callback)(std::string amazonAdId));
    static void trackPlayStoreSubscription(AdjustPlayStoreSubscription2dx subscription);
    static void verifyPlayStorePurchase(AdjustPlayStorePurchase2dx purchase, void(*callback)(AdjustPurchaseVerificationResult2dx verificationResult));
    static void verifyAndTrackPlayStorePurchase(AdjustEvent2dx event, void(*callback)(AdjustPurchaseVerificationResult2dx verificationResult));
    // iOS specific methods.
    static void getIdfa(void(*callback)(std::string idfa));
    static void trackAppStoreSubscription(AdjustAppStoreSubscription2dx subscription);
    static void requestAppTrackingAuthorization(void (*callback)(int status));
    static int getAppTrackingAuthorizationStatus();
    static void updateSkanConversionValue(int conversionValue,
                                          std::string coarseValue,
                                          bool lockWindow,
                                          void (*callback)(std::string error));
    static void getLastDeeplink(void(*callback)(std::string lastDeeplink));
    static void verifyAppStorePurchase(AdjustAppStorePurchase2dx purchase, void(*callback)(AdjustPurchaseVerificationResult2dx verificationResult));
    static void verifyAndTrackAppStorePurchase(AdjustEvent2dx event, void(*callback)(AdjustPurchaseVerificationResult2dx verificationResult));
    static void getIdfv(void(*callback)(std::string idfv));
    // For testing purposes only.
    static void setTestOptions(std::map<std::string, std::string> stringTestOptions, std::map<std::string, int> intTestOptions);
    static void onResume();
    static void onPause();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    static void teardown();
#endif
};

#endif /* ADJUST_ADJUST2DX_H_ */
