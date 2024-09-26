//
//  AdjustPurchaseVerificationResult2dx.cpp
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 25th September 2024.
//  Copyright © 2024-Present Adjust GmbH. All rights reserved.
//

#include "AdjustPurchaseVerificationResult2dx.h"

std::string AdjustPurchaseVerificationResult2dx::getVerificationStatus() {
    return this->verificationStatus;
}

std::string AdjustPurchaseVerificationResult2dx::getMessage() {
    return this->message;
}

int AdjustPurchaseVerificationResult2dx::getCode() {
    return this->code;
}
