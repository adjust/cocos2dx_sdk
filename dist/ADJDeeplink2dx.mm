//
//  ADJDeeplink2dx.mm
//  Adjust SDK
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
