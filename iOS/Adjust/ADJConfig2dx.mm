//
//  ADJConfig2dx.mm
//  AdjustDemo
//
//  Created by Uglješa Erceg on 17/06/15.
//
//

#include "ADJConfig2dx.h"

#include <Adjust/Adjust.h>

@interface AttributionCallback : NSObject<AdjustDelegate>

@end

@implementation AttributionCallback

void (*callbackToTrigger)(ADJAttribution2dx attribution);

- (id)init {
    self = [super init];
    return self;
}

- (void)adjustAttributionChanged:(ADJAttribution *)attribution {
    std::string trackerToken;
    std::string trackerName;
    std::string network;
    std::string campaign;
    std::string adgroup;
    std::string creative;
    std::string clickLabel;

    if (attribution.trackerToken != nil) {
        trackerToken = std::string([attribution.trackerToken UTF8String]);
    } else {
        trackerToken = "";
    }

    if (attribution.trackerName != nil) {
        trackerName = std::string([attribution.trackerName UTF8String]);
    } else {
        trackerName = "";
    }

    if (attribution.network != nil) {
        network = std::string([attribution.network UTF8String]);
    } else {
        network = "";
    }

    if (attribution.campaign != nil) {
        campaign = std::string([attribution.campaign UTF8String]);
    } else {
        campaign = "";
    }

    if (attribution.adgroup != nil) {
        adgroup = std::string([attribution.adgroup UTF8String]);
    } else {
        adgroup = "";
    }

    if (attribution.creative != nil) {
        creative = std::string([attribution.creative UTF8String]);
    } else {
        creative = "";
    }

    if (attribution.clickLabel != nil) {
        clickLabel = std::string([attribution.clickLabel UTF8String]);
    } else {
        clickLabel = "";
    }

    ADJAttribution2dx attribution2dx = ADJAttribution2dx(trackerToken, trackerName, network, campaign, adgroup, creative,clickLabel);

    callbackToTrigger(attribution2dx);
}

@end

void ADJConfig2dx::initConfig(std::string appToken, std::string environment) {
    config = [[ADJConfig alloc] initWithAppToken:
                    [NSString stringWithUTF8String:appToken.c_str()]
                                           environment:
                    [NSString stringWithUTF8String:environment.c_str()]];

    AttributionCallback *attributionCallback = [[AttributionCallback alloc] init];
    ((ADJConfig *)config).delegate = attributionCallback;
}

std::string ADJConfig2dx::getAppToken() {
    return std::string([((ADJConfig *)config).appToken UTF8String]);
}

void ADJConfig2dx::setLogLevel(ADJLogLevel2dx logLevel) {
    ((ADJConfig *)config).logLevel = (ADJLogLevel)logLevel;
}

ADJLogLevel2dx ADJConfig2dx::getLogLevel() {
    return (ADJLogLevel2dx)((ADJConfig *)config).logLevel;
}

std::string ADJConfig2dx::getEnvironment() {
    return std::string([((ADJConfig *)config).environment UTF8String]);
}

void ADJConfig2dx::setSdkPrefix(std::string sdkPrefix) {
    ((ADJConfig *)config).sdkPrefix = [NSString stringWithUTF8String:sdkPrefix.c_str()];
}

std::string ADJConfig2dx::getSdkPrefix() {
    return std::string([((ADJConfig *)config).sdkPrefix UTF8String]);
}

void ADJConfig2dx::setDefaultTracker(std::string defaultTracker) {
    ((ADJConfig *)config).defaultTracker =
    [NSString stringWithUTF8String:defaultTracker.c_str()];
}

std::string ADJConfig2dx::getDefaultTracker() {
    return std::string([((ADJConfig *)config).defaultTracker UTF8String]);
}

void ADJConfig2dx::setEventBufferingEnabled(bool isEnabled) {
    ((ADJConfig *)config).eventBufferingEnabled = isEnabled;
}

bool ADJConfig2dx::getEventBufferingEnabled() {
    return ((ADJConfig *)config).eventBufferingEnabled;
}

void ADJConfig2dx::setMacMd5TrackingEnabled(bool isEnabled) {
    ((ADJConfig *)config).macMd5TrackingEnabled = isEnabled;
}

bool ADJConfig2dx::getMacMd5TrackingEnabled() {
    return ((ADJConfig *)config).macMd5TrackingEnabled;
}

void ADJConfig2dx::setAttributionCallback(void (*callbackMethod)(ADJAttribution2dx attribution)) {
    callback = callbackMethod;
    callbackToTrigger = callback;
}

void* ADJConfig2dx::getConfig() {
    return config;
}