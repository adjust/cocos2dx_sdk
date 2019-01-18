//
//  AdjustEventFailure2dx.cpp
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 6th October 2016.
//  Copyright © 2016-2019 Adjust GmbH. All rights reserved.
//

#include "AdjustEventFailure2dx.h"

std::string AdjustEventFailure2dx::getAdid() {
    return this->adid;
}

std::string AdjustEventFailure2dx::getMessage() {
    return this->message;
}

std::string AdjustEventFailure2dx::getTimestamp() {
    return this->timestamp;
}

std::string AdjustEventFailure2dx::getWillRetry() {
    return this->willRetry;
}

std::string AdjustEventFailure2dx::getEventToken() {
    return this->eventToken;
}

std::string AdjustEventFailure2dx::getCallbackId() {
    return this->callbackId;
}

std::string AdjustEventFailure2dx::getJsonResponse() {
    return this->jsonResponse;
}
