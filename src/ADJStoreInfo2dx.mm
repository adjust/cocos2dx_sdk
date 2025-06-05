//
//  ADJStoreInfo2dx.mm
//  Adjust SDK
//
//  Created by Ugljesa Erceg (@uerceg) on 5th June 2024.
//  Copyright © 2025-Present Adjust GmbH. All rights reserved.
//

#include "ADJStoreInfo2dx.h"
#include <AdjustSdk/ADJStoreInfo.h>

void ADJStoreInfo2dx::initStoreInfo(std::string storeName) {
    storeInfo = [[ADJStoreInfo alloc] initWithStoreName:[NSString stringWithUTF8String:storeName.c_str()]];
}

void ADJStoreInfo2dx::setStoreAppId(std::string storeAppId) {
    [((ADJStoreInfo *)storeInfo) setStoreAppId:[NSString stringWithUTF8String:storeAppId.c_str()]];
}

void* ADJStoreInfo2dx::getStoreInfo() {
    return storeInfo;
}
