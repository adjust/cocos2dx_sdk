//
//  ADJAdjust2dx.h
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 17th June 2015.
//  Copyright © 2015-2019 Adjust GmbH. All rights reserved.
//

#ifndef _ADJUST_ADJADJUST2DX_H_
#define _ADJUST_ADJADJUST2DX_H_

#include <map>
#include <iostream>
#include "ADJEvent2dx.h"
#include "ADJConfig2dx.h"
#include "ADJAppStoreSubscription2dx.h"
#include "ADJThirdPartySharing2dx.h"
#include "ADJAdRevenue2dx.h"
#include "ADJAppStorePurchase2dx.h"
#include "AdjustAttribution2dx.h"

extern const std::string ADJEnvironmentSandbox2dx;
extern const std::string ADJEnvironmentProduction2dx;

class ADJAdjust2dx {
public:
    static void initSdk(ADJConfig2dx adjustConfig);
    static void trackEvent(ADJEvent2dx adjustEvent);
    static void trackAppStoreSubscription(ADJAppStoreSubscription2dx subscription);
    static void trackSubsessionStart();
    static void trackSubsessionEnd();
    static void enable();
    static void disable();
    static void processDeeplink(std::string url);
    static void setPushTokenAsString(std::string pushToken);
    static void switchToOfflineMode();
    static void switchBackToOnlineMode();
    static void gdprForgetMe();
    static void addGlobalCallbackParameter(std::string key, std::string value);
    static void addGlobalPartnerParameter(std::string key, std::string value);
    static void removeGlobalCallbackParameter(std::string key);
    static void removeGlobalPartnerParameter(std::string key);
    static void removeGlobalCallbackParameters();
    static void removeGlobalPartnerParameters();
    static void trackAdRevenueNew(ADJAdRevenue2dx adRevenue);
    static void isEnabledCallback(void(*callbackMethod)(bool isEnabled));
    static void idfaCallback(void(*callbackMethod)(std::string idfa));
    static void adidCallback(void(*callbackMethod)(std::string adid));
    static void sdkVersionCallback(void(*callbackMethod)(std::string sdkVersion));
    static void attributionCallback(void(*callbackMethod)(AdjustAttribution2dx attribution));
    static void requestAppTrackingAuthorizationWithCompletionHandler(void (*trackingStatusCallback)(int status));
    static int getAppTrackingAuthorizationStatus();
    static void trackThirdPartySharing(ADJThirdPartySharing2dx thirdPartySharing);
    static void trackMeasurementConsent(bool measurementConsent);
    static void updateSkanConversionValue(int conversionValue,
                                          std::string coarseValue,
                                          bool* optionalLockWindow,
                                          void (*errorCallback)(std::string error));
    static void lastDeeplinkCallback(void(*callbackMethod)(std::string lastDeeplink));
    static void verifyAppStorePurchase(ADJAppStorePurchase2dx purchase, void (*verificationCallback)(std::string verificationStatus, int code, std::string message));
    static void verifyAndTrackAppStorePurchase(ADJEvent2dx adjustEvent, void (*verificationCallback)(std::string verificationStatus, int code, std::string message));
    static void idfvCallback(void(*callbackMethod)(std::string idfv));
    static void processAndResolveDeeplink(std::string url, void (*resolvedLinkCallback)(std::string resolvedLink));
    // For testing purposes only.
    static void setTestOptions(std::map<std::string, std::string> testOptionsMap);
    static void teardown();
};

#endif /* _ADJUST_ADJADJUST2DX_H_ */
