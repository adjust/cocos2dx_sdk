//
//  AdjustSessionFailure2dx.h
//  Adjust SDK
//
//  Created by Uglješa Erceg on 06/10/2016.
//
//

#ifndef ADJUST_ADJUSTSESSIONFAILURE2DX_H_
#define ADJUST_ADJUSTSESSIONFAILURE2DX_H_

#include <iostream>

class AdjustSessionFailure2dx {
private:
    std::string adid;
    std::string message;
    std::string timestamp;
    std::string willRetry;
    std::string jsonResponse;
public:
    AdjustSessionFailure2dx() {}
    AdjustSessionFailure2dx(std::string adid, std::string message, std::string timestamp, std::string willRetry, std::string jsonResponse) {
        this->adid = adid;
        this->message = message;
        this->timestamp = timestamp;
        this->willRetry = willRetry;
        this->jsonResponse = jsonResponse;
    }
    
    std::string getAdid();
    std::string getMessage();
    std::string getWillRetry();
    std::string getTimestamp();
    std::string getJsonResponse();
};

#endif /* ADJUST_ADJUSTSESSIONFAILURE2DX_H_ */
