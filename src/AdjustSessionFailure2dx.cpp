//
//  AdjustSessionFailure2dx.cpp
//  Adjust SDK
//
//  Created by Uglješa Erceg on 06/10/2016.
//
//

#include "AdjustSessionFailure2dx.h"

std::string AdjustSessionFailure2dx::getAdid() {
    return this->adid;
}

std::string AdjustSessionFailure2dx::getMessage() {
    return this->message;
}

std::string AdjustSessionFailure2dx::getTimestamp() {
    return this->timestamp;
}

std::string AdjustSessionFailure2dx::getWillRetry() {
    return this->willRetry;
}

std::string AdjustSessionFailure2dx::getJsonResponse() {
    return this->jsonResponse;
}
