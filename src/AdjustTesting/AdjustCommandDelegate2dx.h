//
//  AdjustCommandDelegate.h
//  Adjust SDK
//
//  Created by Srdjan Tubin on 30/07/18.
//  Copyright © 2015-2018 Adjust GmbH. All rights reserved.
//

#import <AdjustTestLibrary/ATLTestLibrary.h>

@interface AdjustCommandDelegate2dx : NSObject<AdjustCommandDelegate>

@property (nonatomic) void (*commandExecutorCallback)(std::string className, std::string methodName, std::string jsonParameters);

+ (id)getInstanceWithCommandExecutorCallbackId:(void (*)(std::string className, std::string methodName, std::string jsonParameters))commandExecutorCallbackId;

@end