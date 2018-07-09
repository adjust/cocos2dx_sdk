//
//  ADJDelegate2dx.h
//  Adjust
//
//  Created by uerceg on 12/20/16.
//  Copyright (c) 2012-2016 adjust GmbH. All rights reserved.
//

#import <AdjustSdk/Adjust.h>

@interface ADJDelegate2dx : NSObject<AdjustDelegate>

@property (nonatomic) void (*attributionCallbackMethod)(AdjustAttribution2dx attribution);
@property (nonatomic) void (*eventSuccessCallbackMethod)(AdjustEventSuccess2dx eventSuccess);
@property (nonatomic) void (*eventFailureCallbackMethod)(AdjustEventFailure2dx eventFailure);
@property (nonatomic) void (*sessionSuccessCallbackMethod)(AdjustSessionSuccess2dx sessionSuccess);
@property (nonatomic) void (*sessionFailureCallbackMethod)(AdjustSessionFailure2dx sessionFailure);
@property (nonatomic) bool (*deferredDeeplinkCallbackMethod)(std::string deeplink);

+ (id)getInstanceWithSwizzleOfAttributionCallback:(BOOL)swizzleAttributionCallback
                    swizzleOfEventSuccessCallback:(BOOL)swizzleEventSuccessCallback
                    swizzleOfEventFailureCallback:(BOOL)swizzleEventFailureCallback
                  swizzleOfSessionSuccessCallback:(BOOL)swizzleSessionSuccessCallback
                  swizzleOfSessionFailureCallback:(BOOL)swizzleSessionFailureCallback
                swizzleOfDeferredDeeplinkCallback:(BOOL)swizzleDeferredDeeplinkCallback
						 andAttributionCallbackId:(void (*)(AdjustAttribution2dx attribution))attributionCallbackId
                           eventSuccessCallbackId:(void (*)(AdjustEventSuccess2dx eventSuccess))eventSuccessCallbackId
                           eventFailureCallbackId:(void (*)(AdjustEventFailure2dx eventFailure))eventFailureCallbackId
                         sessionSuccessCallbackId:(void (*)(AdjustSessionSuccess2dx sessionSuccess))sessionSuccessCallbackId
                         sessionFailureCallbackId:(void (*)(AdjustSessionFailure2dx sessionFailure))sessionFailureCallbackId
					   deferredDeeplinkCallbackId:(bool (*)(std::string deeplink))deferredDeeplinkCallbackId;

@end
