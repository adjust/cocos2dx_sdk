//
//  AdjustCordovaDelegate.m
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 20th December 2016.
//  Copyright © 2016-2019 Adjust GmbH. All rights reserved.
//

#import <objc/runtime.h>
#import "ADJAdjust2dx.h"
#import "ADJDelegate2dx.h"

static dispatch_once_t onceToken;
static ADJDelegate2dx *defaultInstance = nil;

@implementation ADJDelegate2dx

+ (id)getInstanceWithSwizzleOfAttributionCallback:(BOOL)swizzleAttributionCallback
                    swizzleOfEventSuccessCallback:(BOOL)swizzleEventSuccessCallback
                    swizzleOfEventFailureCallback:(BOOL)swizzleEventFailureCallback
                  swizzleOfSessionSuccessCallback:(BOOL)swizzleSessionSuccessCallback
                  swizzleOfSessionFailureCallback:(BOOL)swizzleSessionFailureCallback
                swizzleOfDeferredDeeplinkCallback:(BOOL)swizzleDeferredDeeplinkCallback
     swizzleSkanUpdatedWithConversionDataCallback:(BOOL)swizzleSkanUpdatedWithConversionDataCallback
                         andAttributionCallbackId:(void (*)(AdjustAttribution2dx attribution))attributionCallbackId
                           eventSuccessCallbackId:(void (*)(AdjustEventSuccess2dx eventSuccess))eventSuccessCallbackId
                           eventFailureCallbackId:(void (*)(AdjustEventFailure2dx eventFailure))eventFailureCallbackId
                         sessionSuccessCallbackId:(void (*)(AdjustSessionSuccess2dx sessionSuccess))sessionSuccessCallbackId
                         sessionFailureCallbackId:(void (*)(AdjustSessionFailure2dx sessionFailure))sessionFailureCallbackId
                       deferredDeeplinkCallbackId:(bool (*)(std::string deeplink))deferredDeeplinkCallbackId
          skanUpdatedWithConversionDataCallbackId:(void (*)(std::unordered_map<std::string, std::string> data))skanUpdatedWithConversionDataCallbackId
{
    dispatch_once(&onceToken, ^{
        defaultInstance = [[ADJDelegate2dx alloc] init];

        // Do the swizzling where and if needed.
        if (swizzleAttributionCallback) {
            [defaultInstance swizzleCallbackMethod:@selector(adjustAttributionChanged:)
                                  swizzledSelector:@selector(adjustAttributionChangedWannabe:)];
        }
        if (swizzleEventSuccessCallback) {
            [defaultInstance swizzleCallbackMethod:@selector(adjustEventTrackingSucceeded:)
                                  swizzledSelector:@selector(adjustEventTrackingSucceededWannabe:)];
        }
        if (swizzleEventFailureCallback) {
            [defaultInstance swizzleCallbackMethod:@selector(adjustEventTrackingFailed:)
                                  swizzledSelector:@selector(adjustEventTrackingFailedWannabe:)];
        }
        if (swizzleSessionSuccessCallback) {
            [defaultInstance swizzleCallbackMethod:@selector(adjustSessionTrackingSucceeded:)
                                  swizzledSelector:@selector(adjustSessionTrackingSucceededWannabe:)];
        }
        if (swizzleSessionFailureCallback) {
            [defaultInstance swizzleCallbackMethod:@selector(adjustSessionTrackingFailed:)
                                  swizzledSelector:@selector(adjustSessionTrackingFailedWananbe:)];
        }
        if (swizzleDeferredDeeplinkCallback) {
            [defaultInstance swizzleCallbackMethod:@selector(adjustDeferredDeeplinkReceived:)
                                  swizzledSelector:@selector(adjustDeferredDeeplinkReceivedWannabe:)];
        }
        if (swizzleSkanUpdatedWithConversionDataCallback) {
            [defaultInstance swizzleCallbackMethod:@selector(adjustSkanUpdatedWithConversionData:)
                                  swizzledSelector:@selector(adjustSkanUpdatedWithConversionDataWannabe:)];
        }

        [defaultInstance setAttributionCallbackMethod:attributionCallbackId];
        [defaultInstance setEventSuccessCallbackMethod:eventSuccessCallbackId];
        [defaultInstance setEventFailureCallbackMethod:eventFailureCallbackId];
        [defaultInstance setSessionSuccessCallbackMethod:sessionSuccessCallbackId];
        [defaultInstance setSessionFailureCallbackMethod:sessionFailureCallbackId];
        [defaultInstance setDeferredDeeplinkCallbackMethod:deferredDeeplinkCallbackId];
        [defaultInstance setSkanUpdatedWithConversionDataCallbackMethod:skanUpdatedWithConversionDataCallbackId];
    });
    
    return defaultInstance;
}

+ (void)teardown {
    defaultInstance = nil;
    onceToken = 0;
}

- (id)init {
    self = [super init];
    if (nil == self) {
        return nil;
    }
    return self;
}

- (void)adjustAttributionChangedWannabe:(ADJAttribution *)attribution {
    if (nil == attribution) {
        return;
    }
    if (nil == _attributionCallbackMethod) {
        return;
    }

    NSMutableDictionary *dictionary = [NSMutableDictionary dictionary];
    [self addValueOrEmpty:dictionary key:@"trackerToken" value:attribution.trackerToken];
    [self addValueOrEmpty:dictionary key:@"trackerName" value:attribution.trackerName];
    [self addValueOrEmpty:dictionary key:@"network" value:attribution.network];
    [self addValueOrEmpty:dictionary key:@"campaign" value:attribution.campaign];
    [self addValueOrEmpty:dictionary key:@"creative" value:attribution.creative];
    [self addValueOrEmpty:dictionary key:@"adgroup" value:attribution.adgroup];
    [self addValueOrEmpty:dictionary key:@"clickLabel" value:attribution.clickLabel];
    [self addValueOrEmpty:dictionary key:@"costType" value:attribution.costType];
    [self addValueOrEmpty:dictionary key:@"costAmount" value:attribution.costAmount];
    [self addValueOrEmpty:dictionary key:@"costCurrency" value:attribution.costCurrency];
    
    std::string trackerToken = std::string([[dictionary objectForKey:@"trackerToken"] UTF8String]);
    std::string trackerName = std::string([[dictionary objectForKey:@"trackerName"] UTF8String]);
    std::string network = std::string([[dictionary objectForKey:@"network"] UTF8String]);
    std::string campaign = std::string([[dictionary objectForKey:@"campaign"] UTF8String]);
    std::string creative = std::string([[dictionary objectForKey:@"creative"] UTF8String]);
    std::string adgroup = std::string([[dictionary objectForKey:@"adgroup"] UTF8String]);
    std::string clickLabel = std::string([[dictionary objectForKey:@"clickLabel"] UTF8String]);
    std::string costType = std::string([[dictionary objectForKey:@"costType"] UTF8String]);
    double costAmount = [dictionary objectForKey:@"costAmount"] != nil ? [[dictionary objectForKey:@"costAmount"] doubleValue] : 0;
    std::string costCurrency = std::string([[dictionary objectForKey:@"costCurrency"] UTF8String]);
    std::string fbInstallReferrer;

    AdjustAttribution2dx attribution2dx = AdjustAttribution2dx(
        trackerToken,
        trackerName,
        network,
        campaign,
        adgroup,
        creative,
        clickLabel,
        costType,
        costAmount,
        costCurrency,
        fbInstallReferrer);
    _attributionCallbackMethod(attribution2dx);
}

- (void)adjustEventTrackingSucceededWannabe:(ADJEventSuccess *)eventSuccessResponseData {
    if (nil == eventSuccessResponseData || NULL == _eventSuccessCallbackMethod) {
        return;
    }

    NSMutableDictionary *dictionary = [NSMutableDictionary dictionary];
    [self addValueOrEmpty:dictionary key:@"message" value:eventSuccessResponseData.message];
    [self addValueOrEmpty:dictionary key:@"timestamp" value:eventSuccessResponseData.timestamp];
    [self addValueOrEmpty:dictionary key:@"adid" value:eventSuccessResponseData.adid];
    [self addValueOrEmpty:dictionary key:@"eventToken" value:eventSuccessResponseData.eventToken];
    [self addValueOrEmpty:dictionary key:@"callbackId" value:eventSuccessResponseData.callbackId];

    std::string message = std::string([[dictionary objectForKey:@"message"] UTF8String]);
    std::string timestamp = std::string([[dictionary objectForKey:@"timestamp"] UTF8String]);
    std::string adid = std::string([[dictionary objectForKey:@"adid"] UTF8String]);
    std::string eventToken = std::string([[dictionary objectForKey:@"eventToken"] UTF8String]);
    std::string callbackId = std::string([[dictionary objectForKey:@"callbackId"] UTF8String]);
    std::string jsonResponse = "";
    if (eventSuccessResponseData.jsonResponse != nil) {
        NSData *dataJsonResponse = [NSJSONSerialization dataWithJSONObject:eventSuccessResponseData.jsonResponse options:0 error:nil];
        NSString *stringJsonResponse = [[NSString alloc] initWithBytes:[dataJsonResponse bytes]
                                                                length:[dataJsonResponse length]
                                                              encoding:NSUTF8StringEncoding];
        jsonResponse = [stringJsonResponse UTF8String];
    }

    AdjustEventSuccess2dx eventSuccess2dx = AdjustEventSuccess2dx(adid, message, timestamp, eventToken, callbackId, jsonResponse);
    _eventSuccessCallbackMethod(eventSuccess2dx);
}

- (void)adjustEventTrackingFailedWannabe:(ADJEventFailure *)eventFailureResponseData {
    if (nil == eventFailureResponseData || NULL == _eventFailureCallbackMethod) {
        return;
    }

    NSMutableDictionary *dictionary = [NSMutableDictionary dictionary];
    [self addValueOrEmpty:dictionary key:@"message" value:eventFailureResponseData.message];
    [self addValueOrEmpty:dictionary key:@"timestamp" value:eventFailureResponseData.timestamp];
    [self addValueOrEmpty:dictionary key:@"adid" value:eventFailureResponseData.adid];
    [self addValueOrEmpty:dictionary key:@"eventToken" value:eventFailureResponseData.eventToken];
    [self addValueOrEmpty:dictionary key:@"callbackId" value:eventFailureResponseData.callbackId];
    [dictionary setObject:(eventFailureResponseData.willRetry ? @"true" : @"false") forKey:@"willRetry"];

    std::string message = std::string([[dictionary objectForKey:@"message"] UTF8String]);
    std::string timestamp = std::string([[dictionary objectForKey:@"timestamp"] UTF8String]);
    std::string adid = std::string([[dictionary objectForKey:@"adid"] UTF8String]);
    std::string eventToken = std::string([[dictionary objectForKey:@"eventToken"] UTF8String]);
    std::string callbackId = std::string([[dictionary objectForKey:@"callbackId"] UTF8String]);
    std::string willRetry = std::string([[dictionary objectForKey:@"willRetry"] UTF8String]);
    std::string jsonResponse = "";
    if (eventFailureResponseData.jsonResponse != nil) {
        NSData *dataJsonResponse = [NSJSONSerialization dataWithJSONObject:eventFailureResponseData.jsonResponse options:0 error:nil];
        NSString *stringJsonResponse = [[NSString alloc] initWithBytes:[dataJsonResponse bytes]
                                                                length:[dataJsonResponse length]
                                                              encoding:NSUTF8StringEncoding];
        jsonResponse = [stringJsonResponse UTF8String];
    }

    AdjustEventFailure2dx eventFailure2dx = AdjustEventFailure2dx(adid, message, timestamp, willRetry, eventToken, callbackId, jsonResponse);
    _eventFailureCallbackMethod(eventFailure2dx);
}

- (void)adjustSessionTrackingSucceededWannabe:(ADJSessionSuccess *)sessionSuccessResponseData {
    if (nil == sessionSuccessResponseData || NULL == _sessionSuccessCallbackMethod) {
        return;
    }

    NSMutableDictionary *dictionary = [NSMutableDictionary dictionary];
    [self addValueOrEmpty:dictionary key:@"message" value:sessionSuccessResponseData.message];
    [self addValueOrEmpty:dictionary key:@"timestamp" value:sessionSuccessResponseData.timestamp];
    [self addValueOrEmpty:dictionary key:@"adid" value:sessionSuccessResponseData.adid];

    std::string message = std::string([[dictionary objectForKey:@"message"] UTF8String]);
    std::string timestamp = std::string([[dictionary objectForKey:@"timestamp"] UTF8String]);
    std::string adid = std::string([[dictionary objectForKey:@"adid"] UTF8String]);
    std::string jsonResponse = "";
    if (sessionSuccessResponseData.jsonResponse != nil) {
        NSData *dataJsonResponse = [NSJSONSerialization dataWithJSONObject:sessionSuccessResponseData.jsonResponse options:0 error:nil];
        NSString *stringJsonResponse = [[NSString alloc] initWithBytes:[dataJsonResponse bytes]
                                                                length:[dataJsonResponse length]
                                                              encoding:NSUTF8StringEncoding];
        jsonResponse = [stringJsonResponse UTF8String];
    }
    
    AdjustSessionSuccess2dx sessionSuccess2dx = AdjustSessionSuccess2dx(adid, message, timestamp, jsonResponse);
    _sessionSuccessCallbackMethod(sessionSuccess2dx);
}

- (void)adjustSessionTrackingFailedWananbe:(ADJSessionFailure *)sessionFailureResponseData {
    if (nil == sessionFailureResponseData || NULL == _sessionFailureCallbackMethod) {
        return;
    }

    NSMutableDictionary *dictionary = [NSMutableDictionary dictionary];
    [self addValueOrEmpty:dictionary key:@"message" value:sessionFailureResponseData.message];
    [self addValueOrEmpty:dictionary key:@"timestamp" value:sessionFailureResponseData.timestamp];
    [self addValueOrEmpty:dictionary key:@"adid" value:sessionFailureResponseData.adid];
    [dictionary setObject:(sessionFailureResponseData.willRetry ? @"true" : @"false") forKey:@"willRetry"];

    std::string message = std::string([[dictionary objectForKey:@"message"] UTF8String]);
    std::string timestamp = std::string([[dictionary objectForKey:@"timestamp"] UTF8String]);
    std::string adid = std::string([[dictionary objectForKey:@"adid"] UTF8String]);
    std::string willRetry = std::string([[dictionary objectForKey:@"willRetry"] UTF8String]);
    std::string jsonResponse = "";
    if (sessionFailureResponseData.jsonResponse != nil) {
        NSData *dataJsonResponse = [NSJSONSerialization dataWithJSONObject:sessionFailureResponseData.jsonResponse options:0 error:nil];
        NSString *stringJsonResponse = [[NSString alloc] initWithBytes:[dataJsonResponse bytes]
                                                                length:[dataJsonResponse length]
                                                              encoding:NSUTF8StringEncoding];
        jsonResponse = [stringJsonResponse UTF8String];
    }
    
    AdjustSessionFailure2dx sessionFailure2dx = AdjustSessionFailure2dx(adid, message, timestamp, willRetry, jsonResponse);
    _sessionFailureCallbackMethod(sessionFailure2dx);
}

- (BOOL)adjustDeferredDeeplinkReceivedWannabe:(NSURL *)deeplink {
    if (nil == deeplink || NULL == _deferredDeeplinkCallbackMethod) {
        return NO;
    }

    NSString *url = [deeplink absoluteString];
    std::string strDeeplink = std::string([url UTF8String]);
    return _deferredDeeplinkCallbackMethod(strDeeplink);
}

- (void)adjustSkanUpdatedWithConversionDataWannabe:(nonnull NSDictionary<NSString *, NSString *> *)data {
    if (nil == data || NULL == _skanUpdatedWithConversionDataCallbackMethod) {
        return;
    }

    std::unordered_map<std::string, std::string> cppMap;

    for (NSString *key in data) {
        cppMap[key.UTF8String] = data[key].UTF8String;
    }

    _skanUpdatedWithConversionDataCallbackMethod(cppMap);
}

- (void)swizzleCallbackMethod:(SEL)originalSelector
             swizzledSelector:(SEL)swizzledSelector {
    Class cls = [self class];
    Method originalMethod = class_getInstanceMethod(cls, originalSelector);
    Method swizzledMethod = class_getInstanceMethod(cls, swizzledSelector);
    BOOL didAddMethod = class_addMethod(cls,
                                        originalSelector,
                                        method_getImplementation(swizzledMethod),
                                        method_getTypeEncoding(swizzledMethod));
    if (didAddMethod) {
        class_replaceMethod(cls,
                            swizzledSelector,
                            method_getImplementation(originalMethod),
                            method_getTypeEncoding(originalMethod));
    } else {
        method_exchangeImplementations(originalMethod, swizzledMethod);
    }
}

- (void)addValueOrEmpty:(NSMutableDictionary *)dictionary
                    key:(NSString *)key
                  value:(NSObject *)value {
    if (nil != value) {
        if ([value isKindOfClass:[NSString class]]) {
            [dictionary setObject:[NSString stringWithFormat:@"%@", value] forKey:key];
        } else if ([value isKindOfClass:[NSNumber class]]) {
            [dictionary setObject:[NSString stringWithFormat:@"%@", [((NSNumber *)value) stringValue]] forKey:key];
        } else {
            [dictionary setObject:@"" forKey:key];
        }
    } else {
        [dictionary setObject:@"" forKey:key];
    }
}

@end
