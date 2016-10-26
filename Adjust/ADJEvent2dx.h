//
//  ADJEvent2dx.h
//  AdjustSDK
//
//  Created by Uglješa Erceg on 17/06/15.
//
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

    void setTransactionId(std::string transactionId);
    void setRevenue(double amount, std::string currency);
    void addCallbackParameter(std::string key, std::string value);
    void addPartnerParameter(std::string key, std::string value);
    void setReceipt(std::string receipt, std::string transactionId);

    bool isValid();

    void* getEvent();
};

#endif /* _ADJUST_ADJUSTEVENT2DX_H_ */
