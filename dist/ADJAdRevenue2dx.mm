//
//  ADJAdRevenue2dx.mm
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 14th October 2022.
//  Copyright © 2022-Present Adjust GmbH. All rights reserved.
//

#include "ADJAdRevenue2dx.h"
#include <AdjustSdk/ADJAdRevenue.h>

void ADJAdRevenue2dx::initAdRevenue(std::string source) {
    adRevenue = [[ADJAdRevenue alloc] initWithSource:[NSString stringWithUTF8String:source.c_str()]];
}

void ADJAdRevenue2dx::setRevenue(double amount, std::string currency) {
    [((ADJAdRevenue *)adRevenue) setRevenue:amount
                                   currency:[NSString stringWithUTF8String:currency.c_str()]];
}

void ADJAdRevenue2dx::setAdImpressionsCount(int adImpressionsCount) {
    [((ADJAdRevenue *)adRevenue) setAdImpressionsCount:adImpressionsCount];
}

void ADJAdRevenue2dx::setAdRevenueNetwork(std::string adRevenueNetwork) {
    [((ADJAdRevenue *)adRevenue) setAdRevenueNetwork:[NSString stringWithUTF8String:adRevenueNetwork.c_str()]];
}

void ADJAdRevenue2dx::setAdRevenueUnit(std::string adRevenueUnit) {
    [((ADJAdRevenue *)adRevenue) setAdRevenueUnit:[NSString stringWithUTF8String:adRevenueUnit.c_str()]];
}

void ADJAdRevenue2dx::setAdRevenuePlacement(std::string adRevenuePlacement) {
    [((ADJAdRevenue *)adRevenue) setAdRevenuePlacement:[NSString stringWithUTF8String:adRevenuePlacement.c_str()]];
}

void ADJAdRevenue2dx::addCallbackParameter(std::string key, std::string value) {
    [((ADJAdRevenue *)adRevenue) addCallbackParameter:[NSString stringWithUTF8String:key.c_str()]
                                                value:[NSString stringWithUTF8String:value.c_str()]];
}

void ADJAdRevenue2dx::addPartnerParameter(std::string key, std::string value) {
    [((ADJAdRevenue *)adRevenue) addPartnerParameter:[NSString stringWithUTF8String:key.c_str()]
                                               value:[NSString stringWithUTF8String:value.c_str()]];
}

void* ADJAdRevenue2dx::getAdRevenue() {
    return adRevenue;
}
