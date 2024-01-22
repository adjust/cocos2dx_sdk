//
//  ADJAdjust2dx.mm
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 17th June 2015.
//  Copyright © 2015-2019 Adjust GmbH. All rights reserved.
//

#include "ADJAdjust2dx.h"
#include "ADJDelegate2dx.h"
#include <AdjustSdk/Adjust.h>

const std::string ADJEnvironmentSandbox2dx = std::string([ADJEnvironmentSandbox UTF8String]);
const std::string ADJEnvironmentProduction2dx = std::string([ADJEnvironmentProduction UTF8String]);

void ADJAdjust2dx::appDidLaunch(ADJConfig2dx adjustConfig) {
    BOOL isAttributionCallbackImplemented = NULL != adjustConfig.getAttributionCallback() ? YES : NO;
    BOOL isEventSuccessCallbackImplemented = NULL != adjustConfig.getEventSuccessCallback() ? YES : NO;
    BOOL isEventFailureCallbackImplemented = NULL != adjustConfig.getEventFailureCallback() ? YES : NO;
    BOOL isSessionSuccessCallbackImplemented = NULL != adjustConfig.getSessionSuccessCallback() ? YES : NO;
    BOOL isSessionFailureCallbackImplemented = NULL != adjustConfig.getSessionFailureCallback() ? YES : NO;
    BOOL isDeferredDeeplinkCallbackImplemented = NULL != adjustConfig.getDeferredDeeplinkCallback() ? YES : NO;
    BOOL isConversionValueUpdatedListenerImplemented = NULL != adjustConfig.getConversionValueUpdatedCallback() ? YES : NO;
    BOOL isPostbackConversionValueUpdatedCallbackImplemented = NULL != adjustConfig.getPostbackConversionValueUpdatedCallback() ? YES : NO;

    if (isAttributionCallbackImplemented
        || isEventSuccessCallbackImplemented
        || isEventFailureCallbackImplemented
        || isSessionSuccessCallbackImplemented
        || isSessionFailureCallbackImplemented
        || isDeferredDeeplinkCallbackImplemented
        || isConversionValueUpdatedListenerImplemented
        || isPostbackConversionValueUpdatedCallbackImplemented) {
        ((ADJConfig *)adjustConfig.getConfig()).delegate = 
        [ADJDelegate2dx getInstanceWithSwizzleOfAttributionCallback:isAttributionCallbackImplemented
                                      swizzleOfEventSuccessCallback:isEventSuccessCallbackImplemented
                                      swizzleOfEventFailureCallback:isEventFailureCallbackImplemented
                                    swizzleOfSessionSuccessCallback:isSessionSuccessCallbackImplemented
                                    swizzleOfSessionFailureCallback:isSessionFailureCallbackImplemented
                                  swizzleOfDeferredDeeplinkCallback:isDeferredDeeplinkCallbackImplemented
                            swizzleOfConversionValueUpdatedCallback:isConversionValueUpdatedListenerImplemented
                    swizzleOfPostbackConversionValueUpdatedCallback:isPostbackConversionValueUpdatedCallbackImplemented
                                           andAttributionCallbackId:adjustConfig.getAttributionCallback()
                                             eventSuccessCallbackId:adjustConfig.getEventSuccessCallback()
                                             eventFailureCallbackId:adjustConfig.getEventFailureCallback()
                                           sessionSuccessCallbackId:adjustConfig.getSessionSuccessCallback()
                                           sessionFailureCallbackId:adjustConfig.getSessionFailureCallback()
                                         deferredDeeplinkCallbackId:adjustConfig.getDeferredDeeplinkCallback()
                                   conversionValueUpdatedCallbackId:adjustConfig.getConversionValueUpdatedCallback()
                           postbackConversionValueUpdatedCallbackId:adjustConfig.getPostbackConversionValueUpdatedCallback()];
    }

    [Adjust appDidLaunch:(ADJConfig *)adjustConfig.getConfig()];
}

void ADJAdjust2dx::trackEvent(ADJEvent2dx adjustEvent) {
    [Adjust trackEvent:(ADJEvent *)adjustEvent.getEvent()];
}

void ADJAdjust2dx::trackAppStoreSubscription(ADJAppStoreSubscription2dx subscription) {
    [Adjust trackSubscription:(ADJSubscription *)subscription.getSubscription()];
}

void ADJAdjust2dx::verifyAppStorePurchase(ADJAppStorePurchase2dx purchase, void (*verificationCallback)(std::string verificationStatus, int code, std::string message)) {
    [Adjust verifyPurchase:(ADJPurchase *)purchase.getPurchase() completionHandler:^(ADJPurchaseVerificationResult * _Nonnull verificationResult) {
        if (verificationCallback != NULL) {
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

void ADJAdjust2dx::setEnabled(bool isEnabled) {
    [Adjust setEnabled:isEnabled];
}

void ADJAdjust2dx::appWillOpenUrl(std::string url) {
    NSURL *pUrl = [NSURL URLWithString:[NSString stringWithUTF8String:url.c_str()]];
    [Adjust appWillOpenUrl:pUrl];
}

void ADJAdjust2dx::setDeviceToken(std::string deviceToken) {
    NSString *pPushToken = [NSString stringWithUTF8String:deviceToken.c_str()];
    [Adjust setPushToken:pPushToken];
}

void ADJAdjust2dx::setOfflineMode(bool isOffline) {
    [Adjust setOfflineMode:isOffline];
}

void ADJAdjust2dx::sendFirstPackages() {
    [Adjust sendFirstPackages];
}

void ADJAdjust2dx::gdprForgetMe() {
    [Adjust gdprForgetMe];
}

void ADJAdjust2dx::disableThirdPartySharing() {
    [Adjust disableThirdPartySharing];
}

void ADJAdjust2dx::addSessionCallbackParameter(std::string key, std::string value) {
    [Adjust addSessionCallbackParameter:[NSString stringWithUTF8String:key.c_str()] value:[NSString stringWithUTF8String:value.c_str()]];
}

void ADJAdjust2dx::addSessionPartnerParameter(std::string key, std::string value) {
    [Adjust addSessionPartnerParameter:[NSString stringWithUTF8String:key.c_str()] value:[NSString stringWithUTF8String:value.c_str()]];
}

void ADJAdjust2dx::removeSessionCallbackParameter(std::string key) {
    [Adjust removeSessionCallbackParameter:[NSString stringWithUTF8String:key.c_str()]];
}

void ADJAdjust2dx::removeSessionPartnerParameter(std::string key) {
    [Adjust removeSessionPartnerParameter:[NSString stringWithUTF8String:key.c_str()]];
}

void ADJAdjust2dx::resetSessionCallbackParameters() {
    [Adjust resetSessionCallbackParameters];
}

void ADJAdjust2dx::resetSessionPartnerParameters() {
    [Adjust resetSessionPartnerParameters];
}

void ADJAdjust2dx::trackAdRevenue(std::string source, std::string payload) {
    NSData *dataPayload = [[NSString stringWithUTF8String:payload.c_str()] dataUsingEncoding:NSUTF8StringEncoding];
    [Adjust trackAdRevenue:[NSString stringWithUTF8String:source.c_str()] payload:dataPayload];
}

void ADJAdjust2dx::trackAdRevenueNew(ADJAdRevenue2dx adRevenue) {
    [Adjust trackAdRevenue:(ADJAdRevenue *)adRevenue.getAdRevenue()];
}

bool ADJAdjust2dx::isEnabled() {
    return [Adjust isEnabled];
}

std::string ADJAdjust2dx::getIdfa() {
    NSString *idfa = [Adjust idfa];
    if (nil == idfa) {
        return "";
    }

    std::string strIdfa = std::string([idfa UTF8String]);
    return strIdfa;
}

std::string ADJAdjust2dx::getAdid() {
    if (nil == [Adjust adid]) {
        return "";
    }

    std::string adid = std::string([[Adjust adid] UTF8String]);
    return adid;
}

std::string ADJAdjust2dx::getSdkVersion() {
    if (nil == [Adjust sdkVersion]) {
        return "";
    }

    std::string sdkVersion = std::string([[Adjust sdkVersion] UTF8String]);
    return sdkVersion;
}

AdjustAttribution2dx ADJAdjust2dx::getAttribution() {
    ADJAttribution *attribution = [Adjust attribution];
    std::string trackerToken;
    std::string trackerName;
    std::string network;
    std::string campaign;
    std::string adgroup;
    std::string creative;
    std::string clickLabel;
    std::string adid;
    std::string costType;
    double costAmount;
    std::string costCurrency;
    std::string fbInstallReferrer = NULL;

    if (nil != attribution) {
        if (attribution.trackerToken != NULL) {
            trackerToken = std::string([attribution.trackerToken UTF8String]);
        }
        if (attribution.trackerName != NULL) {
            trackerName = std::string([attribution.trackerName UTF8String]);
        }
        if (attribution.network != NULL) {
            network = std::string([attribution.network UTF8String]);
        }
        if (attribution.campaign != NULL) {
            campaign = std::string([attribution.campaign UTF8String]);
        }
        if (attribution.adgroup != NULL) {
            adgroup = std::string([attribution.adgroup UTF8String]);
        }
        if (attribution.creative != NULL) {
            creative = std::string([attribution.creative UTF8String]);
        }
        if (attribution.clickLabel != NULL) {
            clickLabel = std::string([attribution.clickLabel UTF8String]);
        }
        if (attribution.adid != NULL) {
            adid = std::string([attribution.adid UTF8String]);
        }
        if (attribution.costType != NULL) {
            costType = std::string([attribution.costType UTF8String]);
        }
        if (attribution.costType != NULL) {
            costAmount = [attribution.costAmount doubleValue];
        }
        if (attribution.costCurrency != NULL) {
            costCurrency = std::string([attribution.costCurrency UTF8String]);
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
        adid,
        costType,
        costAmount,
        costCurrency,
        fbInstallReferrer);
    return attribution2dx;
}

void ADJAdjust2dx::requestTrackingAuthorizationWithCompletionHandler(void (*trackingStatusCallback)(int status)) {
    [Adjust requestTrackingAuthorizationWithCompletionHandler:^(NSUInteger status) {
        if (trackingStatusCallback != NULL) {
            trackingStatusCallback((int)status);
        }
    }];
}

int ADJAdjust2dx::getAppTrackingAuthorizationStatus() {
    return [Adjust appTrackingAuthorizationStatus];
}

void ADJAdjust2dx::updateConversionValue(int conversionValue) {
    [Adjust updateConversionValue:conversionValue];
}

void ADJAdjust2dx::updatePostbackConversionValue(int conversionValue, void (*errorCallback)(std::string error)) {
    [Adjust updatePostbackConversionValue:conversionValue completionHandler:^(NSError * _Nullable error) {
        if (errorCallback != NULL) {
            errorCallback(std::string([error.localizedDescription UTF8String]));
        }
    }];
}

void ADJAdjust2dx::updatePostbackConversionValue(int conversionValue, std::string coarseValue, void (*errorCallback)(std::string error)) {
    [Adjust updatePostbackConversionValue:conversionValue
                              coarseValue:[NSString stringWithUTF8String:coarseValue.c_str()]
                        completionHandler:^(NSError * _Nullable error) {
        if (errorCallback != NULL) {
            errorCallback(std::string([error.localizedDescription UTF8String]));
        }
    }];
}

void ADJAdjust2dx::updatePostbackConversionValue(int conversionValue, std::string coarseValue, bool lockWindow, void (*errorCallback)(std::string error)) {
    [Adjust updatePostbackConversionValue:conversionValue
                              coarseValue:[NSString stringWithUTF8String:coarseValue.c_str()]
                               lockWindow:lockWindow
                        completionHandler:^(NSError * _Nullable error) {
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

void ADJAdjust2dx::checkForNewAttStatus() {
    [Adjust checkForNewAttStatus];
}

std::string ADJAdjust2dx::getLastDeeplink() {
    NSURL *lastDeeplink = [Adjust lastDeeplink];
    if (nil == lastDeeplink) {
        return "";
    }
    NSString *strLastDeeplink = [lastDeeplink absoluteString];
    if (nil == strLastDeeplink) {
        return "";
    }

    std::string stdStrLastDeeplink = std::string([strLastDeeplink UTF8String]);
    return stdStrLastDeeplink;
}

std::string ADJAdjust2dx::getIdfv() {
    NSString *idfv = [Adjust idfv];
    if (nil == idfv) {
        return "";
    }

    std::string strIdfv = std::string([idfv UTF8String]);
    return strIdfv;
}

void ADJAdjust2dx::processDeeplink(std::string url, void (*resolvedLinkCallback)(std::string resolvedLink)) {
    NSURL *pUrl = [NSURL URLWithString:[NSString stringWithUTF8String:url.c_str()]];
    [Adjust processDeeplink:pUrl completionHandler:^(NSString * _Nonnull resolvedLink) {
        if (resolvedLinkCallback != NULL) {
            if (resolvedLink != nil) {
                resolvedLinkCallback(std::string([resolvedLink UTF8String]));
            } else {
                resolvedLinkCallback("");
            }
        }
    }];
}

void ADJAdjust2dx::setTestOptions(std::map<std::string, std::string> testOptionsMap) {
    AdjustTestOptions *testOptions = [[AdjustTestOptions alloc] init];
    testOptions.baseUrl = [NSString stringWithUTF8String:testOptionsMap["baseUrl"].c_str()];
    testOptions.gdprUrl = [NSString stringWithUTF8String:testOptionsMap["gdprUrl"].c_str()];
    testOptions.subscriptionUrl = [NSString stringWithUTF8String:testOptionsMap["subscriptionUrl"].c_str()];
    testOptions.purchaseVerificationUrl = [NSString stringWithUTF8String:testOptionsMap["purchaseVerificationUrl"].c_str()];

    if (testOptionsMap.find("extraPath") != testOptionsMap.end()) {
        testOptions.extraPath = [NSString stringWithUTF8String:testOptionsMap["extraPath"].c_str()];
    }
    if (testOptionsMap.find("timerIntervalInMilliseconds") != testOptionsMap.end()) {
        NSString *timerIntervalMilliseconds = [NSString stringWithUTF8String:testOptionsMap["timerIntervalInMilliseconds"].c_str()];
        testOptions.timerIntervalInMilliseconds = [NSNumber numberWithInt:[timerIntervalMilliseconds intValue]];
    }
    if (testOptionsMap.find("timerStartInMilliseconds") != testOptionsMap.end()) {
        NSString *timerStartMilliseconds = [NSString stringWithUTF8String:testOptionsMap["timerStartInMilliseconds"].c_str()];
        testOptions.timerStartInMilliseconds = [NSNumber numberWithInt:[timerStartMilliseconds intValue]];
    }
    if (testOptionsMap.find("sessionIntervalInMilliseconds") != testOptionsMap.end()) {
        NSString *sessionIntervalMilliseconds = [NSString stringWithUTF8String:testOptionsMap["sessionIntervalInMilliseconds"].c_str()];
        testOptions.sessionIntervalInMilliseconds = [NSNumber numberWithInt:[sessionIntervalMilliseconds intValue]];
    }
    if (testOptionsMap.find("subsessionIntervalInMilliseconds") != testOptionsMap.end()) {
        NSString *subsessionIntervalMilliseconds = [NSString stringWithUTF8String:testOptionsMap["subsessionIntervalInMilliseconds"].c_str()];
        testOptions.subsessionIntervalInMilliseconds = [NSNumber numberWithInt:[subsessionIntervalMilliseconds intValue]];
    }
    if (testOptionsMap.find("teardown") != testOptionsMap.end()) {
        NSString *teardown = [NSString stringWithUTF8String:testOptionsMap["teardown"].c_str()];
        testOptions.teardown = NO;
        if ([teardown isEqualToString:@"true"]) {
            testOptions.teardown = YES;
        }
    }
    if (testOptionsMap.find("deleteState") != testOptionsMap.end()) {
        NSString *deleteState = [NSString stringWithUTF8String:testOptionsMap["deleteState"].c_str()];
        testOptions.deleteState = NO;
        if ([deleteState isEqualToString:@"true"]) {
            testOptions.deleteState = YES;
        }
    }
    if (testOptionsMap.find("noBackoffWait") != testOptionsMap.end()) {
        NSString *noBackoffWait = [NSString stringWithUTF8String:testOptionsMap["noBackoffWait"].c_str()];
        testOptions.noBackoffWait = NO;
        if ([noBackoffWait isEqualToString:@"true"]) {
            testOptions.noBackoffWait = YES;
        }
    }
    testOptions.adServicesFrameworkEnabled = NO;
    if (testOptionsMap.find("adServicesFrameworkEnabled") != testOptionsMap.end()) {
        NSString *adServicesFrameworkEnabled = [NSString stringWithUTF8String:testOptionsMap["adServicesFrameworkEnabled"].c_str()];
        if ([adServicesFrameworkEnabled isEqualToString:@"true"]) {
            testOptions.adServicesFrameworkEnabled = YES;
        }
    }

    [Adjust setTestOptions:testOptions];
}

void ADJAdjust2dx::teardown() {
    [ADJDelegate2dx teardown];
}
