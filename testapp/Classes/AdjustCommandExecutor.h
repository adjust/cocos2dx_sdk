//
//  AdjustCommandExecutor.h
//  Adjust SDK
//
//  Created by Srdjan Tubin on 04/06/18.
//

#ifndef  _ADJUST_COMMAND_EXECUTOR_H_
#define  _ADJUST_COMMAND_EXECUTOR_H_

// TODO: includes
#include "Command.h"
#include <string>
#include <vector>

#include "Adjust/AdjustEvent2dx.h"
#include "Adjust/AdjustConfig2dx.h"
#include "Adjust/AdjustAttribution2dx.h"
#include "Adjust/AdjustEventFailure2dx.h"
#include "Adjust/AdjustEventSuccess2dx.h"
#include "Adjust/AdjustSessionSuccess2dx.h"
#include "Adjust/AdjustSessionFailure2dx.h"

class AdjustCommandExecutor {
private:
    TestLib2dx testLibrary;
    std::string baseUrl;
    std::string gdprUrl;
    std::string basePath;
    std::string gdprPath;
    std::map<std::int8_t, AdjustEvent2dx> savedEvents;
    std::map<std::int8_t, AdjustConfig2dx> savedConfigs;
    Command command;

    AdjustCommandExecutor(TestLib2dx testLibrary, std::string baseUrl, std::string gdprUrl);

    void testOptions();
    void config();
    void start();
    void event();
    void trackEvent();
    void setReferrer();
    void pause();
    void resume();
    void setEnabled();
    void setOfflineMode();
    void sendFirstPackages();
    void addSessionCallbackParameter();
    void addSessionPartnerParameter();
    void removeSessionCallbackParameter();
    void removeSessionPartnerParameter();
    void resetSessionCallbackParameters();
    void resetSessionPartnerParameters();
    void setPushToken();
    void openDeeplink();
    void sendReferrer();
    void gdprForgetMe();
public:
	static const std::string TAG;
	void executeCommand(Command command);
}

#endif // _ADJUST_COMMAND_EXECUTOR_H_