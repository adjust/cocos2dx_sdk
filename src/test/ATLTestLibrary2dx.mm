//
//  ATLTestLibrary2dx.mm
//  Adjust SDK
//
//  Created by Srdjan Tubin (@2beens) on 30th July 2018.
//  Copyright © 2018-Present Adjust GmbH. All rights reserved.
//

#include <iostream>
#include "ATLTestLibrary2dx.h"
#include "AdjustCommandDelegate2dx.h"
#include <AdjustTestLibrary/ATLTestLibrary.h>

@interface ATLTestLibraryWrapper : NSObject

@property (nonatomic, strong) ATLTestLibrary *testLibrary;

@end

@implementation ATLTestLibraryWrapper
@end

ATLTestLibrary2dx::ATLTestLibrary2dx(std::string baseUrl, std::string controlUrl, void(*executeCommandCallback)(std::string className, std::string methodName, std::string jsonParameters)) {
	AdjustCommandDelegate2dx *adjustCommandDelegate =
    [AdjustCommandDelegate2dx getInstanceWithCommandExecutorCallbackId:executeCommandCallback];
	ATLTestLibrary *atlTestLib =
    [ATLTestLibrary testLibraryWithBaseUrl:[NSString stringWithUTF8String:baseUrl.c_str()]
                             andControlUrl:[NSString stringWithUTF8String:controlUrl.c_str()]
                        andCommandDelegate:adjustCommandDelegate];

	ATLTestLibraryWrapper *testLibWrapper = [[ATLTestLibraryWrapper alloc] init];
	testLibWrapper.testLibrary = atlTestLib;
	testLibrary = (void *)testLibWrapper;
}

ATLTestLibrary2dx::~ATLTestLibrary2dx() {
	if (testLibrary != nullptr) {
		CFBridgingRelease(testLibrary);
		testLibrary = nullptr;
	}
}

void ATLTestLibrary2dx::addTest(std::string testName) {
	ATLTestLibraryWrapper *testLibWrapper = (__bridge ATLTestLibraryWrapper *)testLibrary;
	[testLibWrapper.testLibrary addTest:[NSString stringWithUTF8String:testName.c_str()]];
}

void ATLTestLibrary2dx::addTestDirectory(std::string testDirectory) {
	ATLTestLibraryWrapper *testLibWrapper = (__bridge ATLTestLibraryWrapper *)testLibrary;
	[testLibWrapper.testLibrary addTestDirectory:[NSString stringWithUTF8String:testDirectory.c_str()]];
}

void ATLTestLibrary2dx::startTestSession(std::string clientSdk) {
    ATLTestLibraryWrapper *testLibWrapper = (__bridge ATLTestLibraryWrapper *)testLibrary;
    NSString *clientSdkString = [NSString stringWithUTF8String:clientSdk.c_str()];
    [testLibWrapper.testLibrary startTestSession:clientSdkString];
}

void ATLTestLibrary2dx::addInfoToSend(std::string key, std::string value) {
	ATLTestLibraryWrapper *testLibWrapper = (__bridge ATLTestLibraryWrapper *)testLibrary;
	[testLibWrapper.testLibrary addInfoToSend:[NSString stringWithUTF8String:key.c_str()] 
                                        value:[NSString stringWithUTF8String:value.c_str()]];
}

void ATLTestLibrary2dx::sendInfoToServer(std::string basePath) {
	ATLTestLibraryWrapper *testLibWrapper = (__bridge ATLTestLibraryWrapper *)testLibrary;
	[testLibWrapper.testLibrary sendInfoToServer:[NSString stringWithUTF8String:basePath.c_str()]];
}
