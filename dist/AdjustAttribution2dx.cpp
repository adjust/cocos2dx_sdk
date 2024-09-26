//
//  AdjustAttribution2dx.cpp
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 16th June 2015.
//  Copyright © 2015-Present Adjust GmbH. All rights reserved.
//

#include "AdjustAttribution2dx.h"

std::string AdjustAttribution2dx::getTrackerToken() {
    return this->trackerToken;
}

std::string AdjustAttribution2dx::getTrackerName() {
    return this->trackerName;
}

std::string AdjustAttribution2dx::getNetwork() {
    return this->network;
}

std::string AdjustAttribution2dx::getCampaign() {
    return this->campaign;
}

std::string AdjustAttribution2dx::getAdgroup() {
    return this->adgroup;
}

std::string AdjustAttribution2dx::getCreative() {
    return this->creative;
}

std::string AdjustAttribution2dx::getClickLabel() {
    return this->clickLabel;
}

std::string AdjustAttribution2dx::getCostType() {
    return this->costType;
}

double AdjustAttribution2dx::getCostAmount() {
    return this->costAmount;
}

std::string AdjustAttribution2dx::getCostCurrency() {
    return this->costCurrency;
}

std::string AdjustAttribution2dx::getFbInstallReferrer() {
    return this->fbInstallReferrer;
}
