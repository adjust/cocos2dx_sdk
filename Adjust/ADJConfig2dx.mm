//
//  ADJConfig2dx.mm
//  AdjustSDK
//
//  Created by Uglješa Erceg on 17/06/15.
//
//

#include "ADJConfig2dx.h"

#include <Adjust/Adjust.h>

@interface AttributionCallback : NSObject<AdjustDelegate>

@end

@implementation AttributionCallback

void (*callbackToTrigger)(AdjustAttribution2dx attribution);

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

    AdjustAttribution2dx attribution2dx = AdjustAttribution2dx(trackerToken, trackerName, network, campaign, adgroup, creative,clickLabel);

    callbackToTrigger(attribution2dx);
}

@end

void ADJConfig2dx::initConfig(std::string appToken, std::string environment, std::string sdkPrefix) {
    config = [[ADJConfig alloc] initWithAppToken:
                    [NSString stringWithUTF8String:appToken.c_str()]
                                           environment:
                    [NSString stringWithUTF8String:environment.c_str()]];
    [((ADJConfig *)config) setSdkPrefix:[NSString stringWithUTF8String:sdkPrefix.c_str()]];
}

void ADJConfig2dx::setLogLevel(ADJLogLevel2dx logLevel) {
    ((ADJConfig *)config).logLevel = (ADJLogLevel)logLevel;
}

void ADJConfig2dx::setDefaultTracker(std::string defaultTracker) {
    ((ADJConfig *)config).defaultTracker =
    [NSString stringWithUTF8String:defaultTracker.c_str()];
}

void ADJConfig2dx::setEventBufferingEnabled(bool isEnabled) {
    ((ADJConfig *)config).eventBufferingEnabled = isEnabled;
}

void ADJConfig2dx::setMacMd5TrackingEnabled(bool isEnabled) {
    ((ADJConfig *)config).macMd5TrackingEnabled = isEnabled;
}

void ADJConfig2dx::setAttributionCallback(void (*callbackMethod)(AdjustAttribution2dx attribution)) {
    callback = callbackMethod;
    callbackToTrigger = callback;

    AttributionCallback *attributionCallback = [[AttributionCallback alloc] init];
    ((ADJConfig *)config).delegate = attributionCallback;
}

void* ADJConfig2dx::getConfig() {
    return config;
}