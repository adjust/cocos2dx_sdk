//
//  AdjustEventSuccess2dx.cpp
//  Adjust SDK
//
//  Created by Uglješa Erceg on 06/10/2016.
//
//

#include "AdjustEventSuccess2dx.h"

std::string AdjustEventSuccess2dx::getAdid() {
    return this->adid;
}

std::string AdjustEventSuccess2dx::getMessage() {
    return this->message;
}

std::string AdjustEventSuccess2dx::getTimestamp() {
    return this->timestamp;
}

std::string AdjustEventSuccess2dx::getEventToken() {
    return this->eventToken;
}

std::string AdjustEventSuccess2dx::getJsonResponse() {
    return this->jsonResponse;
}
