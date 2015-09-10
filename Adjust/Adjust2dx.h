//
//  Adjust2dx.h
//  Adjust SDK
//
//  Created by Uglješa Erceg on 16/06/15.
//

#ifndef ADJUST_ADJUST2DX_H_
#define ADJUST_ADJUST2DX_H_

#include <iostream>

#include "AdjustEvent2dx.h"
#include "AdjustConfig2dx.h"

extern const std::string AdjustEnvironmentSandbox2dx;
extern const std::string AdjustEnvironmentProduction2dx;

class Adjust2dx {
public:
	static void start(AdjustConfig2dx adjustConfig);
	static void trackEvent(AdjustEvent2dx event);
	static void setEnabled(bool isEnabled);
	static bool isEnabled();
	static void setOfflineMode(bool isOffline);
    static void appWillOpenUrl(std::string url);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    static void onResume();
    static void onPause();
	static void setReferrer(std::string referrer);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    static void setDeviceToken(std::string deviceToken);
#endif
};

#endif /* ADJUST_ADJUST2DX_H_ */
