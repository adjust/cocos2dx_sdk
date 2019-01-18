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

void ADJConfig2dx::setUserAgent(std::string userAgent) {
    ((ADJConfig *)config).userAgent = [NSString stringWithUTF8String:userAgent.c_str()];
}

void ADJConfig2dx::setDefaultTracker(std::string defaultTracker) {
    ((ADJConfig *)config).defaultTracker = [NSString stringWithUTF8String:defaultTracker.c_str()];
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

void* ADJConfig2dx::getConfig() {
    return config;
}

void ADJConfig2dx::setAppSecret(long secretId, long info1, long info2, long info3, long info4) {
    [((ADJConfig *)config) setAppSecret:secretId info1:info1 info2:info2 info3:info3 info4:info4];
}

void ADJConfig2dx::setIsDeviceKnown(bool isDeviceKnown) {
    [((ADJConfig *)config) setIsDeviceKnown:isDeviceKnown];
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
