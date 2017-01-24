//
//  ADJAdjust2dx.h
//  AdjustSDK
//
//  Created by Uglješa Erceg on 17/06/15.
//
//

#ifndef _ADJUST_ADJUST2DX_H_
#define _ADJUST_ADJUST2DX_H_

#include <iostream>

#include "ADJEvent2dx.h"
#include "ADJConfig2dx.h"
#include "AdjustAttribution2dx.h"

extern const std::string ADJEnvironmentSandbox2dx;
extern const std::string ADJEnvironmentProduction2dx;

class ADJAdjust2dx {
public:
    static void appDidLaunch(ADJConfig2dx adjustConfig);
    static void trackEvent(ADJEvent2dx adjustEvent);
    static void trackSubsessionStart();
    static void trackSubsessionEnd();
    static void setEnabled(bool isEnabled);
    static void appWillOpenUrl(std::string url);
    static void setDeviceToken(std::string deviceToken);
    static void setOfflineMode(bool isOffline);
    
    static void sendFirstPackages();
    static void addSessionCallbackParameter(std::string key, std::string value);
    static void addSessionPartnerParameter(std::string key, std::string value);
    static void removeSessionCallbackParameter(std::string key);
    static void removeSessionPartnerParameter(std::string key);
    static void resetSessionCallbackParameters();
    static void resetSessionPartnerParameters();
    
    static bool isEnabled();
    static std::string getIdfa();
    static std::string getAdid();
    static AdjustAttribution2dx getAttribution();
};

#endif /* _ADJUST_ADJUST2DX_H_ */
