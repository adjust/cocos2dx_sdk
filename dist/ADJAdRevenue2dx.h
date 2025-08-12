//
//  ADJAdRevenue2dx.h
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 14th October 2022.
//  Copyright © 2022-Present Adjust GmbH. All rights reserved.
//

#ifndef _ADJUST_ADJADREVENUE2DX_H_
#define _ADJUST_ADJADREVENUE2DX_H_

#include <iostream>

class ADJAdRevenue2dx {
private:
    void* adRevenue;
    void initAdRevenue(std::string source);

public:
    ADJAdRevenue2dx() {}
    ADJAdRevenue2dx(std::string source) {
        initAdRevenue(source);
    }

    void setRevenue(double amount, std::string currency);
    void setAdImpressionsCount(int adImpressionsCount);
    void setAdRevenueNetwork(std::string adRevenueNetwork);
    void setAdRevenueUnit(std::string adRevenueUnit);
    void setAdRevenuePlacement(std::string adRevenuePlacement);
    void addCallbackParameter(std::string key, std::string value);
    void addPartnerParameter(std::string key, std::string value);
    void* getAdRevenue();
};

#endif /* _ADJUST_ADJADREVENUE2DX_H_ */
