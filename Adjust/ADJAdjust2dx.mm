//
//  ADJAdjust2dx.mm
//  AdjustSDK
//
//  Created by Uglješa Erceg on 17/06/15.
//
//

#include "ADJAdjust2dx.h"
#include <Adjust/Adjust.h>

const std::string ADJEnvironmentSandbox2dx = std::string([ADJEnvironmentSandbox UTF8String]);
const std::string ADJEnvironmentProduction2dx = std::string([ADJEnvironmentProduction UTF8String]);

void ADJAdjust2dx::appDidLaunch(ADJConfig2dx adjustConfig) {
    [Adjust appDidLaunch:(ADJConfig *)adjustConfig.getConfig()];
}

void ADJAdjust2dx::trackEvent(ADJEvent2dx adjustEvent) {
    [Adjust trackEvent:(ADJEvent *)adjustEvent.getEvent()];
}

void ADJAdjust2dx::trackSubsessionStart() {
    [Adjust trackSubsessionStart];
}

void ADJAdjust2dx::trackSubsessionEnd() {
    [Adjust trackSubsessionEnd];
}

void ADJAdjust2dx::setEnabled(bool isEnabled) {
    [Adjust setEnabled:isEnabled];
}

void ADJAdjust2dx::appWillOpenUrl(std::string url) {
    NSURL *pUrl = [NSURL URLWithString:[NSString stringWithUTF8String:url.c_str()]];
    [Adjust appWillOpenUrl:pUrl];
}

void ADJAdjust2dx::setDeviceToken(std::string deviceToken) {
    NSData *pDeviceToken = [[NSString stringWithUTF8String:deviceToken.c_str()]
                            dataUsingEncoding:NSUTF8StringEncoding];
    [Adjust setDeviceToken:pDeviceToken];
}

void ADJAdjust2dx::setOfflineMode(bool isOffline) {
    [Adjust setOfflineMode:isOffline];
}

bool ADJAdjust2dx::isEnabled() {
    return [Adjust isEnabled];
}