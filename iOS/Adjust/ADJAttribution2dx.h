//
//  ADJAttribution2dx.h
//  AdjustDemo
//
//  Created by Uglješa Erceg on 17/06/15.
//
//

#ifndef __AdjustDemo__ADJAttribution2dx__
#define __AdjustDemo__ADJAttribution2dx__

#include <iostream>

class ADJAttribution2dx {
private:
    std::string trackerToken;
    std::string trackerName;
    std::string network;
    std::string campaign;
    std::string adgroup;
    std::string creative;
    std::string clickLabel;
public:
    ADJAttribution2dx() {}
    ADJAttribution2dx(std::string trackerToken, std::string trackerName, std::string network,
                      std::string campaign, std::string adgroup, std::string creative,
                      std::string clickLabel) {
        this->trackerToken = trackerToken;
        this->trackerName = trackerName;
        this->network = network;
        this->campaign = campaign;
        this->adgroup = adgroup;
        this->creative = creative;
        this->clickLabel = clickLabel;
    }

    std::string getTrackerToken();
    std::string getTrackerName();
    std::string getNetwork();
    std::string getCampaign();
    std::string getAdgroup();
    std::string getCreative();
    std::string getClickLabel();
};

#endif /* defined(__AdjustDemo__ADJAttribution2dx__) */
