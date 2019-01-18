//
//  ADJEvent2dx.h
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 17th June 2015.
//  Copyright © 2015-2019 Adjust GmbH. All rights reserved.
//

#ifndef _ADJUST_ADJUSTEVENT2DX_H_
#define _ADJUST_ADJUSTEVENT2DX_H_

#include <iostream>

class ADJEvent2dx {
private:
    void* event;
    void initEvent(std::string eventToken);

public:
    ADJEvent2dx() {}
    ADJEvent2dx(std::string eventToken) {
        initEvent(eventToken);
    }

    void setRevenue(double amount, std::string currency);
    void addCallbackParameter(std::string key, std::string value);
    void addPartnerParameter(std::string key, std::string value);
    void setTransactionId(std::string transactionId);
    void setCallbackId(std::string callbackId);
    void setReceipt(std::string receipt, std::string transactionId);
    bool isValid();
    void* getEvent();
};

#endif /* _ADJUST_ADJUSTEVENT2DX_H_ */
