/*
 * Adjust2dx.h
 *
 *  Created on: Jun 16, 2015
 *      Author: uerceg
 */

#ifndef ADJUST_ADJUST2DX_H_
#define ADJUST_ADJUST2DX_H_

#include <iostream>

#include "Adjust/AdjustEvent2dx.h"

extern std::string AdjustEnvironmentSandbox2dx;
extern std::string AdjustEnvironmentProduction2dx;

class Adjust2dx {
public:

    static void trackEvent(AdjustEvent2dx event);
    static void setEnabled(bool isEnabled);
    static bool isEnabled();
    static void setOfflineMode(bool isOffline);
};

#endif /* ADJUST_ADJUST2DX_H_ */
