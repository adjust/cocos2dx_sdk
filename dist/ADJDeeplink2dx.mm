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
    deeplink = [[ADJDeeplink alloc] initWithDeeplink:
             [NSURL URLWithString:[NSString stringWithUTF8String:deeplinkStr.c_str()]]];
}

void* ADJDeeplink2dx::getDeeplink() {
    return deeplink;
}
