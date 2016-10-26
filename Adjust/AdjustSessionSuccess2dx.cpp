//
//  AdjustSessionSuccess2dx.cpp
//  Adjust SDK
//
//  Created by Uglješa Erceg on 06/10/2016.
//
//

#include "AdjustSessionSuccess2dx.h"

std::string AdjustSessionSuccess2dx::getAdid() {
    return this->adid;
}

std::string AdjustSessionSuccess2dx::getMessage() {
    return this->message;
}

std::string AdjustSessionSuccess2dx::getTimestamp() {
    return this->timestamp;
}

std::string AdjustSessionSuccess2dx::getJsonResponse() {
    return this->jsonResponse;
}
