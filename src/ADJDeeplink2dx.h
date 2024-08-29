//
//  ADJDeeplink2dx.h
//  Adjust SDK
//

#ifndef _ADJUST_ADJDEEPLINK2DX_H_
#define _ADJUST_ADJDEEPLINK2DX_H_

#include <iostream>

class ADJDeeplink2dx {
private:
    void* deeplink;
    void initDeeplink(std::string deeplinkStr);

public:
    ADJDeeplink2dx() {}
    ADJDeeplink2dx(std::string deeplinkStr) {
        initDeeplink(deeplinkStr);
    }

    void* getDeeplink();
};

#endif /* _ADJUST_ADJDEEPLINK2DX_H_ */
