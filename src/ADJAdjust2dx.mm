//
//  ADJAdjust2dx.mm
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 17th June 2015.
//  Copyright © 2015-2019 Adjust GmbH. All rights reserved.
//

#include "ADJAdjust2dx.h"
#include "ADJDelegate2dx.h"
#include <AdjustSdk/AdjustSdk.h>

const std::string ADJEnvironmentSandbox2dx = std::string([ADJEnvironmentSandbox UTF8String]);
const std::string ADJEnvironmentProduction2dx = std::string([ADJEnvironmentProduction UTF8String]);

void ADJAdjust2dx::initSdk(ADJConfig2dx adjustConfig) {
    BOOL isAttributionCallbackImplemented = NULL != adjustConfig.getAttributionCallback() ? YES : NO;
    BOOL isEventSuccessCallbackImplemented = NULL != adjustConfig.getEventSuccessCallback() ? YES : NO;
    BOOL isEventFailureCallbackImplemented = NULL != adjustConfig.getEventFailureCallback() ? YES : NO;
    BOOL isSessionSuccessCallbackImplemented = NULL != adjustConfig.getSessionSuccessCallback() ? YES : NO;
    BOOL isSessionFailureCallbackImplemented = NULL != adjustConfig.getSessionFailureCallback() ? YES : NO;
    BOOL isDeferredDeeplinkCallbackImplemented = NULL != adjustConfig.getDeferredDeeplinkCallback() ? YES : NO;
    BOOL isSkanUpdatedWithConversionDataCallbackImplemented = NULL != adjustConfig.getSkanUpdatedWithConversionDataCallback() ? YES : NO;

    if (isAttributionCallbackImplemented
        || isEventSuccessCallbackImplemented
        || isEventFailureCallbackImplemented
        || isSessionSuccessCallbackImplemented
        || isSessionFailureCallbackImplemented
        || isDeferredDeeplinkCallbackImplemented
        || isSkanUpdatedWithConversionDataCallbackImplemented)
    {
        ((ADJConfig *)adjustConfig.getConfig()).delegate =
        [ADJDelegate2dx getInstanceWithSwizzleOfAttributionCallback:isAttributionCallbackImplemented
                                      swizzleOfEventSuccessCallback:isEventSuccessCallbackImplemented
                                      swizzleOfEventFailureCallback:isEventFailureCallbackImplemented
                                    swizzleOfSessionSuccessCallback:isSessionSuccessCallbackImplemented
                                    swizzleOfSessionFailureCallback:isSessionFailureCallbackImplemented
                                  swizzleOfDeferredDeeplinkCallback:isDeferredDeeplinkCallbackImplemented
                       swizzleSkanUpdatedWithConversionDataCallback:isSkanUpdatedWithConversionDataCallbackImplemented
                                           andAttributionCallbackId:adjustConfig.getAttributionCallback()
                                             eventSuccessCallbackId:adjustConfig.getEventSuccessCallback()
                                             eventFailureCallbackId:adjustConfig.getEventFailureCallback()
                                           sessionSuccessCallbackId:adjustConfig.getSessionSuccessCallback()
                                           sessionFailureCallbackId:adjustConfig.getSessionFailureCallback()
                                         deferredDeeplinkCallbackId:adjustConfig.getDeferredDeeplinkCallback()
                            skanUpdatedWithConversionDataCallbackId:adjustConfig.getSkanUpdatedWithConversionDataCallback()];
    }

    [Adjust initSdk:(ADJConfig *)adjustConfig.getConfig()];
}

void ADJAdjust2dx::trackEvent(ADJEvent2dx adjustEvent) {
    [Adjust trackEvent:(ADJEvent *)adjustEvent.getEvent()];
}

void ADJAdjust2dx::trackAppStoreSubscription(ADJAppStoreSubscription2dx subscription) {
    [Adjust trackAppStoreSubscription:(ADJAppStoreSubscription *)subscription.getSubscription()];
}

void ADJAdjust2dx::verifyAppStorePurchase(ADJAppStorePurchase2dx purchase, void (*verificationCallback)(std::string verificationStatus, int code, std::string message)) {
    [Adjust verifyAppStorePurchase:(ADJAppStorePurchase *)purchase.getPurchase()
             withCompletionHandler:^(ADJPurchaseVerificationResult * _Nonnull verificationResult) {
        if (verificationCallback != NULL) {
            verificationCallback(std::string([verificationResult.verificationStatus UTF8String]),
                                 verificationResult.code,
                                 std::string([verificationResult.message UTF8String]));
        }
    }];
}

void ADJAdjust2dx::verifyAndTrackAppStorePurchase(ADJEvent2dx adjustEvent, void (*verificationCallback)(std::string verificationStatus, int code, std::string message)) {
    [Adjust verifyAndTrackAppStorePurchase:(ADJEvent *)adjustEvent.getEvent()
                     withCompletionHandler:^(ADJPurchaseVerificationResult * _Nonnull verificationResult) {
        if (verificationResult != NULL) {
            verificationCallback(std::string([verificationResult.verificationStatus UTF8String]),
                                 verificationResult.code,
                                 std::string([verificationResult.message UTF8String]));
        }
    }];
}

void ADJAdjust2dx::trackSubsessionStart() {
    [Adjust trackSubsessionStart];
}

void ADJAdjust2dx::trackSubsessionEnd() {
    [Adjust trackSubsessionEnd];
}

void ADJAdjust2dx::enable() {
    [Adjust enable];
}

void ADJAdjust2dx::disable() {
    [Adjust disable];
}

void ADJAdjust2dx::processDeeplink(ADJDeeplink2dx adjustDeeplink) {
    [Adjust processDeeplink:(ADJDeeplink *)adjustDeeplink.getDeeplink()];
}

void ADJAdjust2dx::setPushTokenAsString(std::string pushToken) {
    NSString *pPushToken = [NSString stringWithUTF8String:pushToken.c_str()];
    [Adjust setPushTokenAsString:pPushToken];
}

void ADJAdjust2dx::switchToOfflineMode() {
    [Adjust switchToOfflineMode];
}

void ADJAdjust2dx::switchBackToOnlineMode() {
    [Adjust switchBackToOnlineMode];
}

void ADJAdjust2dx::gdprForgetMe() {
    [Adjust gdprForgetMe];
}

void ADJAdjust2dx::addGlobalCallbackParameter(std::string key, std::string value) {
    [Adjust addGlobalCallbackParameter:[NSString stringWithUTF8String:key.c_str()]
                                forKey:[NSString stringWithUTF8String:value.c_str()]];
}

void ADJAdjust2dx::addGlobalPartnerParameter(std::string key, std::string value) {
    [Adjust addGlobalPartnerParameter:[NSString stringWithUTF8String:key.c_str()]
                               forKey:[NSString stringWithUTF8String:value.c_str()]];
}

void ADJAdjust2dx::removeGlobalCallbackParameter(std::string key) {
    [Adjust removeGlobalCallbackParameterForKey:[NSString stringWithUTF8String:key.c_str()]];
}

void ADJAdjust2dx::removeGlobalPartnerParameter(std::string key) {
    [Adjust removeGlobalPartnerParameterForKey:[NSString stringWithUTF8String:key.c_str()]];
}

void ADJAdjust2dx::removeGlobalCallbackParameters() {
    [Adjust removeGlobalCallbackParameters];
}

void ADJAdjust2dx::removeGlobalPartnerParameters() {
    [Adjust removeGlobalPartnerParameters];
}

void ADJAdjust2dx::trackAdRevenue(ADJAdRevenue2dx adRevenue) {
    [Adjust trackAdRevenue:(ADJAdRevenue *)adRevenue.getAdRevenue()];
}

void ADJAdjust2dx::isEnabledCallback(void(*callbackMethod)(bool isEnabled)) {
    [Adjust isEnabledWithCompletionHandler:^(BOOL isEnabled) {
        callbackMethod(isEnabled ? true : false);
    }];
}

void ADJAdjust2dx::idfaCallback(void(*callbackMethod)(std::string idfa)) {
    [Adjust idfaWithCompletionHandler:^(NSString * _Nullable idfa) {
        if (idfa == nil) {
            callbackMethod("");
        } else {
            callbackMethod(std::string([idfa UTF8String]));
        }
    }];
}

void ADJAdjust2dx::adidCallback(void(*callbackMethod)(std::string adid)) {
    [Adjust adidWithCompletionHandler:^(NSString * _Nullable adid) {
        if (adid == nil) {
            callbackMethod("");
        } else {
            callbackMethod(std::string([adid UTF8String]));
        }
    }];
}

void ADJAdjust2dx::sdkVersionCallback(void(*callbackMethod)(std::string sdkVersion)) {
    [Adjust sdkVersionWithCompletionHandler:^(NSString * _Nullable sdkVersion) {
        if (sdkVersion == nil) {
            callbackMethod("");
        } else {
            callbackMethod(std::string([sdkVersion UTF8String]));
        }
    }];
}

void ADJAdjust2dx::attributionCallback(void(*callbackMethod)(AdjustAttribution2dx attribution)) {
    [Adjust attributionWithCompletionHandler:^(ADJAttribution * _Nullable attribution) {
        std::string trackerToken;
        std::string trackerName;
        std::string network;
        std::string campaign;
        std::string adgroup;
        std::string creative;
        std::string clickLabel;
        std::string adid;
        std::string costType;
        double costAmount = -1;
        std::string costCurrency;
        std::string fbInstallReferrer;

        if (nil != attribution) {
            if (attribution.trackerToken != nil) {
                trackerToken = std::string([attribution.trackerToken UTF8String]);
            }
            if (attribution.trackerName != nil) {
                trackerName = std::string([attribution.trackerName UTF8String]);
            }
            if (attribution.network != nil) {
                network = std::string([attribution.network UTF8String]);
            }
            if (attribution.campaign != nil) {
                campaign = std::string([attribution.campaign UTF8String]);
            }
            if (attribution.adgroup != nil) {
                adgroup = std::string([attribution.adgroup UTF8String]);
            }
            if (attribution.creative != nil) {
                creative = std::string([attribution.creative UTF8String]);
            }
            if (attribution.clickLabel != nil) {
                clickLabel = std::string([attribution.clickLabel UTF8String]);
            }
            if (attribution.costType != nil) {
                costType = std::string([attribution.costType UTF8String]);
            }
            if (attribution.costType != nil) {
                costAmount = [attribution.costAmount doubleValue];
            }
            if (attribution.costCurrency != nil) {
                costCurrency = std::string([attribution.costCurrency UTF8String]);
            }
        }

        AdjustAttribution2dx attribution2dx = AdjustAttribution2dx(trackerToken,
                                                                   trackerName,
                                                                   network,
                                                                   campaign,
                                                                   adgroup,
                                                                   creative,
                                                                   clickLabel,
                                                                   costType,
                                                                   costAmount,
                                                                   costCurrency,
                                                                   fbInstallReferrer);

        callbackMethod(attribution2dx);
    }];
}

void ADJAdjust2dx::requestAppTrackingAuthorizationWithCompletionHandler(void (*trackingStatusCallback)(int status)) {
    [Adjust requestAppTrackingAuthorizationWithCompletionHandler:^(NSUInteger status) {
        if (trackingStatusCallback != NULL) {
            trackingStatusCallback((int)status);
        }
    }];
}

int ADJAdjust2dx::getAppTrackingAuthorizationStatus() {
    return [Adjust appTrackingAuthorizationStatus];
}

void ADJAdjust2dx::updateSkanConversionValue(int conversionValue,
                                             std::string coarseValue,
                                             bool* optionalLockWindow,
                                             void (*errorCallback)(std::string error))
{
    [Adjust updateSkanConversionValue:conversionValue
                          coarseValue:[NSString stringWithUTF8String:coarseValue.c_str()]
                           lockWindow:optionalLockWindow ? @(*optionalLockWindow) : nil
                withCompletionHandler:^(NSError * _Nullable error) {
        if (errorCallback != NULL) {
            errorCallback(std::string([error.localizedDescription UTF8String]));
        }
    }];
}

void ADJAdjust2dx::trackThirdPartySharing(ADJThirdPartySharing2dx thirdPartySharing) {
    [Adjust trackThirdPartySharing:(ADJThirdPartySharing *)thirdPartySharing.getThirdPartySharing()];
}

void ADJAdjust2dx::trackMeasurementConsent(bool measurementConsent) {
    [Adjust trackMeasurementConsent:measurementConsent];
}

void ADJAdjust2dx::lastDeeplinkCallback(void(*callbackMethod)(std::string lastDeeplink)) {
    [Adjust lastDeeplinkWithCompletionHandler:^(NSURL * _Nullable lastDeeplink) {
        if (lastDeeplink == nil) {
            callbackMethod("");
            return;
        }

        NSString *strLastDeeplink = [lastDeeplink absoluteString];
        if (strLastDeeplink == nil) {
            callbackMethod("");
            return;
        }

        callbackMethod(std::string([strLastDeeplink UTF8String]));
    }];
}

void ADJAdjust2dx::idfvCallback(void(*callbackMethod)(std::string idfv)) {
    [Adjust idfvWithCompletionHandler:^(NSString * _Nullable idfv) {
        if (idfv == nil) {
            callbackMethod("");
        } else {
            callbackMethod(std::string([idfv UTF8String]));
        }
    }];
}

void ADJAdjust2dx::processAndResolveDeeplink(ADJDeeplink2dx adjustDeeplink, void (*resolvedLinkCallback)(std::string resolvedLink)) {
    [Adjust processAndResolveDeeplink:(ADJDeeplink *)adjustDeeplink.getDeeplink()
                withCompletionHandler:^(NSString * _Nullable resolvedLink) {
        if (resolvedLinkCallback != NULL) {
            if (resolvedLink != nil) {
                resolvedLinkCallback(std::string([resolvedLink UTF8String]));
            } else {
                resolvedLinkCallback("");
            }
        }
    }];
}

void ADJAdjust2dx::setTestOptions(std::map<std::string, std::string> stringTestOptionsMap,
                                  std::map<std::string, int> intTestOptionsMap)
{
    NSMutableDictionary<NSString *, id> *objcTestOptionsMap =
        [NSMutableDictionary dictionary];

    for (std::map<std::string, std::string>::iterator toStringIterator = stringTestOptionsMap.begin();
         toStringIterator != stringTestOptionsMap.end(); toStringIterator++)
    {
        [objcTestOptionsMap setObject:[NSString stringWithUTF8String:toStringIterator->second.c_str()]
                               forKey:[NSString stringWithUTF8String:toStringIterator->first.c_str()]];
    }

    for (std::map<std::string, int>::iterator toIntIterator = intTestOptionsMap.begin();
         toIntIterator != intTestOptionsMap.end(); toIntIterator++)
    {
        [objcTestOptionsMap setObject:[NSNumber numberWithInt:toIntIterator->second]
                               forKey:[NSString stringWithUTF8String:toIntIterator->first.c_str()]];
    }

    [Adjust setTestOptions:objcTestOptionsMap];
}

void ADJAdjust2dx::teardown() {
    [ADJDelegate2dx teardown];
}
