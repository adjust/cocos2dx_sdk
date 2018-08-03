//
//  AdjustCommandDelegate.h
//  Adjust SDK
//
//  Created by Srdjan Tubin (@2beens) on 30th July 2018.
//  Copyright © 2018 Adjust GmbH. All rights reserved.
//

#import <AdjustTestLibrary/ATLTestLibrary.h>

@interface AdjustCommandDelegate2dx : NSObject<AdjustCommandDelegate>

@property (nonatomic) void (*commandExecutorCallback)(std::string className, std::string methodName, std::string jsonParameters);

+ (id)getInstanceWithCommandExecutorCallbackId:(void (*)(std::string className, std::string methodName, std::string jsonParameters))commandExecutorCallbackId;

@end