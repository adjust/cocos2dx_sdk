//
//  AdjustAttribution2dx.h
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 16th June 2015.
//  Copyright © 2015-2019 Adjust GmbH. All rights reserved.
//

#ifndef ADJUST_ADJUSTATTRIBUTION2DX_H_
#define ADJUST_ADJUSTATTRIBUTION2DX_H_

#include <iostream>

class AdjustAttribution2dx {
private:
    std::string trackerToken;
    std::string trackerName;
    std::string network;
    std::string campaign;
    std::string adgroup;
    std::string creative;
    std::string clickLabel;
    std::string adid;
public:
    AdjustAttribution2dx() {}
    AdjustAttribution2dx(
        std::string trackerToken,
        std::string trackerName,
        std::string network,
        std::string campaign,
        std::string adgroup,
        std::string creative,
        std::string clickLabel,
        std::string adid) {
        this->trackerToken = trackerToken;
        this->trackerName = trackerName;
        this->network = network;
        this->campaign = campaign;
        this->adgroup = adgroup;
        this->creative = creative;
        this->clickLabel = clickLabel;
        this->adid = adid;
    }

    std::string getTrackerToken();
    std::string getTrackerName();
    std::string getNetwork();
    std::string getCampaign();
    std::string getAdgroup();
    std::string getCreative();
    std::string getClickLabel();
    std::string getAdid();
};

#endif /* ADJUST_ADJUSTATTRIBUTION2DX_H_ */
