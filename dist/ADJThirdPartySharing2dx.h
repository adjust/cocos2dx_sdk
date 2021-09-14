//
//  ADJThirdPartySharing2dx.h
//  Adjust SDK
//
//  Created by Uglješa Erceg (@uerceg) on 10th September 2021.
//  Copyright © 2021 Adjust GmbH. All rights reserved.
//

#ifndef _ADJUST_ADJTHIRDPARTYSHARING2DX_H_
#define _ADJUST_ADJTHIRDPARTYSHARING2DX_H_

#include <iostream>

class ADJThirdPartySharing2dx {
private:
    void* thirdPartySharing;
    void initThirdPartySharing();
    void initThirdPartySharing(bool isEnabled);

public:
    ADJThirdPartySharing2dx() {
        initThirdPartySharing();
    }
    ADJThirdPartySharing2dx(bool isEnabled) {
        initThirdPartySharing(isEnabled);
    }

    void addGranularOption(std::string partnerName, std::string key, std::string value);
    void* getThirdPartySharing();
};

#endif /* _ADJUST_ADJTHIRDPARTYSHARING2DX_H_ */
