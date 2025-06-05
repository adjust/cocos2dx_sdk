//
//  ADJStoreInfo2dx.h
//  Adjust SDK
//
//  Created by Ugljesa Erceg (@uerceg) on 5th June 2025.
//  Copyright © 2025-Present Adjust GmbH. All rights reserved.
//

#ifndef _ADJUST_ADJSTOREINFO2DX_H_
#define _ADJUST_ADJSTOREINFO2DX_H_

#include <iostream>

class ADJStoreInfo2dx {
private:
    void* storeInfo;
    void initStoreInfo(std::string storeName);

public:
    ADJStoreInfo2dx() {}
    ADJStoreInfo2dx(std::string storeInfo) {
        initStoreInfo(storeInfo);
    }

    void setStoreAppId(std::string storeAppId);

    void* getStoreInfo();
};

#endif /* _ADJUST_ADJSTOREINFO2DX_H_ */
