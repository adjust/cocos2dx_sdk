//
//  ADJAdjust2dx.mm
//  AdjustSDK
//
//  Created by Uglješa Erceg on 17/06/15.
//
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
    
    if (isAttributionCallbackImplemented || isEventSuccessCallbackImplemented ||
        isEventFailureCallbackImplemented || isSessionSuccessCallbackImplemented ||
        isSessionFailureCallbackImplemented || isDeferredDeeplinkCallbackImplemented) {
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
    NSData *pDeviceToken = [[NSString stringWithUTF8String:deviceToken.c_str()]
                            dataUsingEncoding:NSUTF8StringEncoding];
    [Adjust setDeviceToken:pDeviceToken];
}

void ADJAdjust2dx::setOfflineMode(bool isOffline) {
    [Adjust setOfflineMode:isOffline];
}

void ADJAdjust2dx::sendFirstPackages() {
    [Adjust sendFirstPackages];
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
