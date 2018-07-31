//
//  ATLTestLibrary2dx.mm
//  Adjust SDK
//
//  Created by Srdjan Tubin on 30/07/18.
//  Copyright © 2015-2018 Adjust GmbH. All rights reserved.
//

#include <iostream>
#include "ATLTestLibrary2dx.h"
#include "AdjustCommandDelegate2dx.h"
#include <AdjustTestLibrary/ATLTestLibrary.h>

ATLTestLibrary2dx::ATLTestLibrary2dx(std::string baseUrl, void(*executeCommandCallback)(std::string className, std::string methodName, std::string jsonParameters)) {
	AdjustCommandDelegate2dx *adjustCommandDelegate = [AdjustCommandDelegate2dx getInstanceWithCommandExecutorCallbackId:executeCommandCallback];
	testLibrary = [ATLTestLibrary testLibraryWithBaseUrl:[NSString stringWithUTF8String:baseUrl.c_str()] 
									  andCommandDelegate:adjustCommandDelegate];
}

void ATLTestLibrary2dx::addTest(std::string testName) {
	[((ATLTestLibrary *)testLibrary) addTest:[NSString stringWithUTF8String:testName.c_str()]];
}

void ATLTestLibrary2dx::addTestDirectory(std::string testDirectory) {
	[((ATLTestLibrary *)testLibrary) addTestDirectory:[NSString stringWithUTF8String:testDirectory.c_str()]];
}

void ATLTestLibrary2dx::startTestSession(std::string clientSdk) {
	[((ATLTestLibrary *)testLibrary) startTestSession:[NSString stringWithUTF8String:clientSdk.c_str()]];
}

void ATLTestLibrary2dx::addInfoToSend(std::string key, std::string value) {
	[((ATLTestLibrary *)testLibrary) addInfoToSend:[NSString stringWithUTF8String:key.c_str()] 
											 value:[NSString stringWithUTF8String:value.c_str()]];
}

void ATLTestLibrary2dx::sendInfoToServer(std::string basePath) {
	[((ATLTestLibrary *)testLibrary) sendInfoToServer:[NSString stringWithUTF8String:basePath.c_str()]];
}
