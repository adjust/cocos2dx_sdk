//
//  ADJEvent2dx.h
//  AdjustDemo
//
//  Created by Uglješa Erceg on 17/06/15.
//
//

#ifndef __AdjustDemo__ADJEvent2dx__
#define __AdjustDemo__ADJEvent2dx__

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

#endif /* defined(__AdjustDemo__ADJEvent2dx__) */
