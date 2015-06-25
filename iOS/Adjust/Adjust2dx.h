//
//  Adjust2dx.h
//  AdjustDemo
//
//  Created by Uglješa Erceg on 17/06/15.
//
//

#ifndef __AdjustDemo__Adjust2dx__
#define __AdjustDemo__Adjust2dx__

#include <iostream>

#include "ADJEvent2dx.h"
#include "ADJConfig2dx.h"

extern const std::string ADJEnvironmentSandbox2dx;
extern const std::string ADJEnvironmentProduction2dx;

class Adjust2dx {
public:
    static void appDidLaunch(ADJConfig2dx adjustConfig);
    static void trackEvent(ADJEvent2dx adjustEvent);
    static void trackSubsessionStart();
    static void trackSubsessionEnd();
    static void setEnabled(bool isEnabled);
    static void appWillOpenUrl(std::string url);
    static void setDeviceToken(std::string deviceToken);

    static bool isEnabled();
};

#endif /* defined(__AdjustDemo__Adjust2dx__) */
