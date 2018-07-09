//
//  AdjustCommandExecutor.cpp
//  Adjust SDK
//
//  Created by Srdjan Tubin on 04/06/18.
//

#include <regex>
#include "Adjust/Adjust2dx.h"
#include "Adjust/AdjustConfig2dx.h"
#include "Adjust/AdjustTestOptions2dx.h"
#include "AdjustCommandExecutor.h"
#include "AdjustTesting/TestLib2dx.h"
#include "command.h"

const std::string AdjustCommandExecutor::TAG = "AdjustCommandExecutor";

AdjustCommandExecutor::AdjustCommandExecutor(TestLib2dx *testLibrary, std::string baseUrl, std::string gdprUrl) {
    this->testLibrary = testLibrary;
    this->baseUrl = baseUrl;
    this->gdprUrl = gdprUrl;
}

void AdjustCommandExecutor::executeCommand(Command *command) {
    this->command = command;
    if (command->methodName == "testOptions") {
        this->testOptions();
    } else if (command->methodName == "config") {
        this->config();
    } else if (command->methodName == "start") {
        this->start();
    } else if (command->methodName == "event") {
        this->event();
    } else if (command->methodName == "trackEvent") {
        this->trackEvent();
    } else if (command->methodName == "resume") {
        this->resume();
    } else if (command->methodName == "pause") {
        this->pause();
    } else if (command->methodName == "setReferrer") {
        this->setReferrer();
    } else if (command->methodName == "setOfflineMode") {
        this->setOfflineMode();
    } else if (command->methodName == "sendFirstPackages") {
        this->sendFirstPackages();
    } else if (command->methodName == "addSessionCallbackParameter") {
        this->addSessionCallbackParameter();
    } else if (command->methodName == "addSessionPartnerParameter") {
        this->addSessionPartnerParameter();
    } else if (command->methodName == "removeSessionCallbackParameter") {
        this->removeSessionCallbackParameter();
    } else if (command->methodName == "removeSessionPartnerParameter") {
        this->removeSessionPartnerParameter();
    } else if (command->methodName == "resetSessionCallbackParameters") {
        this->resetSessionCallbackParameters();
    } else if (command->methodName == "resetSessionPartnerParameters") {
        this->resetSessionPartnerParameters();
    } else if (command->methodName == "setPushToken") {
        this->setPushToken();
    } else if (command->methodName == "openDeeplink") {
        this->openDeeplink();
    } else if (command->methodName == "sendReferrer") {
        this->sendReferrer();
    } else if (command->methodName == "gdprForgetMe") {
        this->gdprForgetMe();
    } 
}

void AdjustCommandExecutor::testOptions() {
    AdjustTestOptions2dx testOptions = AdjustTestOptions2dx();
    testOptions.baseUrl = this->baseUrl;
    testOptions.gdprUrl = this->gdprUrl;
    if (this->command->containsParameter("basePath")) {
        this->basePath = command->getFirstParameterValue("basePath");
        this->gdprPath = command->getFirstParameterValue("basePath");
    }
    if (this->command->containsParameter("timerInterval")) {
        std::string timerIntervalString = command->getFirstParameterValue("timerInterval");
        testOptions.timerIntervalInMilliseconds = atol(timerIntervalString.c_str());
    }
    if (this->command->containsParameter("timerStart")) {
        std::string timerStartString = command->getFirstParameterValue("timerStart");
        testOptions.timerStartInMilliseconds = atol(timerStartString.c_str());
    }
    if (this->command->containsParameter("sessionInterval")) {
        std::string sessionIntervalString = command->getFirstParameterValue("sessionInterval");
        testOptions.sessionIntervalInMilliseconds = atol(sessionIntervalString.c_str());
    }
    if (this->command->containsParameter("subsessionInterval")) {
        std::string subsessionIntervalString = command->getFirstParameterValue("subsessionInterval");
        testOptions.subsessionIntervalInMilliseconds = atol(subsessionIntervalString.c_str());
    }
    if (this->command->containsParameter("tryInstallReferrer")) {
        std::string tryInstallReferrerString = command->getFirstParameterValue("tryInstallReferrer");
        testOptions.tryInstallReferrer = (tryInstallReferrerString == "true");
    }
    if (this->command->containsParameter("noBackoffWait")) {
        std::string noBackoffWaitString = command->getFirstParameterValue("noBackoffWait");
        testOptions.noBackoffWait = (noBackoffWaitString == "true");
    }
    if (this->command->containsParameter("teardown")) {
        std::vector<std::string> teardownOptions = command->getParameters("teardown");
        std::vector<std::string>::iterator toIterator = teardownOptions.begin();
        while(toIterator != teardownOptions.end()) {
            std::string teardownOption = (*toIterator);
            if (teardownOption == "resetSdk") {
                testOptions.teardown = true;
                testOptions.basePath = this->basePath;
                testOptions.gdprPath = this->gdprPath;
                testOptions.useTestConnectionOptions = true;
                testOptions.tryInstallReferrer = false;
            }
            if (teardownOption == "deleteState") {
                testOptions.setContext = true;
            }
            if (teardownOption == "resetTest") {
                savedEvents.clear();
                savedConfigs.clear();
                testOptions.timerIntervalInMilliseconds = (long) -1;
                testOptions.timerStartInMilliseconds = (long) -1;
                testOptions.sessionIntervalInMilliseconds = (long) -1;
                testOptions.subsessionIntervalInMilliseconds = (long) -1;
            }
            if (teardownOption == "sdk") {
                testOptions.teardown = true;
                testOptions.basePath = NULL;
                testOptions.gdprPath = NULL;
                testOptions.useTestConnectionOptions = false;
            }
            if (teardownOption == "test") {
                savedEvents = NULL;
                savedConfigs = NULL;
                testOptions.timerIntervalInMilliseconds = (long) -1;
                testOptions.timerStartInMilliseconds = (long) -1;
                testOptions.sessionIntervalInMilliseconds = (long) -1;
                testOptions.subsessionIntervalInMilliseconds = (long) -1;
            }
            toIterator++;
        }

    }
    Adjust2dx::setTestOptions(testOptions);
}

void AdjustCommandExecutor::config() {
    int configNumber = 0;
    if (this->command->containsParameter("configName")) {
        std::string configName = command->getFirstParameterValue("configName");
        std::string configNumberStr = configName.substr (configName.length() - 1, 1);
        configNumber = std::stoi(configNumberStr);
    }

    AdjustConfig2dx adjustConfig;
    if (this->savedConfigs.count(configNumber) > 0) {
        adjustConfig = this->savedConfigs[configNumber];
    } else {
        std::string environmentParam = command->getFirstParameterValue("environment");
        std::string appToken = command->getFirstParameterValue("appToken");

        std::string environment;
        if (environmentParam == "production") {
            environment = AdjustEnvironmentProduction2dx;
        } else {
            environment = AdjustEnvironmentSandbox2dx;
        }

        auto adjustConfig = AdjustConfig2dx(appToken, environment);
        adjustConfig.setLogLevel(AdjustLogLevel2dxVerbose);

        savedConfigs[configNumber] = adjustConfig;
    }

    if (this->command->containsParameter("logLevel")) {
        std::string logLevelString = command->getFirstParameterValue("logLevel");
        AdjustLogLevel2dx logLevel = NULL;
        if (logLevelString == "verbose") {
            logLevel = AdjustLogLevel2dxVerbose;
        } else if (logLevelString == "debug") {
            logLevel = AdjustLogLevel2dxDebug;
        }  else if (logLevelString == "info") {
            logLevel = AdjustLogLevel2dxInfo;
        }  else if (logLevelString == "warn") {
            logLevel = AdjustLogLevel2dxWarn;
        }  else if (logLevelString == "error") {
            logLevel = AdjustLogLevel2dxError;
        }  else if (logLevelString == "assert") {
            logLevel = AdjustLogLevel2dxAssert;
        }  else if (logLevelString == "suppress") {
            logLevel = AdjustLogLevel2dxSuppress;
        } 
        
        std::cout << "TestApp: logLevel: " << logLevelString << std::endl;
        adjustConfig.setLogLevel(logLevel);
    }

    if (this->command->containsParameter("sdkPrefix")) {
        //std::string sdkPrefix = command->getFirstParameterValue("sdkPrefix");
        //adjustConfig.setSdkPrefix(sdkPrefix);
    }

    if (this->command->containsParameter("defaultTracker")) {
        std::string defaultTracker = command->getFirstParameterValue("defaultTracker");
        adjustConfig.setDefaultTracker(defaultTracker);
    }

    if (this->command->containsParameter("appSecret")) {
        std::vector<std::string> appSecretArray = command->getParameters("appSecret");

        unsigned long long secretId = strtoull(appSecretArray[0].c_str(), NULL, 10);
        unsigned long long info1 = strtoull(appSecretArray[1].c_str(), NULL, 10);
        unsigned long long info2 = strtoull(appSecretArray[2].c_str(), NULL, 10);
        unsigned long long info3 = strtoull(appSecretArray[3].c_str(), NULL, 10);
        unsigned long long info4 = strtoull(appSecretArray[4].c_str(), NULL, 10);

        adjustConfig.setAppSecret(secretId, info1, info2, info3, info4);
    }

    if (this->command->containsParameter("delayStart")) {
        std::string delayStartString = command->getFirstParameterValue("delayStart");
        double delayStart = std::stod(delayStartString);
        adjustConfig.setDelayStart(delayStart);
    }

    if (this->command->containsParameter("deviceKnown")) {
        std::string deviceKnownString = command->getFirstParameterValue("deviceKnown");
        bool deviceKnown = (deviceKnownString == "true");
        adjustConfig.setDeviceKnown(deviceKnown);
    }

    if (this->command->containsParameter("eventBufferingEnabled")) {
        std::string eventBufferingEnabledString = command->getFirstParameterValue("eventBufferingEnabled");
        bool eventBufferingEnabled = (eventBufferingEnabledString == "true");
        adjustConfig.setEventBufferingEnabled(eventBufferingEnabled);
    }

    if (this->command->containsParameter("sendInBackground")) {
        std::string sendInBackgroundString = command->getFirstParameterValue("sendInBackground");
        bool sendInBackground = (sendInBackgroundString == "true");
        adjustConfig.setSendInBackground(sendInBackground);
    }

    if (this->command->containsParameter("userAgent")) {
        std::string userAgent = command->getFirstParameterValue("userAgent");
        adjustConfig.setUserAgent(userAgent);
    }

    if (this->command->containsParameter("deferredDeeplinkCallback")) {
        adjustConfig.setDeferredDeeplinkCallback([](std::string deeplink) {
            if (deeplink == NULL) {
                std::cout << "TestApp: Deeplink Response, uri = NULL" << std::endl;
                return false;
            }

            std::cout << "TestApp: Deeplink Response, uri = " << deeplink << std::endl;

            // if starts with "adjusttest"
            std::smatch match;
            std::regex_search(deeplink, match, std::regex("^adjusttest"));
            return match.suffix().length() > 0;
        });
    }

    if (this->command->containsParameter("attributionCallbackSendAll")) {
        adjustConfig.setAttributionCallback([](AdjustAttribution2dx attribution){
            std::cout << "TestApp: attribution received: " << attribution.getTrackerToken() << std::endl;

            this->testLibrary->addInfoToSend("trackerToken", attribution.getTrackerToken());
            this->testLibrary->addInfoToSend("trackerName", attribution.getTrackerName());
            this->testLibrary->addInfoToSend("network", attribution.getNetwork());
            this->testLibrary->addInfoToSend("campaign", attribution.getCampaign());
            this->testLibrary->addInfoToSend("adgroup", attribution.getAdgroup());
            this->testLibrary->addInfoToSend("creative", attribution.getCreative());
            this->testLibrary->addInfoToSend("clickLabel", attribution.getClickLabel());
            this->testLibrary->addInfoToSend("adid", attribution.getAdid());
            this->testLibrary->sendInfoToServer(this->basePath);
        });
    }

    if (this->command->containsParameter("sessionCallbackSendSuccess")) {
        adjustConfig.setSessionSuccessCallback([](AdjustSessionSuccess2dx adjustSessionSuccess) {
            std::cout << "TestApp: session_success received: " << adjustSessionSuccess.getMessage() << std::endl;

            this->testLibrary->addInfoToSend("message", adjustSessionSuccess.getMessage());
            this->testLibrary->addInfoToSend("timestamp", adjustSessionSuccess.getTimestamp());
            this->testLibrary->addInfoToSend("adid", adjustSessionSuccess.getAdid());
            if(adjustSessionSuccess.getJsonResponse() != NULL) {
                this->testLibrary->addInfoToSend("jsonResponse", adjustSessionSuccess.getJsonResponse());
            }
            this->testLibrary->sendInfoToServer(this->basePath);
        });
    }

    if (this->command->containsParameter("sessionCallbackSendFailure")) {
        adjustConfig.setSessionFailureCallback([](AdjustSessionFailure2dx adjustSessionFailure) {
            std::cout << "TestApp: session_fail received: " << adjustSessionFailure.getMessage() << std::endl;

            this->testLibrary->addInfoToSend("message", adjustSessionFailure.getMessage());
            this->testLibrary->addInfoToSend("timestamp", adjustSessionFailure.getTimestamp());
            this->testLibrary->addInfoToSend("adid", adjustSessionFailure.getAdid());
            this->testLibrary->addInfoToSend("willRetry", adjustSessionFailure.getWillRetry());
            if(adjustSessionFailure.getJsonResponse() != NULL) {
                this->testLibrary->addInfoToSend("jsonResponse", adjustSessionFailure.getJsonResponse());
            }
            this->testLibrary->sendInfoToServer(this->basePath);
        });
    }

    if (this->command->containsParameter("eventCallbackSendSuccess")) {
        adjustConfig.setEventSuccessCallback([](AdjustEventSuccess2dx adjustEventSuccess) {
            std::cout << "TestApp: event_success received: " << adjustEventSuccess.getMessage() << std::endl;

            this->testLibrary->addInfoToSend("message", adjustEventSuccess.getMessage());
            this->testLibrary->addInfoToSend("timestamp", adjustEventSuccess.getTimestamp());
            this->testLibrary->addInfoToSend("adid", adjustEventSuccess.getAdid());
            this->testLibrary->addInfoToSend("eventToken", adjustEventSuccess.getEventToken());
            if(adjustEventSuccess.getJsonResponse() != NULL) {
                this->testLibrary->addInfoToSend("jsonResponse", adjustEventSuccess.getJsonResponse());
            }
            this->testLibrary->sendInfoToServer(this->basePath);
        });
    }

    if (this->command->containsParameter("eventCallbackSendFailure")) {
        adjustConfig.setEventFailureCallback([](AdjustEventFailure2dx adjustEventFailure){
            std::cout << "TestApp: event_fail received: " << adjustEventFailure.getMessage() << std::endl;

            this->testLibrary->addInfoToSend("message", adjustEventFailure.getMessage());
            this->testLibrary->addInfoToSend("timestamp", adjustEventFailure.getTimestamp());
            this->testLibrary->addInfoToSend("adid", adjustEventFailure.getAdid());
            this->testLibrary->addInfoToSend("eventToken", adjustEventFailure.getEventToken());
            this->testLibrary->addInfoToSend("willRetry", adjustEventFailure.getWillRetry());
            if(adjustEventFailure.getJsonResponse() != NULL) {
                this->testLibrary->addInfoToSend("jsonResponse", adjustEventFailure.getJsonResponse());
            }
            this->testLibrary->sendInfoToServer(this->basePath);
        });
    }
}

void AdjustCommandExecutor::start() {
    config();
    int configNumber = 0;
    if (this->command->containsParameter("configName")) {
        std::string configName = command->getFirstParameterValue("configName");
        std::string configNumberStr = configName.substr (configName.length() - 1, 1);
        configNumber = std::stoi(configNumberStr);
    }

    AdjustConfig2dx adjustConfig = this->savedConfigs[configNumber];

    Adjust2dx::start(adjustConfig);

    this->savedConfigs.erase(0);
}

void AdjustCommandExecutor::event() {
    int eventNumber = 0;
    if (this->command->containsParameter("eventName")) {
        std::string eventName = command->getFirstParameterValue("eventName");
        std::string eventNumberStr = eventName.substr (eventName.length() - 1, 1);
        eventNumber = std::stoi(eventNumberStr);
    }

    AdjustEvent2dx adjustEvent = NULL;
    if (this->savedEvents.count(eventNumber) > 0) {
        adjustEvent = this->savedEvents[eventNumber];
    } else {
        std::string eventToken = command->getFirstParameterValue("eventToken");

        adjustEvent = AdjustEvent2dx(eventToken);
        savedEvents[eventNumber] = adjustEvent;
    }

    if (this->command->containsParameter("revenue")) {
        std::vector<std::string> revenueParams = command->getParameters("revenue");
        std::string currency = revenueParams[0];
        double revenue = std::stod(revenueParams[1]);
        adjustEvent.setRevenue(revenue, currency);
    }

    if (this->command->containsParameter("callbackParams")) {
        std::vector<std::string> callbackParams = command->getParameters("callbackParams");
        for (int i = 0; i < callbackParams.size(); i = i + 2) {
            std::string key = callbackParams[i];
            std::string value = callbackParams[i + 1];
            adjustEvent.addCallbackParameter(key, value);
        }
    }

    if (this->command->containsParameter("partnerParams")) {
        std::vector<std::string> partnerParams = command->getParameters("partnerParams");
        for (int i = 0; i < partnerParams.size(); i = i + 2) {
            std::string key = partnerParams[i];
            std::string value = partnerParams[i + 1];
            adjustEvent.addPartnerParameter(key, value);
        }
    }

    if (this->command->containsParameter("orderId")) {
        std::string orderId = command->getFirstParameterValue("orderId");
        adjustEvent.setTransactionId(orderId);
    }
}

void AdjustCommandExecutor::trackEvent() {
    event();
    int eventNumber = 0;
    if (this->command->containsParameter("eventName")) {
        std::string eventName = command->getFirstParameterValue("eventName");
        std::string eventNameStr = eventName.substr (eventName.length() - 1, 1);
        eventNumber = std::stoi(eventNameStr);
    }

    AdjustEvent2dx adjustEvent = this->savedEvents[eventNumber];
    Adjust2dx::trackEvent(adjustEvent);

    this->savedEvents.erase(0);
}

void AdjustCommandExecutor::resume() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Adjust2dx::onResume();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
#endif
}

void AdjustCommandExecutor::pause() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Adjust2dx::onPause();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
#endif
}

void AdjustCommandExecutor::setReferrer() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string referrer = command->getFirstParameterValue("referrer");
    Adjust2dx::setReferrer(referrer);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
#endif
}

void AdjustCommandExecutor::setOfflineMode() {
    std::string enabledStr = command->getFirstParameterValue("enabled");
    bool enabled = (enabledStr == "true");
    Adjust2dx::setOfflineMode(enabled);
}

void AdjustCommandExecutor::sendFirstPackages() {
    Adjust2dx::sendFirstPackages();
}

void AdjustCommandExecutor::addSessionCallbackParameter() {
    if (this->command->containsParameter("KeyValue")) {
        std::vector<std::string> keyValuePairs = command->getParameters("KeyValue");
        for (int i = 0; i < keyValuePairs.size(); i = i + 2) {
            std::string key = keyValuePairs[i];
            std::string value = keyValuePairs[i + 1];
            Adjust2dx::addSessionCallbackParameter(key, value);
        }
    }
}

void AdjustCommandExecutor::addSessionPartnerParameter() {
    if (this->command->containsParameter("KeyValue")) {
        std::vector<std::string> keyValuePairs = command->getParameters("KeyValue");
        for (int i = 0; i < keyValuePairs.size(); i = i + 2) {
            std::string key = keyValuePairs[i];
            std::string value = keyValuePairs[i + 1];
            Adjust2dx::addSessionPartnerParameter(key, value);
        }
    }
}

void AdjustCommandExecutor::removeSessionCallbackParameter() {
    if (this->command->containsParameter("key")) {
        std::vector<std::string> keys = command->getParameters("key");
        for (int i = 0; i < keys.size(); i++) {
            std::string key = keys[i];
            Adjust2dx::removeSessionCallbackParameter(key);
        }
    }
}

void AdjustCommandExecutor::removeSessionPartnerParameter() {
    if (this->command->containsParameter("key")) {
        std::vector<std::string> keys = command->getParameters("key");
        for (int i = 0; i < keys.size(); i++) {
            std::string key = keys[i];
            Adjust2dx::removeSessionPartnerParameter(key);
        }
    }
}

void AdjustCommandExecutor::resetSessionCallbackParameters() {
    Adjust2dx::resetSessionCallbackParameters();
}

void AdjustCommandExecutor::resetSessionPartnerParameters() {
    Adjust2dx::resetSessionPartnerParameters();
}

void AdjustCommandExecutor::setPushToken() {
    std::string token = command->getFirstParameterValue("pushToken");
    Adjust2dx::setDeviceToken(token);
}

void AdjustCommandExecutor::openDeeplink() {
    std::string deeplink = command->getFirstParameterValue("deeplink");
    Adjust2dx::appWillOpenUrl(deeplink);
}

void AdjustCommandExecutor::sendReferrer() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string referrer = command->getFirstParameterValue("referrer");
    Adjust2dx::setReferrer(referrer);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
#endif
}

void AdjustCommandExecutor::gdprForgetMe() {
    Adjust2dx::gdprForgetMe();
}