//
//  ADJConfig2dx.mm
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 17th June 2015.
//  Copyright © 2015-2019 Adjust GmbH. All rights reserved.
//

#include "ADJConfig2dx.h"
#include "ADJDelegate2dx.h"
#include <AdjustSdk/Adjust.h>

void ADJConfig2dx::initConfig(std::string appToken, std::string environment, bool allowSuppressLogLevel, std::string sdkPrefix) {
    config = [[ADJConfig alloc] initWithAppToken:[NSString stringWithUTF8String:appToken.c_str()]
                                     environment:[NSString stringWithUTF8String:environment.c_str()]
                           allowSuppressLogLevel:allowSuppressLogLevel];
    [((ADJConfig *)config) setSdkPrefix:[NSString stringWithUTF8String:sdkPrefix.c_str()]];
}

void ADJConfig2dx::setLogLevel(ADJLogLevel2dx logLevel) {
    ((ADJConfig *)config).logLevel = (ADJLogLevel)logLevel;
}

void ADJConfig2dx::setDelayStart(double delayStart) {
    ((ADJConfig *)config).delayStart = delayStart;
}

void ADJConfig2dx::setSendInBackground(bool isEnabled) {
    ((ADJConfig *)config).sendInBackground = isEnabled;
}

void ADJConfig2dx::setEventBufferingEnabled(bool isEnabled) {
    ((ADJConfig *)config).eventBufferingEnabled = isEnabled;
}

void ADJConfig2dx::setAllowIdfaReading(bool isAllowed) {
    ((ADJConfig *)config).allowIdfaReading = isAllowed;
}

void ADJConfig2dx::setAllowiAdInfoReading(bool isAllowed) {
    // deprecated
    // ((ADJConfig *)config).allowiAdInfoReading = isAllowed;
}

void ADJConfig2dx::setAllowAdServicesInfoReading(bool isAllowed) {
    ((ADJConfig *)config).allowAdServicesInfoReading = isAllowed;
}

void ADJConfig2dx::setNeedsCost(bool needsCost) {
    ((ADJConfig *)config).needsCost = needsCost;
}

void ADJConfig2dx::setUserAgent(std::string userAgent) {
    ((ADJConfig *)config).userAgent = [NSString stringWithUTF8String:userAgent.c_str()];
}

void ADJConfig2dx::setDefaultTracker(std::string defaultTracker) {
    ((ADJConfig *)config).defaultTracker = [NSString stringWithUTF8String:defaultTracker.c_str()];
}

void ADJConfig2dx::setExternalDeviceId(std::string externalDeviceId) {
    ((ADJConfig *)config).externalDeviceId = [NSString stringWithUTF8String:externalDeviceId.c_str()];
}

void ADJConfig2dx::setUrlStrategy(std::string urlStrategy) {
    NSString *strUrlStrategy = [NSString stringWithUTF8String:urlStrategy.c_str()];
    if ([strUrlStrategy isEqualToString:@"china"]) {
        ((ADJConfig *)config).urlStrategy = ADJUrlStrategyChina;
    } else if ([strUrlStrategy isEqualToString:@"india"]) {
        ((ADJConfig *)config).urlStrategy = ADJUrlStrategyIndia;
    } else if ([strUrlStrategy isEqualToString:@"cn"]) {
        ((ADJConfig *)config).urlStrategy = ADJUrlStrategyCn;
    } else if ([strUrlStrategy isEqualToString:@"cn-only"]) {
        ((ADJConfig *)config).urlStrategy = ADJUrlStrategyCnOnly;
    } else if ([strUrlStrategy isEqualToString:@"data-residency-eu"]) {
        ((ADJConfig *)config).urlStrategy = ADJDataResidencyEU;
    } else if ([strUrlStrategy isEqualToString:@"data-residency-tr"]) {
        ((ADJConfig *)config).urlStrategy = ADJDataResidencyTR;
    } else if ([strUrlStrategy isEqualToString:@"data-residency-us"]) {
        ((ADJConfig *)config).urlStrategy = ADJDataResidencyUS;
    }
}

void ADJConfig2dx::deactivateSkAdNetworkHandling() {
    [((ADJConfig *)config) deactivateSKAdNetworkHandling];
}

void ADJConfig2dx::setCoppaCompliantEnabled(bool isEnabled) {
    ((ADJConfig *)config).coppaCompliantEnabled = isEnabled;
}

void ADJConfig2dx::setLinkMeEnabled(bool isEnabled) {
    ((ADJConfig *)config).linkMeEnabled = isEnabled;
}

void ADJConfig2dx::setAttConsentWaitingInterval(int numberOfSeconds) {
    ((ADJConfig *)config).attConsentWaitingInterval = numberOfSeconds;
}

void ADJConfig2dx::setAttributionCallback(void (*callbackMethod)(AdjustAttribution2dx attribution)) {
    attributionCallback = callbackMethod;
}

void ADJConfig2dx::setEventSuccessCallback(void(*callbackMethod)(AdjustEventSuccess2dx eventSuccess)) {
    eventSuccessCallback = callbackMethod;
}

void ADJConfig2dx::setEventFailureCallback(void(*callbackMethod)(AdjustEventFailure2dx eventFailure)) {
    eventFailureCallback = callbackMethod;
}

void ADJConfig2dx::setSessionSuccessCallback(void(*callbackMethod)(AdjustSessionSuccess2dx sessionSuccess)) {
    sessionSuccessCallback = callbackMethod;
}

void ADJConfig2dx::setSessionFailureCallback(void(*callbackMethod)(AdjustSessionFailure2dx sessionFailure)) {
    sessionFailureCallback = callbackMethod;
}

void ADJConfig2dx::setDeferredDeeplinkCallback(bool(*callbackMethod)(std::string deeplink)) {
    deferredDeeplinkCallback = callbackMethod;
}

void ADJConfig2dx::setConversionValueUpdatedCallback(void(*callbackMethod)(int conversionValue)) {
    conversionValueUpdatedCallback = callbackMethod;
}

void ADJConfig2dx::setPostbackConversionValueUpdatedCallback(void(*callbackMethod)(int conversionValue, std::string coarseValue, bool lockWindow)) {
    postbackConversionValueUpdatedCallback = callbackMethod;
}

void* ADJConfig2dx::getConfig() {
    return config;
}

void ADJConfig2dx::setAppSecret(long secretId, long info1, long info2, long info3, long info4) {
    [((ADJConfig *)config) setAppSecret:secretId info1:info1 info2:info2 info3:info3 info4:info4];
}

void ADJConfig2dx::setIsDeviceKnown(bool isDeviceKnown) {
    [((ADJConfig *)config) setIsDeviceKnown:isDeviceKnown];
}

void ADJConfig2dx::setReadDeviceInfoOnceEnabled(bool isEnabled) {
    ((ADJConfig *)config).readDeviceInfoOnceEnabled = isEnabled;
}

void(*ADJConfig2dx::getAttributionCallback())(AdjustAttribution2dx) {
    return attributionCallback;
}

void(*ADJConfig2dx::getEventSuccessCallback())(AdjustEventSuccess2dx) {
    return eventSuccessCallback;
}

void(*ADJConfig2dx::getEventFailureCallback())(AdjustEventFailure2dx) {
    return eventFailureCallback;
}

void(*ADJConfig2dx::getSessionSuccessCallback())(AdjustSessionSuccess2dx) {
    return sessionSuccessCallback;
}

void(*ADJConfig2dx::getSessionFailureCallback())(AdjustSessionFailure2dx) {
    return sessionFailureCallback;
}

bool(*ADJConfig2dx::getDeferredDeeplinkCallback())(std::string) {
    return deferredDeeplinkCallback;
}

void(*ADJConfig2dx::getConversionValueUpdatedCallback())(int) {
    return conversionValueUpdatedCallback;
}

void(*ADJConfig2dx::getPostbackConversionValueUpdatedCallback())(int, std::string, bool) {
    return postbackConversionValueUpdatedCallback;
}
