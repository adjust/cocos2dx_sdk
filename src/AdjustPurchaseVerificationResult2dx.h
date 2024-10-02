//
//  AdjustPurchaseVerificationResult2dx.h
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 25th September 2024.
//  Copyright © 2024-Present Adjust GmbH. All rights reserved.
//

#ifndef ADJUST_ADJUSTPURCHASEVERIFICATIONRESULT2DX_H_
#define ADJUST_ADJUSTPURCHASEVERIFICATIONRESULT2DX_H_

#include <iostream>

class AdjustPurchaseVerificationResult2dx {
private:
    std::string verificationStatus;
    std::string message;
    int code;
public:
    AdjustPurchaseVerificationResult2dx() {}
    AdjustPurchaseVerificationResult2dx(
        std::string verificationStatus,
        std::string message,
        int code) {
        this->verificationStatus = verificationStatus;
        this->message = message;
        this->code = code;
    }

    std::string getVerificationStatus();
    std::string getMessage();
    int getCode();
};

#endif /* ADJUST_ADJUSTPURCHASEVERIFICATIONRESULT2DX_H_ */
