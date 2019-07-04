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
    
    if (isAttributionCallbackImplemented
        || isEventSuccessCallbackImplemented
        || isEventFailureCallbackImplemented
        || isSessionSuccessCallbackImplemented
        || isSessionFailureCallbackImplemented
        || isDeferredDeeplinkCallbackImplemented) {
        ((ADJConfig *)adjustConfig.getConfig()).delegate = [ADJDelegate2dx getInstanceWithSwizzleOfAttributionCallback:isAttributionCallbackImplemented
                                                                                         swizzleOfEventSuccessCallback:isEventSuccessCallbackImplemented
                                                                                         swizzleOfEventFailureCallback:isEventFailureCallbackImplemented
                                                                                       swizzleOfSessionSuccessCallback:isSessionSuccessCallbackImplemented
                                                                                       swizzleOfSessionFailureCallback:isSessionFailureCallbackImplemented
                                                                                     swizzleOfDeferredDeeplinkCallback:isDeferredDeeplinkCallbackImplemented
                                                                                              andAttributionCallbackId:adjustConfig.getAttributionCallback()
                                                                                                eventSuccessCallbackId:adjustConfig.getEventSuccessCallback()
                                                                                                eventFailureCallbackId:adjustConfig.getEventFailureCallback()
                                                                                              sessionSuccessCallbackId:adjustConfig.getSessionSuccessCallback()
                                                                                              sessionFailureCallbackId:adjustConfig.getSessionFailureCallback()
                                                                                            deferredDeeplinkCallbackId:adjustConfig.getDeferredDeeplinkCallback()];
    }

    [Adjust appDidLaunch:(ADJConfig *)adjustConfig.getConfig()];
}

void ADJAdjust2dx::trackEvent(ADJEvent2dx adjustEvent) {
    [Adjust trackEvent:(ADJEvent *)adjustEvent.getEvent()];
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

bool ADJAdjust2dx::isEnabled() {
    return [Adjust isEnabled];
}

std::string ADJAdjust2dx::getIdfa() {
    if (nil == [Adjust idfa]) {
        return "";
    }

    std::string idfa = std::string([[Adjust idfa] UTF8String]);
    return idfa;
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
    }

    AdjustAttribution2dx attribution2dx = AdjustAttribution2dx(trackerToken, trackerName, network, campaign, adgroup, creative, clickLabel, adid);
    return attribution2dx;
}

void ADJAdjust2dx::setTestOptions(std::map<std::string, std::string> testOptionsMap) {
    AdjustTestOptions *testOptions = [[AdjustTestOptions alloc] init];
    testOptions.baseUrl = [NSString stringWithUTF8String:testOptionsMap["baseUrl"].c_str()];
    testOptions.gdprUrl = [NSString stringWithUTF8String:testOptionsMap["gdprUrl"].c_str()];

    if (testOptionsMap.find("basePath") != testOptionsMap.end()) {
        testOptions.basePath = [NSString stringWithUTF8String:testOptionsMap["basePath"].c_str()];
    }
    if (testOptionsMap.find("gdprPath") != testOptionsMap.end()) {
        testOptions.gdprPath = [NSString stringWithUTF8String:testOptionsMap["gdprPath"].c_str()];
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
    testOptions.iAdFrameworkEnabled = NO;
    if (testOptionsMap.find("iAdFrameworkEnabled") != testOptionsMap.end()) {
        NSString *iAdFrameworkEnabled = [NSString stringWithUTF8String:testOptionsMap["iAdFrameworkEnabled"].c_str()];
        if ([iAdFrameworkEnabled isEqualToString:@"true"]) {
            testOptions.iAdFrameworkEnabled = YES;
        }
    }

    [Adjust setTestOptions:testOptions];
}

void ADJAdjust2dx::teardown() {
    [ADJDelegate2dx teardown];
}
