//
//  ADJConfig2dx.h
//  AdjustDemo
//
//  Created by Uglješa Erceg on 17/06/15.
//
//

#ifndef __AdjustDemo__ADJConfig2dx__
#define __AdjustDemo__ADJConfig2dx__

#include <iostream>
#include "ADJAttribution2dx.h"

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
    void (*callback)(ADJAttribution2dx attribution);
    void initConfig(std::string appToken, std::string environment);

public:
    ADJConfig2dx() {}
    ADJConfig2dx(std::string appToken, std::string environment) {
        initConfig(appToken, environment);
    }

    std::string getAppToken();

    void setLogLevel(ADJLogLevel2dx logLevel);
    ADJLogLevel2dx getLogLevel();

    std::string getEnvironment();

    void setSdkPrefix(std::string sdkPrefix);
    std::string getSdkPrefix();

    void setDefaultTracker(std::string defaultTracker);
    std::string getDefaultTracker();

    void setEventBufferingEnabled(bool isEnabled);
    bool getEventBufferingEnabled();

    void setMacMd5TrackingEnabled(bool isEnabled);
    bool getMacMd5TrackingEnabled();

    void setAttributionCallback(void (*callbackMethod)(ADJAttribution2dx attribution));

    void* getConfig();
};

#endif /* defined(__AdjustDemo__ADJConfig2dx__) */
