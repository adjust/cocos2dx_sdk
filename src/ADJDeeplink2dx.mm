//
//  ADJDeeplink2dx.mm
//  Adjust SDK
//
//  Created by Pedro Silva (@nonelse) on 30th August 2024.
//  Copyright © 2024-Present Adjust GmbH. All rights reserved.
//

#include "ADJDeeplink2dx.h"
#include <AdjustSdk/ADJDeeplink.h>

void ADJDeeplink2dx::initDeeplink(std::string deeplinkStr) {
    NSURL *deeplinkUrl = [NSURL URLWithString:[NSString stringWithUTF8String:deeplinkStr.c_str()]];
    deeplink = [[ADJDeeplink alloc] initWithDeeplink:deeplinkUrl];
}

void ADJDeeplink2dx::setReferrer(std::string referrer) {
    NSURL *referrerUrl = [NSURL URLWithString:[NSString stringWithUTF8String:referrer.c_str()]];
    [((ADJDeeplink *)deeplink) setReferrer:referrerUrl];
}

void* ADJDeeplink2dx::getDeeplink() {
    return deeplink;
}
