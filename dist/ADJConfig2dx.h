//
//  ADJConfig2dx.h
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 17th June 2015.
//  Copyright © 2015-2019 Adjust GmbH. All rights reserved.
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
    ADJLogLevel2dxVerbose = 1,
    ADJLogLevel2dxDebug = 2,
    ADJLogLevel2dxInfo = 3,
    ADJLogLevel2dxWarn = 4,
    ADJLogLevel2dxError = 5,
    ADJLogLevel2dxAssert = 6,
    ADJLogLevel2dxSuppress = 7 };

class ADJConfig2dx {
private:
    void* config;
    void (*attributionCallback)(AdjustAttribution2dx attribution) = NULL;
    void (*eventSuccessCallback)(AdjustEventSuccess2dx eventSuccess) = NULL;
    void (*eventFailureCallback)(AdjustEventFailure2dx eventFailure) = NULL;
    void (*sessionSuccessCallback)(AdjustSessionSuccess2dx sessionSuccess) = NULL;
    void (*sessionFailureCallback)(AdjustSessionFailure2dx sessionFailure) = NULL;
    bool (*deferredDeeplinkCallback)(std::string deeplink) = NULL;
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
    void setUserAgent(std::string userAgent);
    void setDefaultTracker(std::string defaultTracker);
    void setAppSecret(long secretId, long info1, long info2, long info3, long info4);
    void setIsDeviceKnown(bool isDeviceKnown);
    void setAttributionCallback(void(*callbackMethod)(AdjustAttribution2dx attribution));
    void setEventSuccessCallback(void(*callbackMethod)(AdjustEventSuccess2dx eventSuccess));
    void setEventFailureCallback(void(*callbackMethod)(AdjustEventFailure2dx eventFailure));
    void setSessionSuccessCallback(void(*callbackMethod)(AdjustSessionSuccess2dx sessionSuccess));
    void setSessionFailureCallback(void(*callbackMethod)(AdjustSessionFailure2dx sessionFailure));
    void setDeferredDeeplinkCallback(bool(*callbackMethod)(std::string deeplink));
    void* getConfig();
    void(*getAttributionCallback())(AdjustAttribution2dx);
    void(*getEventSuccessCallback())(AdjustEventSuccess2dx);
    void(*getEventFailureCallback())(AdjustEventFailure2dx);
    void(*getSessionSuccessCallback())(AdjustSessionSuccess2dx);
    void(*getSessionFailureCallback())(AdjustSessionFailure2dx);
    bool(*getDeferredDeeplinkCallback())(std::string);
};

#endif /* _ADJUST_ADJUSTCONFIG2DX_H_ */
