//
//  ADJAppStorePurchase2dx.mm
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 17th January 2024.
//  Copyright © 2015-Present Adjust GmbH. All rights reserved.
//

#include "ADJAppStorePurchase2dx.h"
#include <AdjustSdk/ADJPurchase.h>

void ADJAppStorePurchase2dx::initPurchase(std::string productId, std::string transactionId, std::string receipt) {
    NSString *strProductId = [NSString stringWithUTF8String:productId.c_str()];
    NSString *strTransactionId = [NSString stringWithUTF8String:transactionId.c_str()];
    NSString *strReceipt = [NSString stringWithUTF8String:receipt.c_str()];
    purchase = [[ADJPurchase alloc] initWithTransactionId:strTransactionId
                                                productId:strProductId
                                               andReceipt:[strReceipt dataUsingEncoding:NSUTF8StringEncoding]];
}

void* ADJAppStorePurchase2dx::getPurchase() {
    return purchase;
}
