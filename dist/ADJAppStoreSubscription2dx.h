//
//  ADJAppStoreSubscription2dx.h
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 12th June 2020.
//  Copyright © 2020-Present Adjust GmbH. All rights reserved.
//

#ifndef _ADJUST_ADJAPPSTORESUBSCRIPTION2DX_H_
#define _ADJUST_ADJAPPSTORESUBSCRIPTION2DX_H_

#include <iostream>

class ADJAppStoreSubscription2dx {
private:
    void* subscription;
    void initSubscription(std::string price, std::string currency, std::string transactionId);

public:
    ADJAppStoreSubscription2dx() {}
    ADJAppStoreSubscription2dx(std::string price, std::string currency, std::string transactionId) {
        initSubscription(price, currency, transactionId);
    }

    void setTransactionDate(std::string transactionDate);
    void setSalesRegion(std::string salesRegion);
    void addCallbackParameter(std::string key, std::string value);
    void addPartnerParameter(std::string key, std::string value);
    void* getSubscription();
};

#endif /* _ADJUST_ADJAPPSTORESUBSCRIPTION2DX_H_ */
