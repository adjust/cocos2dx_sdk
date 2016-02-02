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

enum ADJLogLevel2dx {
    ADJLogLevel2dxVerbose = 1,
    ADJLogLevel2dxDebug   = 2,
    ADJLogLevel2dxInfo    = 3,
    ADJLogLevel2dxWarn    = 4,
    ADJLogLevel2dxError   = 5,
    ADJLogLevel2dxAssert  = 6 };

class ADJConfig2dx {
private:
    void* config;
    void (*callback)(AdjustAttribution2dx attribution);
    void initConfig(std::string appToken, std::string environment, std::string sdkPrefix);

public:
    ADJConfig2dx() {}
    ADJConfig2dx(std::string appToken, std::string environment, std::string sdkPrefix) {
        initConfig(appToken, environment, sdkPrefix);
    }

    void setLogLevel(ADJLogLevel2dx logLevel);
    void setDefaultTracker(std::string defaultTracker);
    void setEventBufferingEnabled(bool isEnabled);

    void setAttributionCallback(void (*callbackMethod)(AdjustAttribution2dx attribution));

    void* getConfig();
};

#endif /* _ADJUST_ADJUSTCONFIG2DX_H_ */
