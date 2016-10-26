//
//  ADJConfig2dx.h
//  AdjustSDK
//
//  Created by Uglješa Erceg on 17/06/15.
//
//

#ifndef _ADJUST_ADJUSTCONFIG2DX_H_
#define _ADJUST_ADJUSTCONFIG2DX_H_

#include <iostream>

#include "AdjustAttribution2dx.h"
#include "AdjustEventFailure2dx.h"
#include "AdjustEventSuccess2dx.h"
#include "AdjustSessionSuccess2dx.h"
#include "AdjustSessionFailure2dx.h"

enum ADJLogLevel2dx {
    ADJLogLevel2dxVerbose   = 1,
    ADJLogLevel2dxDebug     = 2,
    ADJLogLevel2dxInfo      = 3,
    ADJLogLevel2dxWarn      = 4,
    ADJLogLevel2dxError     = 5,
    ADJLogLevel2dxAssert    = 6,
    ADJLogLevel2dxSuppress  = 7 };

class ADJConfig2dx {
private:
    void* config;

    void (*attributionCallback)(AdjustAttribution2dx attribution);
    void (*eventSuccessCallback)(AdjustEventSuccess2dx eventSuccess);
    void (*eventFailureCallback)(AdjustEventFailure2dx eventFailure);
    void (*sessionSuccessCallback)(AdjustSessionSuccess2dx sessionSuccess);
    void (*sessionFailureCallback)(AdjustSessionFailure2dx sessionFailure);
    void (*deferredDeeplinkCallback)(std::string deeplink);

    void initConfig(std::string appToken, std::string environment, bool allowSuppressLogLevel, std::string sdkPrefix);

public:
    ADJConfig2dx() {}
    
    ADJConfig2dx(std::string appToken, std::string environment, std::string sdkPrefix) {
        initConfig(appToken, environment, false, sdkPrefix);
    }
    
    ADJConfig2dx(std::string appToken, std::string environment, bool allowSuppressLogLevel, std::string sdkPrefix) {
        initConfig(appToken, environment, allowSuppressLogLevel, sdkPrefix);
    }

    void setDelayStart(double delayStart);
    void setLogLevel(ADJLogLevel2dx logLevel);

    void setSendInBackground(bool isEnabled);
    void setEventBufferingEnabled(bool isEnabled);
    void setLaunchDeferredDeeplink(bool shouldLaunch);

    void setUserAgent(std::string userAgent);
    void setDefaultTracker(std::string defaultTracker);

    void setAttributionCallback(void(*callbackMethod)(AdjustAttribution2dx attribution));
    void setEventSuccessCallback(void(*callbackMethod)(AdjustEventSuccess2dx eventSuccess));
    void setEventFailureCallback(void(*callbackMethod)(AdjustEventFailure2dx eventFailure));
    void setSessionSuccessCallback(void(*callbackMethod)(AdjustSessionSuccess2dx sessionSuccess));
    void setSessionFailureCallback(void(*callbackMethod)(AdjustSessionFailure2dx sessionFailure));
    void setDeferredDeeplinkCallback(void(*callbackMethod)(std::string deeplink));

    void* getConfig();
};

#endif /* _ADJUST_ADJUSTCONFIG2DX_H_ */
