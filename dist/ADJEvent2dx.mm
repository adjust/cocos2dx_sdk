//
//  ADJEvent2dx.mm
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 17th June 2015.
//  Copyright © 2015-2019 Adjust GmbH. All rights reserved.
//

#include "ADJEvent2dx.h"
#include <AdjustSdk/ADJEvent.h>

void ADJEvent2dx::initEvent(std::string eventToken) {
    event = [[ADJEvent alloc] initWithEventToken:
             [NSString stringWithUTF8String:eventToken.c_str()]];
}

void ADJEvent2dx::setRevenue(double amount, std::string currency) {
    [((ADJEvent *)event) setRevenue:amount
                           currency:[NSString stringWithUTF8String:currency.c_str()]];
}

void ADJEvent2dx::addCallbackParameter(std::string key, std::string value) {
    [((ADJEvent *)event) addCallbackParameter:[NSString stringWithUTF8String:key.c_str()]
                                        value:[NSString stringWithUTF8String:value.c_str()]];
}

void ADJEvent2dx::addPartnerParameter(std::string key, std::string value) {
    [((ADJEvent *)event) addPartnerParameter:[NSString stringWithUTF8String:key.c_str()]
                                       value:[NSString stringWithUTF8String:value.c_str()]];
}

void ADJEvent2dx::setTransactionId(std::string transactionId) {
    [((ADJEvent *)event) setTransactionId:[NSString stringWithUTF8String:transactionId.c_str()]];
}

void ADJEvent2dx::setCallbackId(std::string callbackId) {
    [((ADJEvent *)event) setCallbackId:[NSString stringWithUTF8String:callbackId.c_str()]];
}

void ADJEvent2dx::setReceipt(std::string receipt, std::string transactionId) {
    [((ADJEvent *)event) setReceipt:
     [[NSString stringWithUTF8String:receipt.c_str()] dataUsingEncoding:NSUTF8StringEncoding]
                       transactionId:[NSString stringWithUTF8String:transactionId.c_str()]];
}

bool ADJEvent2dx::isValid() {
    return [((ADJEvent *)event) isValid];
}

void* ADJEvent2dx::getEvent() {
    return event;
}
