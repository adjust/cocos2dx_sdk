//
//  AdjustConfig2dx.h
//  Adjust SDK
//
//  Created by Uglješa Erceg on 16/06/15.
//

#ifndef ADJUST_ADJUSTCONFIG2DX_H_
#define ADJUST_ADJUSTCONFIG2DX_H_

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "ADJConfig2dx.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
using namespace AdjustWinRT;
#endif

#include <iostream>
#include "AdjustAttribution2dx.h"

enum AdjustLogLevel2dx {
    AdjustLogLevel2dxVerbose = 1,
    AdjustLogLevel2dxDebug   = 2,
    AdjustLogLevel2dxInfo    = 3,
    AdjustLogLevel2dxWarn    = 4,
    AdjustLogLevel2dxError   = 5,
    AdjustLogLevel2dxAssert  = 6 };

class AdjustConfig2dx {
private:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    jobject config;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    bool isConfigSet;
    ADJConfig2dx config;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    bool isConfigSet;
    WRTAdjustConfig^ config;
#endif
    void initConfig(std::string appToken, std::string environment);

public:
    AdjustConfig2dx() {}
    AdjustConfig2dx(std::string appToken, std::string environment) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        initConfig(appToken, environment);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        isConfigSet = false;
        initConfig(appToken, environment);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
        isConfigSet = false;
        initConfig(appToken, environment);
#endif
    }

    void setLogLevel(AdjustLogLevel2dx logLevel, void(*logCallback)(const char* log) = NULL);
    void setEventBufferingEnabled(bool isEnabled);
    void setDefaultTracker(std::string defaultTracker);
    void setAttributionCallback(void (*attributionCallback)(AdjustAttribution2dx attribution));

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    jobject getConfig();
    void setProcessName(std::string processName);
};
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJConfig2dx getConfig();
};
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    typedef void(*AttributionCallback)(AdjustAttribution2dx attribution);

    WRTAdjustConfig^ getConfig();
    static AttributionCallback attributionCallbackSaved;
    static void triggerSavedAttributionCallback(AdjustAttribution2dx attribution);
};
#endif

#endif /* ADJUST_ADJUSTCONFIG2DX_H_ */
