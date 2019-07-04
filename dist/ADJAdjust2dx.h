//
//  ADJAdjust2dx.h
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 17th June 2015.
//  Copyright © 2015-2019 Adjust GmbH. All rights reserved.
//

#ifndef _ADJUST_ADJUST2DX_H_
#define _ADJUST_ADJUST2DX_H_

#include <map>
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
    static void gdprForgetMe();
    static void addSessionCallbackParameter(std::string key, std::string value);
    static void addSessionPartnerParameter(std::string key, std::string value);
    static void removeSessionCallbackParameter(std::string key);
    static void removeSessionPartnerParameter(std::string key);
    static void resetSessionCallbackParameters();
    static void resetSessionPartnerParameters();
    static void trackAdRevenue(std::string source, std::string payload);
    static bool isEnabled();
    static std::string getIdfa();
    static std::string getAdid();
    static std::string getSdkVersion();
    static AdjustAttribution2dx getAttribution();
    // For testing purposes only.
    static void setTestOptions(std::map<std::string, std::string> testOptionsMap);
    static void teardown();
};

#endif /* _ADJUST_ADJUST2DX_H_ */
