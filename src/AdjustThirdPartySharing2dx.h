//
//  AdjustThirdPartySharing2dx.h
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 10th September 2021.
//  Copyright © 2021-Present Adjust GmbH. All rights reserved.
//

#ifndef ADJUST_ADJUSTTHIRDPARTYSHARING_H_
#define ADJUST_ADJUSTTHIRDPARTYSHARING_H_

#include "cocos2d.h"
#include <iostream>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "ADJThirdPartySharing2dx.h"
#endif

class AdjustThirdPartySharing2dx {
private:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    jobject thirdPartySharing;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    bool isThirdPartySharingSet;
    ADJThirdPartySharing2dx thirdPartySharing;
#endif
    void initThirdPartySharing();
    void initThirdPartySharing(bool isEnabled);

public:
    AdjustThirdPartySharing2dx() {
        initThirdPartySharing();
    }

    AdjustThirdPartySharing2dx(bool isEnabled) {
        initThirdPartySharing(isEnabled);
    }

    void addGranularOption(std::string partnerName, std::string key, std::string value);
    void addPartnerSharingSetting(std::string partnerName, std::string key, bool value);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    jobject getThirdPartySharing();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ADJThirdPartySharing2dx getThirdPartySharing();
#endif
};

#endif /* ADJUST_ADJUSTTHIRDPARTYSHARING_H_ */
