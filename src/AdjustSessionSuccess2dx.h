//
//  AdjustSessionSuccess2dx.h
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 6th October 2016.
//  Copyright © 2016-2019 Adjust GmbH. All rights reserved.
//

#ifndef ADJUST_ADJUSTSESSIONSUCCESS2DX_H_
#define ADJUST_ADJUSTSESSIONSUCCESS2DX_H_

#include <iostream>

class AdjustSessionSuccess2dx {
private:
    std::string adid;
    std::string message;
    std::string timestamp;
    std::string jsonResponse;
public:
    AdjustSessionSuccess2dx() {}
    AdjustSessionSuccess2dx(
        std::string adid,
        std::string message,
        std::string timestamp,
        std::string jsonResponse) {
        this->adid = adid;
        this->message = message;
        this->timestamp = timestamp;
        this->jsonResponse = jsonResponse;
    }

    std::string getAdid();
    std::string getMessage();
    std::string getTimestamp();
    std::string getJsonResponse();
};

#endif /* ADJUST_ADJUSTSESSIONSUCCESS2DX_H_ */
