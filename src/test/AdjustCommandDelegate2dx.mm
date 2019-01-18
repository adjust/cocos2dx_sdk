//
//  AdjustCommandDelegate.mm
//  Adjust SDK
//
//  Created by Srdjan Tubin (@2beens) on 30th July 2018.
//  Copyright © 2018-2019 Adjust GmbH. All rights reserved.
//

#import <objc/runtime.h>
#import "AdjustCommandDelegate2dx.h"

@implementation AdjustCommandDelegate2dx

+ (id)getInstanceWithCommandExecutorCallbackId:(void (*)(std::string className, std::string methodName, std::string jsonParameters))commandExecutorCallbackId {
    static dispatch_once_t onceToken;
    static AdjustCommandDelegate2dx *defaultInstance = nil;

    dispatch_once(&onceToken, ^{
        defaultInstance = [[AdjustCommandDelegate2dx alloc] init];
        [defaultInstance setCommandExecutorCallback:commandExecutorCallbackId];
    });

    return defaultInstance;
}

- (id)init {
    self = [super init];
    if (nil == self) {
        return nil;
    }
    return self;
}

- (void)executeCommand:(NSString *)className
            methodName:(NSString *)methodName
        jsonParameters:(NSString *)jsonParameters {
    if (nil == _commandExecutorCallback) {
        return;
    }

    std::string strClassName = std::string([className UTF8String]);
    std::string strMethodName = std::string([methodName UTF8String]);
    std::string strJsonParameters = std::string([jsonParameters UTF8String]);
    _commandExecutorCallback(strClassName, strMethodName, strJsonParameters);
}

@end