//
//  ATLAdjustTestOptions2dx.mm
//  Adjust SDK
//
//  Created by Srdjan Tubin on 30/07/18.
//  Copyright © 2015-2018 Adjust GmbH. All rights reserved.
//

#include "ATLAdjustTestOptions2dx.h"
#include <AdjustSdk/Adjust.h>

ATLAdjustTestOptions2dx::ATLAdjustTestOptions2dx() {
	testOptions = [[AdjustTestOptions alloc] init];
}

void ATLAdjustTestOptions2dx::setBaseUrl(std::string baseUrl) {
	((AdjustTestOptions *)testOptions).baseUrl = [NSString stringWithUTF8String:baseUrl.c_str()];
}

void ATLAdjustTestOptions2dx::setGdprUrl(std::string gdprUrl) {
	((AdjustTestOptions *)testOptions).gdprUrl = [NSString stringWithUTF8String:gdprUrl.c_str()];
}

void ATLAdjustTestOptions2dx::setBasePath(std::string basePath) {
	((AdjustTestOptions *)testOptions).basePath = [NSString stringWithUTF8String:basePath.c_str()];
}

void ATLAdjustTestOptions2dx::setGdprPath(std::string gdprPath) {
	((AdjustTestOptions *)testOptions).gdprPath = [NSString stringWithUTF8String:gdprPath.c_str()];
}

void ATLAdjustTestOptions2dx::setTimerIntervalInMilliseconds(long timerIntervalInMilliseconds) {
    ((AdjustTestOptions *)testOptions).timerIntervalInMilliseconds = [NSNumber numberWithLong:timerIntervalInMilliseconds];
}

void ATLAdjustTestOptions2dx::setTimerStartInMilliseconds(long timerStartInMilliseconds) {
    ((AdjustTestOptions *)testOptions).timerStartInMilliseconds = [NSNumber numberWithLong:timerStartInMilliseconds];
}

void ATLAdjustTestOptions2dx::setSessionIntervalInMilliseconds(long sessionIntervalInMilliseconds) {
    ((AdjustTestOptions *)testOptions).sessionIntervalInMilliseconds = [NSNumber numberWithLong:sessionIntervalInMilliseconds];
}

void ATLAdjustTestOptions2dx::setSubsessionIntervalInMilliseconds(long subsessionIntervalInMilliseconds) {
    ((AdjustTestOptions *)testOptions).subsessionIntervalInMilliseconds = [NSNumber numberWithLong:subsessionIntervalInMilliseconds];
}

void ATLAdjustTestOptions2dx::setTeardown(bool teardown) {
	((AdjustTestOptions *)testOptions).teardown = teardown;
}

void ATLAdjustTestOptions2dx::setDeleteState(bool deleteState) {
	((AdjustTestOptions *)testOptions).deleteState = deleteState;
}

void ATLAdjustTestOptions2dx::setNoBackoffWait(bool noBackoffWait) {
	((AdjustTestOptions *)testOptions).noBackoffWait = noBackoffWait;
}

void ATLAdjustTestOptions2dx::setIAdFrameworkEnabled(bool iAdFrameworkEnabled) {
	((AdjustTestOptions *)testOptions).iAdFrameworkEnabled = iAdFrameworkEnabled;
}

void* ATLAdjustTestOptions2dx::getTestOptions() {
	return testOptions;
}
