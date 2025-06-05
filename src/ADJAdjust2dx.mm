//
//  ADJAdjust2dx.mm
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 17th June 2015.
//  Copyright © 2015-Present Adjust GmbH. All rights reserved.
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
    BOOL isSkanUpdatedCallbackImplemented = NULL != adjustConfig.getSkanUpdatedCallback() ? YES : NO;

    if (isAttributionCallbackImplemented
        || isEventSuccessCallbackImplemented
        || isEventFailureCallbackImplemented
        || isSessionSuccessCallbackImplemented
        || isSessionFailureCallbackImplemented
        || isDeferredDeeplinkCallbackImplemented
        || isSkanUpdatedCallbackImplemented)
    {
        ((ADJConfig *)adjustConfig.getConfig()).delegate =
        [ADJDelegate2dx getInstanceWithSwizzleAttributionCallback:isAttributionCallbackImplemented
                                      swizzleEventSuccessCallback:isEventSuccessCallbackImplemented
                                      swizzleEventFailureCallback:isEventFailureCallbackImplemented
                                    swizzleSessionSuccessCallback:isSessionSuccessCallbackImplemented
                                    swizzleSessionFailureCallback:isSessionFailureCallbackImplemented
                                  swizzleDeferredDeeplinkCallback:isDeferredDeeplinkCallbackImplemented
                                       swizzleSkanUpdatedCallback:isSkanUpdatedCallbackImplemented
                                            attributionCallbackId:adjustConfig.getAttributionCallback()
                                           eventSuccessCallbackId:adjustConfig.getEventSuccessCallback()
                                           eventFailureCallbackId:adjustConfig.getEventFailureCallback()
                                         sessionSuccessCallbackId:adjustConfig.getSessionSuccessCallback()
                                         sessionFailureCallbackId:adjustConfig.getSessionFailureCallback()
                                       deferredDeeplinkCallbackId:adjustConfig.getDeferredDeeplinkCallback()
                                            skanUpdatedCallbackId:adjustConfig.getSkanUpdatedCallback()];
    }

    [Adjust initSdk:(ADJConfig *)adjustConfig.getConfig()];
}

void ADJAdjust2dx::trackEvent(ADJEvent2dx adjustEvent) {
    [Adjust trackEvent:(ADJEvent *)adjustEvent.getEvent()];
}

void ADJAdjust2dx::trackAppStoreSubscription(ADJAppStoreSubscription2dx subscription) {
    [Adjust trackAppStoreSubscription:(ADJAppStoreSubscription *)subscription.getSubscription()];
}

void ADJAdjust2dx::verifyAppStorePurchase(ADJAppStorePurchase2dx purchase, void (*callback)(AdjustPurchaseVerificationResult2dx verificationResult)) {
    [Adjust verifyAppStorePurchase:(ADJAppStorePurchase *)purchase.getPurchase()
             withCompletionHandler:^(ADJPurchaseVerificationResult * _Nonnull verificationResult) {
        if (callback != NULL) {
            if (verificationResult == nil) {
                callback(AdjustPurchaseVerificationResult2dx());
            } else {
                AdjustPurchaseVerificationResult2dx verificationResult2dx = AdjustPurchaseVerificationResult2dx(
                    std::string([verificationResult.verificationStatus UTF8String]),
                    std::string([verificationResult.message UTF8String]),
                    verificationResult.code);
                callback(verificationResult2dx);
            }
        }
    }];
}

void ADJAdjust2dx::verifyAndTrackAppStorePurchase(ADJEvent2dx adjustEvent, void (*callback)(AdjustPurchaseVerificationResult2dx verificationResult)) {
    [Adjust verifyAndTrackAppStorePurchase:(ADJEvent *)adjustEvent.getEvent()
                     withCompletionHandler:^(ADJPurchaseVerificationResult * _Nonnull verificationResult) {
        if (callback != NULL) {
            if (verificationResult == nil) {
                callback(AdjustPurchaseVerificationResult2dx());
            } else {
                AdjustPurchaseVerificationResult2dx verificationResult2dx = AdjustPurchaseVerificationResult2dx(
                    std::string([verificationResult.verificationStatus UTF8String]),
                    std::string([verificationResult.message UTF8String]),
                    verificationResult.code);
                callback(verificationResult2dx);
            }
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

void ADJAdjust2dx::setPushToken(std::string pushToken) {
    NSString *strPushToken = [NSString stringWithUTF8String:pushToken.c_str()];
    [Adjust setPushTokenAsString:strPushToken];
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
    [Adjust addGlobalCallbackParameter:[NSString stringWithUTF8String:value.c_str()]
                                forKey:[NSString stringWithUTF8String:key.c_str()]];
}

void ADJAdjust2dx::addGlobalPartnerParameter(std::string key, std::string value) {
    [Adjust addGlobalPartnerParameter:[NSString stringWithUTF8String:value.c_str()]
                               forKey:[NSString stringWithUTF8String:key.c_str()]];
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

void ADJAdjust2dx::isEnabled(void(*callback)(bool isEnabled)) {
    if (callback == NULL) {
        return;
    }

    [Adjust isEnabledWithCompletionHandler:^(BOOL isEnabled) {
        callback(isEnabled ? true : false);
    }];
}

void ADJAdjust2dx::getIdfa(void(*callback)(std::string idfa)) {
    if (callback == NULL) {
        return;
    }

    [Adjust idfaWithCompletionHandler:^(NSString * _Nullable idfa) {
        callback(idfa != nil ? std::string([idfa UTF8String]) : std::string());
    }];
}

void ADJAdjust2dx::getAdid(void(*callback)(std::string adid)) {
    if (callback == NULL) {
        return;
    }

    [Adjust adidWithCompletionHandler:^(NSString * _Nullable adid) {
        callback(adid != nil ? std::string([adid UTF8String]) : std::string());
    }];
}

void ADJAdjust2dx::getSdkVersion(void(*callback)(std::string sdkVersion), std::string sdkPrefix) {
    if (callback == NULL) {
        return;
    }

    [Adjust sdkVersionWithCompletionHandler:^(NSString * _Nullable sdkVersion) {
        callback(sdkVersion != nil ? sdkPrefix + "@" + std::string([sdkVersion UTF8String]) : std::string());
    }];
}

void ADJAdjust2dx::getAttribution(void(*callback)(AdjustAttribution2dx attribution)) {
    if (callback == NULL) {
        return;
    }

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
        std::string fbInstallReferrer; // unused in ios
        std::string jsonResponse;

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
            if (attribution.jsonResponse != nil) {
                NSData *dataJsonResponse = [NSJSONSerialization dataWithJSONObject:attribution.jsonResponse
                                                                           options:0
                                                                             error:nil];
                NSString *stringJsonResponse = [[NSString alloc] initWithBytes:[dataJsonResponse bytes]
                                                                        length:[dataJsonResponse length]
                                                                      encoding:NSUTF8StringEncoding];
                jsonResponse = std::string([stringJsonResponse UTF8String]);
            }
        }

        AdjustAttribution2dx attribution2dx = AdjustAttribution2dx(
            trackerToken,
            trackerName,
            network,
            campaign,
            adgroup,
            creative,
            clickLabel,
            costType,
            costAmount,
            costCurrency,
            fbInstallReferrer,
            jsonResponse);

        callback(attribution2dx);
    }];
}

void ADJAdjust2dx::requestAppTrackingAuthorization(void (*callback)(int status)) {
    [Adjust requestAppTrackingAuthorizationWithCompletionHandler:^(NSUInteger status) {
        if (callback != NULL) {
            callback((int)status);
        }
    }];
}

int ADJAdjust2dx::getAppTrackingAuthorizationStatus() {
    return [Adjust appTrackingAuthorizationStatus];
}

void ADJAdjust2dx::updateSkanConversionValue(int conversionValue,
                                             std::string coarseValue,
                                             bool lockWindow,
                                             void (*callback)(std::string error)) {
    [Adjust updateSkanConversionValue:conversionValue
                          coarseValue:[NSString stringWithUTF8String:coarseValue.c_str()]
                           lockWindow:@(lockWindow)
                withCompletionHandler:^(NSError * _Nullable error) {
        if (callback != NULL) {
            callback(error != nil ? std::string([error.localizedDescription UTF8String]) : std::string());
        }
    }];
}

void ADJAdjust2dx::trackThirdPartySharing(ADJThirdPartySharing2dx thirdPartySharing) {
    [Adjust trackThirdPartySharing:(ADJThirdPartySharing *)thirdPartySharing.getThirdPartySharing()];
}

void ADJAdjust2dx::trackMeasurementConsent(bool measurementConsent) {
    [Adjust trackMeasurementConsent:measurementConsent];
}

void ADJAdjust2dx::getLastDeeplink(void(*callback)(std::string lastDeeplink)) {
    if (callback == NULL) {
        return;
    }

    [Adjust lastDeeplinkWithCompletionHandler:^(NSURL * _Nullable lastDeeplink) {
        if (lastDeeplink == nil) {
            callback(std::string());
            return;
        }

        NSString *strLastDeeplink = [lastDeeplink absoluteString];
        callback(strLastDeeplink != nil ? std::string([strLastDeeplink UTF8String]) : std::string());
    }];
}

void ADJAdjust2dx::getIdfv(void(*callback)(std::string idfv)) {
    if (callback == NULL) {
        return;
    }

    [Adjust idfvWithCompletionHandler:^(NSString * _Nullable idfv) {
        callback(idfv != nil ? std::string([idfv UTF8String]) : std::string());
    }];
}

void ADJAdjust2dx::processAndResolveDeeplink(ADJDeeplink2dx adjustDeeplink, void (*callback)(std::string resolvedLink)) {
    [Adjust processAndResolveDeeplink:(ADJDeeplink *)adjustDeeplink.getDeeplink()
                withCompletionHandler:^(NSString * _Nullable resolvedLink) {
        if (callback != NULL) {
            callback(resolvedLink != nil ? std::string([resolvedLink UTF8String]) : std::string());
        }
    }];
}

void ADJAdjust2dx::setTestOptions(std::map<std::string, std::string> stringTestOptionsMap,
                                  std::map<std::string, int> intTestOptionsMap) {
    NSMutableDictionary<NSString *, id> *objcTestOptionsMap =
        [NSMutableDictionary dictionary];

    for (std::map<std::string, std::string>::iterator toStringIterator = stringTestOptionsMap.begin();
         toStringIterator != stringTestOptionsMap.end();
         toStringIterator++) {
        [objcTestOptionsMap setObject:[NSString stringWithUTF8String:toStringIterator->second.c_str()]
                               forKey:[NSString stringWithUTF8String:toStringIterator->first.c_str()]];
    }

    for (std::map<std::string, int>::iterator toIntIterator = intTestOptionsMap.begin();
         toIntIterator != intTestOptionsMap.end();
         toIntIterator++) {
        [objcTestOptionsMap setObject:[NSNumber numberWithInt:toIntIterator->second]
                               forKey:[NSString stringWithUTF8String:toIntIterator->first.c_str()]];
    }

    [Adjust setTestOptions:objcTestOptionsMap];
}

void ADJAdjust2dx::teardown() {
    [ADJDelegate2dx teardown];
}
