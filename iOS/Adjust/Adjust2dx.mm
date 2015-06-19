//
//  Adjust2dx.mm
//  AdjustDemo
//
//  Created by Uglješa Erceg on 17/06/15.
//
//

#include "Adjust2dx.h"
#include <Adjust/Adjust.h>

const std::string ADJEnvironmentSandbox2dx = std::string([ADJEnvironmentSandbox UTF8String]);
const std::string ADJEnvironmentProduction2dx = std::string([ADJEnvironmentProduction UTF8String]);

void Adjust2dx::appDidLaunch(ADJConfig2dx adjustConfig) {
    [Adjust appDidLaunch:(ADJConfig *)adjustConfig.getConfig()];
}

void Adjust2dx::trackEvent(ADJEvent2dx adjustEvent) {
    [Adjust trackEvent:(ADJEvent *)adjustEvent.getEvent()];
}

void Adjust2dx::trackSubsessionStart() {
    [Adjust trackSubsessionStart];
}

void Adjust2dx::trackSubsessionEnd() {
    [Adjust trackSubsessionEnd];
}

void Adjust2dx::setEnabled(bool isEnabled) {
    [Adjust setEnabled:isEnabled];
}

void Adjust2dx::appWillOpenUrl(std::string url) {
    NSURL *pUrl = [NSURL URLWithString:[NSString stringWithUTF8String:url.c_str()]];
    [Adjust appWillOpenUrl:pUrl];
}

void Adjust2dx::setDeviceToken(std::string deviceToken) {
    NSData *pDeviceToken = [[NSString stringWithUTF8String:deviceToken.c_str()]
                            dataUsingEncoding:NSUTF8StringEncoding];
    [Adjust setDeviceToken:pDeviceToken];
}

bool Adjust2dx::isEnabled() {
    return [Adjust isEnabled];
}