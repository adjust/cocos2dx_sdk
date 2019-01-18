//
//  AdjustCommandExecutor.cpp
//  Adjust SDK
//
//  Created by Srdjan Tubin (@2beens) on 4th June 2018.
//  Copyright © 2018-2019 Adjust GmbH. All rights reserved.
//

#define COCOS2D_DEBUG 1

#include <regex>
#include <base/CCConsole.h>
#include <platform/CCStdC.h>
#include "AdjustCommandExecutor.h"

static std::string localBasePath;
const std::string AdjustCommandExecutor::TAG = "AdjustCommandExecutor";

AdjustCommandExecutor::AdjustCommandExecutor(std::string baseUrl, std::string gdprUrl) {
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
    } else if (command->methodName == "setEnabled") {
        this->setEnabled();
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
    std::map<std::string, std::string> testOptions;
    testOptions["baseUrl"] = this->baseUrl;
    testOptions["gdprUrl"] = this->gdprUrl;
    if (this->command->containsParameter("basePath")) {
        this->basePath = command->getFirstParameterValue("basePath");
        this->gdprPath = command->getFirstParameterValue("basePath");
    }
    if (this->command->containsParameter("timerInterval")) {
        testOptions["timerIntervalInMilliseconds"] = command->getFirstParameterValue("timerInterval");
    }
    if (this->command->containsParameter("timerStart")) {
        testOptions["timerStartInMilliseconds"] = command->getFirstParameterValue("timerStart");
    }
    if (this->command->containsParameter("sessionInterval")) {
        testOptions["sessionIntervalInMilliseconds"] = command->getFirstParameterValue("sessionInterval");
    }
    if (this->command->containsParameter("subsessionInterval")) {
        testOptions["subsessionIntervalInMilliseconds"] = command->getFirstParameterValue("subsessionInterval");
    }
    if (this->command->containsParameter("tryInstallReferrer")) {
        testOptions["tryInstallReferrer"] = command->getFirstParameterValue("tryInstallReferrer");
    }
    if (this->command->containsParameter("noBackoffWait")) {
        testOptions["noBackoffWait"] = command->getFirstParameterValue("noBackoffWait");
    }
    // "false" is default value - iAd will not be used in test app by default.
    testOptions["iAdFrameworkEnabled"] = "false";
    if (this->command->containsParameter("iAdFrameworkEnabled")) {
        testOptions["iAdFrameworkEnabled"] = command->getFirstParameterValue("iAdFrameworkEnabled");
    }
    if (this->command->containsParameter("teardown")) {
        std::vector<std::string> teardownOptions = command->getParameters("teardown");
        std::vector<std::string>::iterator toIterator = teardownOptions.begin();
        while(toIterator != teardownOptions.end()) {
            std::string teardownOption = (*toIterator);
            if (teardownOption == "resetSdk") {
                testOptions["teardown"] = "true";
                testOptions["basePath"] = this->basePath;
                testOptions["gdprPath"] = this->gdprPath;
                // Android specific.
                testOptions["useTestConnectionOptions"] = "true";
                testOptions["tryInstallReferrer"] = "false";
                #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                Adjust2dx::teardown();
                #endif
            }
            if (teardownOption == "deleteState") {
                // Android specific.
                testOptions["setContext"] = "true";
                // iOS specific.
                testOptions["deleteState"] = "true";
            }
            if (teardownOption == "resetTest") {
                savedEvents.clear();
                savedConfigs.clear();
                testOptions["timerIntervalInMilliseconds"] = "-1";
                testOptions["timerStartInMilliseconds"] = "-1";
                testOptions["sessionIntervalInMilliseconds"] = "-1";
                testOptions["subsessionIntervalInMilliseconds"] = "-1";
            }
            if (teardownOption == "sdk") {
                testOptions["teardown"] = "true";
                testOptions["basePath"] = "";
                testOptions["gdprPath"] = "";
                // Android specific.
                testOptions["useTestConnectionOptions"] = "false";
            }
            if (teardownOption == "test") {
                savedEvents.clear();
                savedConfigs.clear();
                testOptions["timerIntervalInMilliseconds"] = "-1";
                testOptions["timerStartInMilliseconds"] = "-1";
                testOptions["sessionIntervalInMilliseconds"] = "-1";
                testOptions["subsessionIntervalInMilliseconds"] = "-1";
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

    AdjustConfig2dx *adjustConfig;
    if (this->savedConfigs.count(configNumber) > 0) {
        adjustConfig = this->savedConfigs[configNumber];
    } else {
        std::string environmentParam = "";
        std::string appToken = "";
        if (this->command->containsParameter("environment")) {
            environmentParam = command->getFirstParameterValue("environment");
        }
        if (this->command->containsParameter("appToken")) {
            appToken = command->getFirstParameterValue("appToken");
        }

        std::string environment;
        if (environmentParam == "production") {
            environment = AdjustEnvironmentProduction2dx;
        } else if (environmentParam == "sandbox") {
            environment = AdjustEnvironmentSandbox2dx;
        } else {
            environment = "";
        }

        adjustConfig = new AdjustConfig2dx(appToken, environment);
        adjustConfig->setLogLevel(AdjustLogLevel2dxVerbose);
        savedConfigs[configNumber] = adjustConfig;
    }

    if (this->command->containsParameter("logLevel")) {
        std::string logLevelString = command->getFirstParameterValue("logLevel");
        if (logLevelString == "verbose") {
            adjustConfig->setLogLevel(AdjustLogLevel2dxVerbose);
        } else if (logLevelString == "debug") {
            adjustConfig->setLogLevel(AdjustLogLevel2dxDebug);
        }  else if (logLevelString == "info") {
            adjustConfig->setLogLevel(AdjustLogLevel2dxInfo);
        }  else if (logLevelString == "warn") {
            adjustConfig->setLogLevel(AdjustLogLevel2dxWarn);
        }  else if (logLevelString == "error") {
            adjustConfig->setLogLevel(AdjustLogLevel2dxError);
        }  else if (logLevelString == "assert") {
            adjustConfig->setLogLevel(AdjustLogLevel2dxAssert);
        }  else if (logLevelString == "suppress") {
            adjustConfig->setLogLevel(AdjustLogLevel2dxSuppress);
        }
    }

    if (this->command->containsParameter("defaultTracker")) {
        std::string defaultTracker = command->getFirstParameterValue("defaultTracker");
        adjustConfig->setDefaultTracker(defaultTracker);
    }

    if (this->command->containsParameter("appSecret")) {
        try {
            std::vector<std::string> appSecretArray = command->getParameters("appSecret");

            if (appSecretArray[0].length() > 0
                && appSecretArray[1].length() > 0
                && appSecretArray[2].length() > 0
                && appSecretArray[3].length() > 0
                && appSecretArray[4].length() > 0) {
                unsigned long long secretId = strtoull(appSecretArray[0].c_str(), NULL, 10);
                unsigned long long info1 = strtoull(appSecretArray[1].c_str(), NULL, 10);
                unsigned long long info2 = strtoull(appSecretArray[2].c_str(), NULL, 10);
                unsigned long long info3 = strtoull(appSecretArray[3].c_str(), NULL, 10);
                unsigned long long info4 = strtoull(appSecretArray[4].c_str(), NULL, 10);
                adjustConfig->setAppSecret(secretId, info1, info2, info3, info4);
            }
        }
        catch (const std::exception &e) {
            CCLOG("\n[AdjustCommandExecutor]: appSecret exception: %s", e.what());
        }
    }

    if (this->command->containsParameter("delayStart")) {
        std::string delayStartString = command->getFirstParameterValue("delayStart");
        double delayStart = std::stod(delayStartString);
        adjustConfig->setDelayStart(delayStart);
    }

    if (this->command->containsParameter("deviceKnown")) {
        std::string deviceKnownString = command->getFirstParameterValue("deviceKnown");
        bool deviceKnown = (deviceKnownString == "true");
        adjustConfig->setDeviceKnown(deviceKnown);
    }

    if (this->command->containsParameter("eventBufferingEnabled")) {
        std::string eventBufferingEnabledString = command->getFirstParameterValue("eventBufferingEnabled");
        bool eventBufferingEnabled = (eventBufferingEnabledString == "true");
        adjustConfig->setEventBufferingEnabled(eventBufferingEnabled);
    }

    if (this->command->containsParameter("sendInBackground")) {
        std::string sendInBackgroundString = command->getFirstParameterValue("sendInBackground");
        bool sendInBackground = (sendInBackgroundString == "true");
        adjustConfig->setSendInBackground(sendInBackground);
    }

    if (this->command->containsParameter("userAgent")) {
        std::string userAgent = command->getFirstParameterValue("userAgent");
        adjustConfig->setUserAgent(userAgent);
    }

    if (this->command->containsParameter("attributionCallbackSendAll")) {
        localBasePath = this->basePath;
        adjustConfig->setAttributionCallback([](AdjustAttribution2dx attribution) {
            CCLOG("\n[AdjustCommandExecutor]: Attribution received: %s", attribution.getTrackerToken().c_str());
            TestLib2dx::addInfoToSend("trackerToken", attribution.getTrackerToken());
            TestLib2dx::addInfoToSend("trackerName", attribution.getTrackerName());
            TestLib2dx::addInfoToSend("network", attribution.getNetwork());
            TestLib2dx::addInfoToSend("campaign", attribution.getCampaign());
            TestLib2dx::addInfoToSend("adgroup", attribution.getAdgroup());
            TestLib2dx::addInfoToSend("creative", attribution.getCreative());
            TestLib2dx::addInfoToSend("clickLabel", attribution.getClickLabel());
            TestLib2dx::addInfoToSend("adid", attribution.getAdid());
            TestLib2dx::sendInfoToServer(localBasePath);
        });
    }

    if (this->command->containsParameter("sessionCallbackSendSuccess")) {
        localBasePath = this->basePath;
        adjustConfig->setSessionSuccessCallback([](AdjustSessionSuccess2dx adjustSessionSuccess) {
            CCLOG("\n[AdjustCommandExecutor]: Session success: %s", adjustSessionSuccess.getMessage().c_str());
            TestLib2dx::addInfoToSend("message", adjustSessionSuccess.getMessage());
            TestLib2dx::addInfoToSend("timestamp", adjustSessionSuccess.getTimestamp());
            TestLib2dx::addInfoToSend("adid", adjustSessionSuccess.getAdid());
            if (!adjustSessionSuccess.getJsonResponse().empty()) {
                TestLib2dx::addInfoToSend("jsonResponse", adjustSessionSuccess.getJsonResponse());
            }
            TestLib2dx::sendInfoToServer(localBasePath);
        });
    }

    if (this->command->containsParameter("sessionCallbackSendFailure")) {
        localBasePath = this->basePath;
        adjustConfig->setSessionFailureCallback([](AdjustSessionFailure2dx adjustSessionFailure) {
            CCLOG("\n[AdjustCommandExecutor]: Session failure: %s", adjustSessionFailure.getMessage().c_str());
            TestLib2dx::addInfoToSend("message", adjustSessionFailure.getMessage());
            TestLib2dx::addInfoToSend("timestamp", adjustSessionFailure.getTimestamp());
            TestLib2dx::addInfoToSend("adid", adjustSessionFailure.getAdid());
            TestLib2dx::addInfoToSend("willRetry", adjustSessionFailure.getWillRetry());
            if (!adjustSessionFailure.getJsonResponse().empty()) {
                TestLib2dx::addInfoToSend("jsonResponse", adjustSessionFailure.getJsonResponse());
            }
            TestLib2dx::sendInfoToServer(localBasePath);
        });
    }

    if (this->command->containsParameter("eventCallbackSendSuccess")) {
        localBasePath = this->basePath;
        adjustConfig->setEventSuccessCallback([](AdjustEventSuccess2dx adjustEventSuccess) {
            CCLOG("\n[AdjustCommandExecutor]: Event success: %s", adjustEventSuccess.getMessage().c_str());
            TestLib2dx::addInfoToSend("message", adjustEventSuccess.getMessage());
            TestLib2dx::addInfoToSend("timestamp", adjustEventSuccess.getTimestamp());
            TestLib2dx::addInfoToSend("adid", adjustEventSuccess.getAdid());
            TestLib2dx::addInfoToSend("eventToken", adjustEventSuccess.getEventToken());
            TestLib2dx::addInfoToSend("callbackId", adjustEventSuccess.getCallbackId());
            if (!adjustEventSuccess.getJsonResponse().empty()) {
                TestLib2dx::addInfoToSend("jsonResponse", adjustEventSuccess.getJsonResponse());
            }
            TestLib2dx::sendInfoToServer(localBasePath);
        });
    }

    if (this->command->containsParameter("eventCallbackSendFailure")) {
        localBasePath = this->basePath;
        adjustConfig->setEventFailureCallback([](AdjustEventFailure2dx adjustEventFailure){
            CCLOG("\n[AdjustCommandExecutor]: Event failure: %s", adjustEventFailure.getMessage().c_str());
            TestLib2dx::addInfoToSend("message", adjustEventFailure.getMessage());
            TestLib2dx::addInfoToSend("timestamp", adjustEventFailure.getTimestamp());
            TestLib2dx::addInfoToSend("adid", adjustEventFailure.getAdid());
            TestLib2dx::addInfoToSend("eventToken", adjustEventFailure.getEventToken());
            TestLib2dx::addInfoToSend("callbackId", adjustEventFailure.getCallbackId());
            TestLib2dx::addInfoToSend("willRetry", adjustEventFailure.getWillRetry());
            if (!adjustEventFailure.getJsonResponse().empty()) {
                TestLib2dx::addInfoToSend("jsonResponse", adjustEventFailure.getJsonResponse());
            }
            TestLib2dx::sendInfoToServer(localBasePath);
        });
    }

    if (this->command->containsParameter("deferredDeeplinkCallback")) {
        localBasePath = this->basePath;
        std::string openDeeplinkString = command->getFirstParameterValue("deferredDeeplinkCallback");
        // TODO: Figure out how to pass return value parameter into lambda method.
        // bool openDeeplink = (openDeeplinkString == "true");
        adjustConfig->setDeferredDeeplinkCallback([](std::string deeplink) {
            CCLOG("\n[AdjustCommandExecutor]: Deferred deep link received: %s", deeplink.c_str());
            TestLib2dx::addInfoToSend("deeplink", deeplink);
            TestLib2dx::sendInfoToServer(localBasePath);
            return true;
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

    AdjustConfig2dx *adjustConfig = this->savedConfigs[configNumber];
    Adjust2dx::start(*adjustConfig);
    this->savedConfigs.erase(0);
}

void AdjustCommandExecutor::event() {
    int eventNumber = 0;
    if (this->command->containsParameter("eventName")) {
        std::string eventName = command->getFirstParameterValue("eventName");
        std::string eventNumberStr = eventName.substr (eventName.length() - 1, 1);
        eventNumber = std::stoi(eventNumberStr);
    }

    AdjustEvent2dx *adjustEvent;
    if (this->savedEvents.count(eventNumber) > 0) {
        adjustEvent = this->savedEvents[eventNumber];
    } else {
        std::string eventToken = command->getFirstParameterValue("eventToken");

        adjustEvent = new AdjustEvent2dx(eventToken);
        savedEvents[eventNumber] = adjustEvent;
    }

    if (this->command->containsParameter("revenue")) {
        std::vector<std::string> revenueParams = command->getParameters("revenue");
        std::string currency = revenueParams[0];
        double revenue = std::stod(revenueParams[1]);
        adjustEvent->setRevenue(revenue, currency);
    }

    if (this->command->containsParameter("callbackParams")) {
        std::vector<std::string> callbackParams = command->getParameters("callbackParams");
        for (int i = 0; i < callbackParams.size(); i = i + 2) {
            std::string key = callbackParams[i];
            std::string value = callbackParams[i + 1];
            adjustEvent->addCallbackParameter(key, value);
        }
    }

    if (this->command->containsParameter("partnerParams")) {
        std::vector<std::string> partnerParams = command->getParameters("partnerParams");
        for (int i = 0; i < partnerParams.size(); i = i + 2) {
            std::string key = partnerParams[i];
            std::string value = partnerParams[i + 1];
            adjustEvent->addPartnerParameter(key, value);
        }
    }

    if (this->command->containsParameter("orderId")) {
        std::string orderId = command->getFirstParameterValue("orderId");
        adjustEvent->setTransactionId(orderId);
    }

    if (this->command->containsParameter("callbackId")) {
        std::string callbackId = command->getFirstParameterValue("callbackId");
        adjustEvent->setCallbackId(callbackId);
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

    AdjustEvent2dx *adjustEvent = this->savedEvents[eventNumber];
    Adjust2dx::trackEvent(*adjustEvent);
    this->savedEvents.erase(0);
}

void AdjustCommandExecutor::resume() {
    Adjust2dx::onResume();
}

void AdjustCommandExecutor::pause() {
    Adjust2dx::onPause();
}

void AdjustCommandExecutor::setEnabled() {
    std::string enabledStr = command->getFirstParameterValue("enabled");
    bool enabled = (enabledStr == "true");
    Adjust2dx::setEnabled(enabled);
}

void AdjustCommandExecutor::setReferrer() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string referrer = command->getFirstParameterValue("referrer");
    Adjust2dx::setReferrer(referrer);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    // No referrer in iOS.
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
    // No referrer in iOS.
#endif
}

void AdjustCommandExecutor::gdprForgetMe() {
    Adjust2dx::gdprForgetMe();
}
