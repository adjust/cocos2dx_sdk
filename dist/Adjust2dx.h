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
#include <functional>
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
    [[deprecated("This method does not support lambda captures. Use the std::function overload instead.")]]
    static void isEnabled(void(*callback)(bool isEnabled));
    static void isEnabled(std::function<void(bool)> callback);
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
    [[deprecated("This method does not support lambda captures. Use the std::function overload instead.")]]
    static void getAdid(void(*callback)(std::string adid));
    static void getAdid(std::function<void(std::string)> callback);
    [[deprecated("This method does not support lambda captures. Use the std::function overload instead.")]]
    static void getAdidWithTimeout(int timeoutInMilliseconds, void(*callback)(std::string adid));
    static void getAdidWithTimeout(int timeoutInMilliseconds, std::function<void(std::string)> callback);
    [[deprecated("This method does not support lambda captures. Use the std::function overload instead.")]]
    static void getSdkVersion(void(*callback)(std::string sdkVersion));
    static void getSdkVersion(std::function<void(std::string)> callback);
    [[deprecated("This method does not support lambda captures. Use the std::function overload instead.")]]
    static void getAttribution(void(*callback)(AdjustAttribution2dx attribution));
    static void getAttribution(std::function<void(AdjustAttribution2dx)> callback);
    [[deprecated("This method does not support lambda captures. Use the std::function overload instead.")]]
    static void getAttributionWithTimeout(int timeoutInMilliseconds, void(*callback)(AdjustAttribution2dx attribution));
    static void getAttributionWithTimeout(int timeoutInMilliseconds, std::function<void(AdjustAttribution2dx)> callback);
    static void trackAdRevenue(AdjustAdRevenue2dx adRevenue);
    [[deprecated("This method does not support lambda captures. Use the std::function overload instead.")]]
    static void processAndResolveDeeplink(AdjustDeeplink2dx deeplink,
                                          void (*resolvedLinkCallback)(std::string resolvedLink));
    static void processAndResolveDeeplink(AdjustDeeplink2dx deeplink,
                                          std::function<void(std::string)> resolvedLinkCallback);
    [[deprecated("This method does not support lambda captures. Use the std::function overload instead.")]]
    static void getLastDeeplink(void(*callback)(std::string lastDeeplink));
    static void getLastDeeplink(std::function<void(std::string)> callback);
    static void endFirstSessionDelay();
    static void enableCoppaComplianceInDelay();
    static void disableCoppaComplianceInDelay();
    static void setExternalDeviceIdInDelay(std::string);
    // androind only
    [[deprecated("This method does not support lambda captures. Use the std::function overload instead.")]]
    static void getGoogleAdId(void (*callback)(std::string googleAdId));
    static void getGoogleAdId(std::function<void(std::string)> callback);
    [[deprecated("This method does not support lambda captures. Use the std::function overload instead.")]]
    static void getAmazonAdId(void (*callback)(std::string amazonAdId));
    static void getAmazonAdId(std::function<void(std::string)> callback);
    static void trackPlayStoreSubscription(AdjustPlayStoreSubscription2dx subscription);
    [[deprecated("This method does not support lambda captures. Use the std::function overload instead.")]]
    static void verifyPlayStorePurchase(AdjustPlayStorePurchase2dx purchase, void(*callback)(AdjustPurchaseVerificationResult2dx verificationResult));
    static void verifyPlayStorePurchase(AdjustPlayStorePurchase2dx purchase, std::function<void(AdjustPurchaseVerificationResult2dx)> callback);
    [[deprecated("This method does not support lambda captures. Use the std::function overload instead.")]]
    static void verifyAndTrackPlayStorePurchase(AdjustEvent2dx event, void(*callback)(AdjustPurchaseVerificationResult2dx verificationResult));
    static void verifyAndTrackPlayStorePurchase(AdjustEvent2dx event, std::function<void(AdjustPurchaseVerificationResult2dx)> callback);
    static void enablePlayStoreKidsComplianceInDelay();
    static void disablePlayStoreKidsComplianceInDelay();
    // ios only
    [[deprecated("This method does not support lambda captures. Use the std::function overload instead.")]]
    static void getIdfa(void(*callback)(std::string idfa));
    static void getIdfa(std::function<void(std::string)> callback);
    static void trackAppStoreSubscription(AdjustAppStoreSubscription2dx subscription);
    [[deprecated("This method does not support lambda captures. Use the std::function overload instead.")]]
    static void requestAppTrackingAuthorization(void (*callback)(int status));
    static void requestAppTrackingAuthorization(std::function<void(int)> callback);
    static int getAppTrackingAuthorizationStatus();
    [[deprecated("This method does not support lambda captures. Use the std::function overload instead.")]]
    static void updateSkanConversionValue(int conversionValue,
                                          std::string coarseValue,
                                          bool lockWindow,
                                          void (*callback)(std::string error));
    static void updateSkanConversionValue(int conversionValue,
                                          std::string coarseValue,
                                          bool lockWindow,
                                          std::function<void(std::string)> callback);
    [[deprecated("This method does not support lambda captures. Use the std::function overload instead.")]]
    static void verifyAppStorePurchase(AdjustAppStorePurchase2dx purchase, void(*callback)(AdjustPurchaseVerificationResult2dx verificationResult));
    static void verifyAppStorePurchase(AdjustAppStorePurchase2dx purchase, std::function<void(AdjustPurchaseVerificationResult2dx)> callback);
    [[deprecated("This method does not support lambda captures. Use the std::function overload instead.")]]
    static void verifyAndTrackAppStorePurchase(AdjustEvent2dx event, void(*callback)(AdjustPurchaseVerificationResult2dx verificationResult));
    static void verifyAndTrackAppStorePurchase(AdjustEvent2dx event, std::function<void(AdjustPurchaseVerificationResult2dx)> callback);
    [[deprecated("This method does not support lambda captures. Use the std::function overload instead.")]]
    static void getIdfv(void(*callback)(std::string idfv));
    static void getIdfv(std::function<void(std::string)> callback);
    // testing only
    static void onResume();
    static void onPause();
    static void setTestOptions(std::map<std::string, std::string> stringTestOptions, std::map<std::string, int> intTestOptions);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    static void teardown();
#endif
};

#endif /* ADJUST_ADJUST2DX_H_ */
