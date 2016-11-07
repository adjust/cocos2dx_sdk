//
//  ADJAdjust2dx.mm
//  AdjustSDK
//
//  Created by Uglješa Erceg on 17/06/15.
//
//

#include "ADJAdjust2dx.h"
#include <AdjustSdk/Adjust.h>

const std::string ADJEnvironmentSandbox2dx = std::string([ADJEnvironmentSandbox UTF8String]);
const std::string ADJEnvironmentProduction2dx = std::string([ADJEnvironmentProduction UTF8String]);

void ADJAdjust2dx::appDidLaunch(ADJConfig2dx adjustConfig) {
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
    std::string idfa = std::string([[Adjust idfa] UTF8String]);
    return idfa;
}
