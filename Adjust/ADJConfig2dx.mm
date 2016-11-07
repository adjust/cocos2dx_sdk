//
//  ADJConfig2dx.mm
//  AdjustSDK
//
//  Created by Uglješa Erceg on 17/06/15.
//
//

#include "ADJConfig2dx.h"

#include <AdjustSdk/Adjust.h>

@interface AdjustDelegate2dx : NSObject<AdjustDelegate>

@end

@implementation AdjustDelegate2dx

void (*attributionCallbackMethod)(AdjustAttribution2dx attribution);
void (*eventSuccessCallbackMethod)(AdjustEventSuccess2dx eventSuccess);
void (*eventFailureCallbackMethod)(AdjustEventFailure2dx eventFailure);
void (*sessionSuccessCallbackMethod)(AdjustSessionSuccess2dx sessionSuccess);
void (*sessionFailureCallbackMethod)(AdjustSessionFailure2dx sessionFailure);
bool (*deferredDeeplinkCallbackMethod)(std::string deeplink);

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

    if (nil != attribution) {
        if (nil != attribution.trackerToken) {
            trackerToken = std::string([attribution.trackerToken UTF8String]);
        }

        if (nil != attribution.trackerName) {
            trackerName = std::string([attribution.trackerName UTF8String]);
        }

        if (nil != attribution.network) {
            network = std::string([attribution.network UTF8String]);
        }

        if (nil != attribution.campaign) {
            campaign = std::string([attribution.campaign UTF8String]);
        }

        if (nil != attribution.adgroup) {
            adgroup = std::string([attribution.adgroup UTF8String]);
        }

        if (nil != attribution.creative) {
            creative = std::string([attribution.creative UTF8String]);
        }

        if (nil != attribution.clickLabel) {
            clickLabel = std::string([attribution.clickLabel UTF8String]);
        }
    }

    AdjustAttribution2dx attribution2dx = AdjustAttribution2dx(trackerToken, trackerName, network, campaign, adgroup, creative,clickLabel);

    if (nil != attributionCallbackMethod) {
        attributionCallbackMethod(attribution2dx);
    }
}

- (void)adjustEventTrackingSucceeded:(ADJEventSuccess *)eventSuccess {
    std::string message;
    std::string timestamp;
    std::string adid;
    std::string eventToken;
    std::string jsonResponse;

    if (nil != eventSuccess) {
        if (nil != eventSuccess.message) {
            message = std::string([eventSuccess.message UTF8String]);
        }

        if (nil != eventSuccess.timeStamp) {
            timestamp = std::string([eventSuccess.timeStamp UTF8String]);
        }

        if (nil != eventSuccess.adid) {
            adid = std::string([eventSuccess.adid UTF8String]);
        }

        if (nil != eventSuccess.eventToken) {
            eventToken = std::string([eventSuccess.eventToken UTF8String]);
        }

        if (nil != eventSuccess.jsonResponse) {
            jsonResponse = std::string([[NSString stringWithFormat:@"%@", eventSuccess.jsonResponse] UTF8String]);
        }
    }

    AdjustEventSuccess2dx eventSuccess2dx = AdjustEventSuccess2dx(adid, message, timestamp, eventToken, jsonResponse);

    if (nil != eventSuccessCallbackMethod) {
        eventSuccessCallbackMethod(eventSuccess2dx);
    }
}

- (void)adjustEventTrackingFailed:(ADJEventFailure *)eventFailure {
    std::string message;
    std::string timestamp;
    std::string adid;
    std::string eventToken;
    std::string willRetry;
    std::string jsonResponse;

    if (nil != eventFailure) {
        if (nil != eventFailure.message) {
            message = std::string([eventFailure.message UTF8String]);
        }

        if (nil != eventFailure.timeStamp) {
            timestamp = std::string([eventFailure.timeStamp UTF8String]);
        }

        if (nil != eventFailure.adid) {
            adid = std::string([eventFailure.adid UTF8String]);
        }

        if (nil != eventFailure.eventToken) {
            eventToken = std::string([eventFailure.eventToken UTF8String]);
        }

        willRetry = eventFailure.willRetry ? "true" : "false";

        if (nil != eventFailure.jsonResponse) {
            jsonResponse = std::string([[NSString stringWithFormat:@"%@", eventFailure.jsonResponse] UTF8String]);
        }
    }

    AdjustEventFailure2dx eventFailure2dx = AdjustEventFailure2dx(adid, message, timestamp, willRetry, eventToken, jsonResponse);

    if (nil != eventFailureCallbackMethod) {
        eventFailureCallbackMethod(eventFailure2dx);
    }
}

- (void)adjustSessionTrackingSucceeded:(ADJSessionSuccess *)sessionSuccess {
    std::string message;
    std::string timestamp;
    std::string adid;
    std::string jsonResponse;

    if (nil != sessionSuccess) {
        if (nil != sessionSuccess.message) {
            message = std::string([sessionSuccess.message UTF8String]);
        }

        if (nil != sessionSuccess.timeStamp) {
            timestamp = std::string([sessionSuccess.timeStamp UTF8String]);
        }

        if (nil != sessionSuccess.adid) {
            adid = std::string([sessionSuccess.adid UTF8String]);
        }

        if (nil != sessionSuccess.jsonResponse) {
            jsonResponse = std::string([[NSString stringWithFormat:@"%@", sessionSuccess.jsonResponse] UTF8String]);
        }
    }

    AdjustSessionSuccess2dx sessionSuccess2dx = AdjustSessionSuccess2dx(adid, message, timestamp, jsonResponse);

    if (nil != sessionSuccessCallbackMethod) {
        sessionSuccessCallbackMethod(sessionSuccess2dx);
    }
}

- (void)adjustSessionTrackingFailed:(ADJSessionFailure *)sessionFailure {
    std::string message;
    std::string timestamp;
    std::string adid;
    std::string willRetry;
    std::string jsonResponse;

    if (nil != sessionFailure) {
        if (nil != sessionFailure.message) {
            message = std::string([sessionFailure.message UTF8String]);
        }

        if (nil != sessionFailure.timeStamp) {
            timestamp = std::string([sessionFailure.timeStamp UTF8String]);
        }

        if (nil != sessionFailure.adid) {
            adid = std::string([sessionFailure.adid UTF8String]);
        }

        willRetry = sessionFailure.willRetry ? "true" : "false";

        if (nil != sessionFailure.jsonResponse) {
            jsonResponse = std::string([[NSString stringWithFormat:@"%@", sessionFailure.jsonResponse] UTF8String]);
        }
    }

    AdjustSessionFailure2dx sessionFailure2dx = AdjustSessionFailure2dx(adid, message, timestamp, willRetry, jsonResponse);

    if (nil != sessionFailureCallbackMethod) {
        sessionFailureCallbackMethod(sessionFailure2dx);
    }
}

- (BOOL)adjustDeeplinkResponse:(NSURL *)deeplink {
    if (nil != deferredDeeplinkCallbackMethod) {
        return deferredDeeplinkCallbackMethod(nil != deeplink ? std::string([[deeplink absoluteString] UTF8String]) : "");
    }
    
    return YES;
}

@end

void ADJConfig2dx::initConfig(std::string appToken, std::string environment, bool allowSuppressLogLevel, std::string sdkPrefix) {
    config = [[ADJConfig alloc] initWithAppToken:[NSString stringWithUTF8String:appToken.c_str()]
                                     environment:[NSString stringWithUTF8String:environment.c_str()]
                           allowSuppressLogLevel:allowSuppressLogLevel];
    [((ADJConfig *)config) setSdkPrefix:[NSString stringWithUTF8String:sdkPrefix.c_str()]];

    AdjustDelegate2dx *adjustDelegate2dx = [[AdjustDelegate2dx alloc] init];
    ((ADJConfig *)config).delegate = adjustDelegate2dx;
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
    attributionCallbackMethod = attributionCallback;
}

void ADJConfig2dx::setEventSuccessCallback(void(*callbackMethod)(AdjustEventSuccess2dx eventSuccess)) {
    eventSuccessCallback = callbackMethod;
    eventSuccessCallbackMethod = eventSuccessCallback;
}

void ADJConfig2dx::setEventFailureCallback(void(*callbackMethod)(AdjustEventFailure2dx eventFailure)) {
    eventFailureCallback = callbackMethod;
    eventFailureCallbackMethod = eventFailureCallback;
}

void ADJConfig2dx::setSessionSuccessCallback(void(*callbackMethod)(AdjustSessionSuccess2dx sessionSuccess)) {
    sessionSuccessCallback = callbackMethod;
    sessionSuccessCallbackMethod = sessionSuccessCallback;
}

void ADJConfig2dx::setSessionFailureCallback(void(*callbackMethod)(AdjustSessionFailure2dx sessionFailure)) {
    sessionFailureCallback = callbackMethod;
    sessionFailureCallbackMethod = sessionFailureCallback;
}

void ADJConfig2dx::setDeferredDeeplinkCallback(bool(*callbackMethod)(std::string deeplink)) {
    deferredDeeplinkCallback = callbackMethod;
    deferredDeeplinkCallbackMethod = deferredDeeplinkCallback;
}

void* ADJConfig2dx::getConfig() {
    return config;
}
