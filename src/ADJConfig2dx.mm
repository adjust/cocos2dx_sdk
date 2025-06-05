//
//  ADJConfig2dx.mm
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 17th June 2015.
//  Copyright © 2015-Present Adjust GmbH. All rights reserved.
//

#include "ADJConfig2dx.h"
#include "ADJDelegate2dx.h"
#include <AdjustSdk/AdjustSdk.h>

void ADJConfig2dx::initConfig(std::string appToken, std::string environment, bool allowSuppressLogLevel, std::string sdkPrefix) {
    config = [[ADJConfig alloc] initWithAppToken:[NSString stringWithUTF8String:appToken.c_str()]
                                     environment:[NSString stringWithUTF8String:environment.c_str()]
                                suppressLogLevel:allowSuppressLogLevel];
    [((ADJConfig *)config) setSdkPrefix:[NSString stringWithUTF8String:sdkPrefix.c_str()]];
}

void ADJConfig2dx::setLogLevel(ADJLogLevel2dx logLevel) {
    ((ADJConfig *)config).logLevel = (ADJLogLevel)logLevel;
}

void ADJConfig2dx::enableSendingInBackground() {
    [((ADJConfig *)config) enableSendingInBackground];
}

void ADJConfig2dx::disableIdfaReading() {
    [((ADJConfig *)config) disableIdfaReading];
}

void ADJConfig2dx::disableIdfvReading() {
    [((ADJConfig *)config) disableIdfvReading];
}

void ADJConfig2dx::disableAdServices() {
    [((ADJConfig *)config) disableAdServices];
}

void ADJConfig2dx::enableCostDataInAttribution() {
    [((ADJConfig *)config) enableCostDataInAttribution];
}

void ADJConfig2dx::setDefaultTracker(std::string defaultTracker) {
    ((ADJConfig *)config).defaultTracker = [NSString stringWithUTF8String:defaultTracker.c_str()];
}

void ADJConfig2dx::setExternalDeviceId(std::string externalDeviceId) {
    ((ADJConfig *)config).externalDeviceId = [NSString stringWithUTF8String:externalDeviceId.c_str()];
}

void ADJConfig2dx::setUrlStrategy(std::vector<std::string> urlStrategyDomains,
                                  bool useSubdomains,
                                  bool isDataResidency)
{
    NSMutableArray *urlStrategyDomainsMut = [[NSMutableArray alloc] init];
    for (std::vector<std::string>::iterator toIterator = urlStrategyDomains.begin();
         toIterator != urlStrategyDomains.end(); toIterator++)
    {
        std::string urlStrategyDomain = (*toIterator);
        [urlStrategyDomainsMut addObject:[NSString stringWithUTF8String:urlStrategyDomain.c_str()]];
    }

    [((ADJConfig *)config) setUrlStrategy:(NSArray *)urlStrategyDomainsMut
                            useSubdomains:useSubdomains
                          isDataResidency:isDataResidency];
}

void ADJConfig2dx::disableSkanAttribution() {
    [((ADJConfig *)config) disableSkanAttribution];
}

void ADJConfig2dx::enableLinkMe() {
    [((ADJConfig *)config) enableLinkMe];
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

void ADJConfig2dx::setSkanUpdatedCallback(void(*callbackMethod)(std::unordered_map<std::string, std::string> data)) {
    skanUpdatedCallback = callbackMethod;
}

void* ADJConfig2dx::getConfig() {
    return config;
}

void ADJConfig2dx::enableDeviceIdsReadingOnce() {
    [((ADJConfig *)config) enableDeviceIdsReadingOnce];
}

void ADJConfig2dx::enableCoppaCompliance() {
    [((ADJConfig *)config) enableCoppaCompliance];
}

void ADJConfig2dx::setEventDeduplicationIdsMaxSize(int eventDeduplicationIdsMaxSize) {
    ((ADJConfig *)config).eventDeduplicationIdsMaxSize = eventDeduplicationIdsMaxSize;
}

void ADJConfig2dx::disableAppTrackingTransparencyUsage() {
    [((ADJConfig *)config) disableAppTrackingTransparencyUsage];
}

void ADJConfig2dx::enableFirstSessionDelay() {
    [((ADJConfig *)config) enableFirstSessionDelay];
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

void(*ADJConfig2dx::getSkanUpdatedCallback())(std::unordered_map<std::string, std::string>) {
    return skanUpdatedCallback;
}
