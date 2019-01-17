//
//  AdjustSessionSuccess2dx.cpp
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 6th October 2016.
//  Copyright © 2016-2019 Adjust GmbH. All rights reserved.
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
