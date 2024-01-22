//
//  ADJAppStorePurchase2dx.h
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 17th January 2024.
//  Copyright © 2015-Present Adjust GmbH. All rights reserved.
//

#ifndef _ADJUST_ADJAPPSTOREPURCHASE2DX_H_
#define _ADJUST_ADJAPPSTOREPURCHASE2DX_H_

#include <iostream>

class ADJAppStorePurchase2dx {
private:
    void* purchase;
    void initPurchase(std::string productId, std::string transactionId, std::string receipt);

public:
    ADJAppStorePurchase2dx() {}
    ADJAppStorePurchase2dx(std::string productId, std::string transactionId, std::string receipt) {
        initPurchase(productId, transactionId, receipt);
    }

    void* getPurchase();
};

#endif /* _ADJUST_ADJAPPSTOREPURCHASE2DX_H_ */
