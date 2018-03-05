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
#include "AdjustAttribution2dx.h"

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
    static void setDeviceToken(std::string deviceToken);
    
    static void sendFirstPackages();
    static void addSessionCallbackParameter(std::string key, std::string value);
    static void addSessionPartnerParameter(std::string key, std::string value);
    static void removeSessionCallbackParameter(std::string key);
    static void removeSessionPartnerParameter(std::string key);
    static void resetSessionCallbackParameters();
    static void resetSessionPartnerParameters();

    static std::string getAdid();
    static AdjustAttribution2dx getAttribution();
    
    // Android-specific
    static void setReferrer(std::string referrer);
    static void getGoogleAdId(void (*adIdCallback)(std::string adId));
    static std::string getAmazonAdId();
    static void onResume();
    static void onPause();
    
    // iOS-specific
    static std::string getIdfa();
    
    // Windows-specific
    static std::string getWindowsAdId();
    static void applicationPaused();
    static void applicationResumed();
};

#endif /* ADJUST_ADJUST2DX_H_ */
