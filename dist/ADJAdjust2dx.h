//
//  ADJAdjust2dx.h
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 17th June 2015.
//  Copyright © 2015-Present Adjust GmbH. All rights reserved.
//

#ifndef _ADJUST_ADJADJUST2DX_H_
#define _ADJUST_ADJADJUST2DX_H_

#include <map>
#include <iostream>
#include "ADJEvent2dx.h"
#include "ADJDeeplink2dx.h"
#include "ADJConfig2dx.h"
#include "ADJAppStoreSubscription2dx.h"
#include "ADJThirdPartySharing2dx.h"
#include "ADJAdRevenue2dx.h"
#include "ADJAppStorePurchase2dx.h"
#include "AdjustAttribution2dx.h"
#include "AdjustPurchaseVerificationResult2dx.h"

extern const std::string ADJEnvironmentSandbox2dx;
extern const std::string ADJEnvironmentProduction2dx;

class ADJAdjust2dx {
public:
    static void initSdk(ADJConfig2dx adjustConfig);
    static void trackEvent(ADJEvent2dx adjustEvent);
    static void trackAppStoreSubscription(ADJAppStoreSubscription2dx subscription);
    static void enable();
    static void disable();
    static void processDeeplink(ADJDeeplink2dx adjustDeeplink);
    static void setPushToken(std::string pushToken);
    static void switchToOfflineMode();
    static void switchBackToOnlineMode();
    static void gdprForgetMe();
    static void addGlobalCallbackParameter(std::string key, std::string value);
    static void addGlobalPartnerParameter(std::string key, std::string value);
    static void removeGlobalCallbackParameter(std::string key);
    static void removeGlobalPartnerParameter(std::string key);
    static void removeGlobalCallbackParameters();
    static void removeGlobalPartnerParameters();
    static void trackAdRevenue(ADJAdRevenue2dx adRevenue);
    static void isEnabled(void(*callback)(bool isEnabled));
    static void getIdfa(void(*callback)(std::string idfa));
    static void getAdid(void(*callback)(std::string adid));
    static void getSdkVersion(void(*callback)(std::string sdkVersion), std::string sdkPrefix);
    static void getAttribution(void(*callback)(AdjustAttribution2dx attribution));
    static void requestAppTrackingAuthorization(void (*callback)(int status));
    static int getAppTrackingAuthorizationStatus();
    static void trackThirdPartySharing(ADJThirdPartySharing2dx thirdPartySharing);
    static void trackMeasurementConsent(bool measurementConsent);
    static void updateSkanConversionValue(int conversionValue,
                                          std::string coarseValue,
                                          bool lockWindow,
                                          void (*callback)(std::string error));
    static void getLastDeeplink(void(*callback)(std::string lastDeeplink));
    static void verifyAppStorePurchase(ADJAppStorePurchase2dx purchase, void (*callback)(AdjustPurchaseVerificationResult2dx verificationResult));
    static void verifyAndTrackAppStorePurchase(ADJEvent2dx adjustEvent, void (*callback)(AdjustPurchaseVerificationResult2dx verificationResult));
    static void getIdfv(void(*callback)(std::string idfv));
    static void processAndResolveDeeplink(ADJDeeplink2dx adjustDeeplink, void (*callback)(std::string resolvedLink));
    static void endFirstSessionDelay();
    static void enableCoppaComplianceInDelay();
    static void disableCoppaComplianceInDelay();
    static void setExternalDeviceIdInDelay(std::string);
    // testing only
    static void trackSubsessionStart();
    static void trackSubsessionEnd();
    static void setTestOptions(std::map<std::string, std::string> stringTestOptionsMap,
                               std::map<std::string, int> intTestOptionsMap);
    static void teardown();
};

#endif /* _ADJUST_ADJADJUST2DX_H_ */
