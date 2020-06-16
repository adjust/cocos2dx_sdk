//
//  ADJAppStoreSubscription2dx.mm
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 12th June 2020.
//  Copyright © 2015-2020 Adjust GmbH. All rights reserved.
//

#include "ADJAppStoreSubscription2dx.h"
#include <AdjustSdk/ADJSubscription.h>

void ADJAppStoreSubscription2dx::initSubscription(std::string price, std::string currency, std::string transactionId, std::string receipt) {
    NSString *strPrice = [NSString stringWithUTF8String:price.c_str()];
    NSString *strCurrency = [NSString stringWithUTF8String:currency.c_str()];
    NSString *strTransactionId = [NSString stringWithUTF8String:transactionId.c_str()];
    NSString *strReceipt = [NSString stringWithUTF8String:receipt.c_str()];
    subscription = [[ADJSubscription alloc] initWithPrice:[NSDecimalNumber decimalNumberWithString:strPrice]
                                                 currency:strCurrency
                                            transactionId:strTransactionId
                                               andReceipt:[strReceipt dataUsingEncoding:NSUTF8StringEncoding]];
}

void ADJAppStoreSubscription2dx::setTransactionDate(std::string transactionDate) {
    NSString *strTransactionDate = [NSString stringWithUTF8String:transactionDate.c_str()];
    [((ADJSubscription *)subscription) setTransactionDate:[NSDate dateWithTimeIntervalSince1970:[strTransactionDate doubleValue]]];
}

void ADJAppStoreSubscription2dx::setSalesRegion(std::string salesRegion) {
    NSString *strSalesRegion = [NSString stringWithUTF8String:salesRegion.c_str()];
    [((ADJSubscription *)subscription) setSalesRegion:strSalesRegion];
}

void ADJAppStoreSubscription2dx::addCallbackParameter(std::string key, std::string value) {
    [((ADJSubscription *)subscription) addCallbackParameter:[NSString stringWithUTF8String:key.c_str()]
                                                      value:[NSString stringWithUTF8String:value.c_str()]];
}

void ADJAppStoreSubscription2dx::addPartnerParameter(std::string key, std::string value) {
    [((ADJSubscription *)subscription) addPartnerParameter:[NSString stringWithUTF8String:key.c_str()]
                                                     value:[NSString stringWithUTF8String:value.c_str()]];
}

void* ADJAppStoreSubscription2dx::getSubscription() {
    return subscription;
}
