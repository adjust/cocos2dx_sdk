//
//  AdjustEventSuccess2dx.h
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 6th October 2016.
//  Copyright © 2016-2019 Adjust GmbH. All rights reserved.
//

#ifndef ADJUST_ADJUSTEVENTSUCCESS2DX_H_
#define ADJUST_ADJUSTEVENTSUCCESS2DX_H_

#include <iostream>

class AdjustEventSuccess2dx {
private:
    std::string adid;
    std::string message;
    std::string timestamp;
    std::string eventToken;
    std::string callbackId;
    std::string jsonResponse;
public:
    AdjustEventSuccess2dx() {}
    AdjustEventSuccess2dx(
        std::string adid,
        std::string message,
        std::string timestamp,
        std::string eventToken,
        std::string callbackId,
        std::string jsonResponse) {
        this->adid = adid;
        this->message = message;
        this->timestamp = timestamp;
        this->eventToken = eventToken;
        this->callbackId = callbackId;
        this->jsonResponse = jsonResponse;
    }

    std::string getAdid();
    std::string getMessage();
    std::string getTimestamp();
    std::string getEventToken();
    std::string getCallbackId();
    std::string getJsonResponse();
};

#endif /* ADJUST_ADJUSTEVENTSUCCESS2DX_H_ */
