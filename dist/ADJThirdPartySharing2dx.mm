//
//  ADJThirdPartySharing2dx.mm
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 10th September 2015.
//  Copyright © 2021 Adjust GmbH. All rights reserved.
//

#include "ADJThirdPartySharing2dx.h"
#include <AdjustSdk/ADJThirdPartySharing.h>

void ADJThirdPartySharing2dx::initThirdPartySharing() {
    thirdPartySharing = [[ADJThirdPartySharing alloc] initWithIsEnabled:nil];
}

void ADJThirdPartySharing2dx::initThirdPartySharing(bool isEnabled) {
    thirdPartySharing = [[ADJThirdPartySharing alloc] initWithIsEnabled:[NSNumber numberWithBool:isEnabled]];
}

void ADJThirdPartySharing2dx::addGranularOption(std::string partnerName, std::string key, std::string value) {
    [((ADJThirdPartySharing *)thirdPartySharing) addGranularOption:[NSString stringWithUTF8String:partnerName.c_str()]
                                                               key:[NSString stringWithUTF8String:key.c_str()]
                                                             value:[NSString stringWithUTF8String:value.c_str()]];
}

void ADJThirdPartySharing2dx::addPartnerSharingSetting(std::string partnerName, std::string key, bool value) {
    [((ADJThirdPartySharing *)thirdPartySharing) addPartnerSharingSetting:[NSString stringWithUTF8String:partnerName.c_str()]
                                                                      key:[NSString stringWithUTF8String:key.c_str()]
                                                                    value:value];
}

void* ADJThirdPartySharing2dx::getThirdPartySharing() {
    return thirdPartySharing;
}
