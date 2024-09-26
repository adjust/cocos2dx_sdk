//
//  AdjustCommandExecutor.h
//  Adjust SDK
//
//  Created by Srdjan Tubin (@2beens) on 4th June 2018.
//  Copyright © 2018-2020 Adjust GmbH. All rights reserved.
//

#ifndef  _ADJUST_COMMAND_EXECUTOR_H_
#define  _ADJUST_COMMAND_EXECUTOR_H_

#include <map>
#include <string>
#include <vector>
#include "Command.h"
#include "Adjust/Adjust2dx.h"
#include "Adjust/AdjustEvent2dx.h"
#include "Adjust/AdjustConfig2dx.h"
#include "Adjust/AdjustAttribution2dx.h"
#include "Adjust/AdjustAppStoreSubscription2dx.h"
#include "Adjust/AdjustPlayStoreSubscription2dx.h"
#include "Adjust/AdjustEventFailure2dx.h"
#include "Adjust/AdjustEventSuccess2dx.h"
#include "Adjust/AdjustSessionSuccess2dx.h"
#include "Adjust/AdjustSessionFailure2dx.h"
#include "Adjust/AdjustThirdPartySharing2dx.h"
#include "Adjust/AdjustAdRevenue2dx.h"
#include "Adjust/AdjustAppStorePurchase2dx.h"
#include "Adjust/AdjustPlayStorePurchase2dx.h"
#include "Adjust/AdjustDeeplink2dx.h"
#include "Adjust/AdjustPurchaseVerificationResult2dx.h"
#include "Adjust/test/TestLib2dx.h"
#include "Adjust/test/TestConnectionOptions2dx.h"

class AdjustCommandExecutor {
private:
    std::string urlOverwrite;
    std::string basePath;
    std::map<std::int8_t, AdjustEvent2dx*> savedEvents;
    std::map<std::int8_t, AdjustConfig2dx*> savedConfigs;
    Command *command;

    void testOptions();
    void config();
    void start();
    void event();
    void trackEvent();
    void pause();
    void resume();
    void setEnabled();
    void setOfflineMode();
    void addGlobalCallbackParameter();
    void addGlobalPartnerParameter();
    void removeGlobalCallbackParameter();
    void removeGlobalPartnerParameter();
    void removeGlobalCallbackParameters();
    void removeGlobalPartnerParameters();
    void setPushToken();
    void openDeeplink();
    void gdprForgetMe();
    void trackSubscription();
    void trackThirdPartySharing();
    void trackMeasurementConsent();
    void trackAdRevenue();
    void getLastDeeplink();
    void verifyPurchase();
    void verifyTrack();
    void processDeeplink();
    void attributionGetter();
public:
    static const std::string TAG;
    AdjustCommandExecutor(std::string urlOverwrite);
    void executeCommand(Command *command);
};

#endif // _ADJUST_COMMAND_EXECUTOR_H_
