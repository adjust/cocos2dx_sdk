//
//  AdjustCommandExecutor.cpp
//  Adjust SDK
//
//  Created by Srdjan Tubin (@2beens) on 4th June 2018.
//  Copyright © 2018-2020 Adjust GmbH. All rights reserved.
//

#define COCOS2D_DEBUG 1

#include <regex>
#include <base/CCConsole.h>
#include <platform/CCStdC.h>
#include <sstream>
#include "AdjustCommandExecutor.h"

static std::string localBasePath;
const std::string AdjustCommandExecutor::TAG = "AdjustCommandExecutor";

AdjustCommandExecutor::AdjustCommandExecutor(std::string urlOverwrite) {
    this->urlOverwrite = urlOverwrite;
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
    } else if (command->methodName == "addGlobalCallbackParameter") {
        this->addGlobalCallbackParameter();
    } else if (command->methodName == "addGlobalPartnerParameter") {
        this->addGlobalPartnerParameter();
    } else if (command->methodName == "removeGlobalCallbackParameter") {
        this->removeGlobalCallbackParameter();
    } else if (command->methodName == "removeGlobalPartnerParameter") {
        this->removeGlobalPartnerParameter();
    } else if (command->methodName == "removeGlobalCallbackParameters") {
        this->removeGlobalCallbackParameters();
    } else if (command->methodName == "removeGlobalPartnerParameters") {
        this->removeGlobalPartnerParameters();
    } else if (command->methodName == "setPushToken") {
        this->setPushToken();
    } else if (command->methodName == "openDeeplink") {
        this->openDeeplink();
    } else if (command->methodName == "sendReferrer") {
        this->sendReferrer();
    } else if (command->methodName == "gdprForgetMe") {
        this->gdprForgetMe();
    } else if (command->methodName == "trackSubscription") {
        this->trackSubscription();
    } else if (command->methodName == "thirdPartySharing") {
        this->trackThirdPartySharing();
    } else if (command->methodName == "measurementConsent") {
        this->trackMeasurementConsent();
    } else if (command->methodName == "trackAdRevenue") {
        this->trackAdRevenue();
    } else if (command->methodName == "getLastDeeplink") {
        this->getLastDeeplink();
    } else if (command->methodName == "verifyPurchase") {
        this->verifyPurchase();
    } else if (command->methodName == "verifyTrack") {
        this->verifyTrack();
    } else if (command->methodName == "processDeeplink") {
        this->processDeeplink();
    } else if (command->methodName == "attributionGetter") {
        this->attributionGetter();
    }
}

void AdjustCommandExecutor::testOptions() {
    std::map<std::string, std::string> stringTestOptions;
    std::map<std::string, int> intTestOptions;

    stringTestOptions["testUrlOverwrite"] = this->urlOverwrite;

    if (this->command->containsParameter("basePath")) {
        this->basePath = command->getFirstParameterValue("basePath");
    }
    if (this->command->containsParameter("timerInterval")) {
        intTestOptions["timerIntervalInMilliseconds"] = std::stoi(command->getFirstParameterValue("timerInterval"));
    }
    if (this->command->containsParameter("timerStart")) {
        intTestOptions["timerStartInMilliseconds"] = std::stoi(command->getFirstParameterValue("timerStart"));
    }
    if (this->command->containsParameter("sessionInterval")) {
        intTestOptions["sessionIntervalInMilliseconds"] = std::stoi(command->getFirstParameterValue("sessionInterval"));
    }
    if (this->command->containsParameter("subsessionInterval")) {
        intTestOptions["subsessionIntervalInMilliseconds"] = std::stoi(command->getFirstParameterValue("subsessionInterval"));
    }
    if (this->command->containsParameter("attStatus")) {
        intTestOptions["attStatusInt"] = std::stoi(command->getFirstParameterValue("attStatus"));
    }

    if (this->command->containsParameter("idfa")) {
        stringTestOptions["idfa"] = command->getFirstParameterValue("idfa");
    }

    if (this->command->containsParameter("noBackoffWait")) {
        if (command->getFirstParameterValue("noBackoffWait") == "true") {
            intTestOptions["noBackoffWait"] = 1;
        } else {
            intTestOptions["noBackoffWait"] = 0;
        }
    }
    // "false" is default value - AdServices will not be used in test app by default.
    intTestOptions["adServicesFrameworkEnabled"] = 0;
    if (this->command->containsParameter("adServicesFrameworkEnabled")) {
        if (command->getFirstParameterValue("adServicesFrameworkEnabled") == "true") {
            intTestOptions["adServicesFrameworkEnabled"] = 1;
        }
    }

    bool useTestConnectionOptions = false;

    if (this->command->containsParameter("teardown")) {
        std::vector<std::string> teardownOptions = command->getParameters("teardown");
        std::vector<std::string>::iterator toIterator = teardownOptions.begin();
        while(toIterator != teardownOptions.end()) {
            std::string teardownOption = (*toIterator);
            if (teardownOption == "resetSdk") {
                intTestOptions["teardown"] = 1;
                stringTestOptions["extraPath"] = this->basePath;
                // Android specific.
                useTestConnectionOptions = true;
                intTestOptions["tryInstallReferrer"] = 0;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                Adjust2dx::teardown();
#endif
            }
            if (teardownOption == "deleteState") {
                // Android specific.
                intTestOptions["setContext"] = 1;
                // iOS specific.
                intTestOptions["deleteState"] = 1;
            }
            if (teardownOption == "resetTest") {
                savedEvents.clear();
                savedConfigs.clear();
                intTestOptions["timerIntervalInMilliseconds"] = -1000;
                intTestOptions["timerStartInMilliseconds"] = -1000;
                intTestOptions["sessionIntervalInMilliseconds"] = -1000;
                intTestOptions["subsessionIntervalInMilliseconds"] = -1000;
            }
            if (teardownOption == "sdk") {
                intTestOptions["teardown"] = 1;
                stringTestOptions.erase("extraPath");
                // Android specific.
                intTestOptions["useTestConnectionOptions"] = 0;
            }
            if (teardownOption == "test") {
                savedEvents.clear();
                savedConfigs.clear();
                this->basePath = "";
                intTestOptions["timerIntervalInMilliseconds"] = -1000;
                intTestOptions["timerStartInMilliseconds"] = -1000;
                intTestOptions["sessionIntervalInMilliseconds"] = -1000;
                intTestOptions["subsessionIntervalInMilliseconds"] = -1000;
            }
            toIterator++;
        }
    }

    Adjust2dx::setTestOptions(stringTestOptions, intTestOptions);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (useTestConnectionOptions == true) {
        TestConnectionOptions2dx::setTestConnectionOptions();
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#endif
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

    if (this->command->containsParameter("checkPasteboard")) {
        std::string checkPasteboardString = command->getFirstParameterValue("checkPasteboard");
        bool checkPasteboard = (checkPasteboardString == "true");
        if (checkPasteboard) {
            adjustConfig->enableLinkMe();
        }
    }

    if (this->command->containsParameter("skanCallback")) {
        localBasePath = this->basePath;
        adjustConfig->setSkanUpdatedWithConversionDataCallback([](std::unordered_map<std::string, std::string> data) {
            CCLOG("\n[AdjustCommandExecutor]: Skan Updated received");

            for (std::unordered_map<std::string, std::string>::iterator toIterator = data.begin();
                 toIterator != data.end(); toIterator++)
            {
                TestLib2dx::addInfoToSend(toIterator->first, toIterator->second);

            }
            TestLib2dx::sendInfoToServer(localBasePath);
        });
    }

    if (this->command->containsParameter("attConsentWaitingSeconds")) {
        std::string attConsentWaitingSecondsString = command->getFirstParameterValue("attConsentWaitingSeconds");
        adjustConfig->setAttConsentWaitingInterval(std::stoi(attConsentWaitingSecondsString));
    }

    if (this->command->containsParameter("eventDeduplicationIdsMaxSize")) {
        std::string eventDeduplicationIdsMaxSizeString = command->getFirstParameterValue("eventDeduplicationIdsMaxSize");
        adjustConfig->setEventDeduplicationIdsMaxSize(std::stoi(eventDeduplicationIdsMaxSizeString));
    }

    if (this->command->containsParameter("coppaCompliant")) {
        std::string coppaCompliantString = command->getFirstParameterValue("coppaCompliant");
        bool coppaCompliant = (coppaCompliantString == "true");
        if (coppaCompliant) {
            adjustConfig->enableCoppaCompliance();
        }
    }

    if (this->command->containsParameter("needsCost")) {
        std::string needsCostString = command->getFirstParameterValue("needsCost");
        bool needsCost = (needsCostString == "true");
        if (needsCost) {
            adjustConfig->enableCostDataInAttribution();
        }
    }

    if (this->command->containsParameter("allowIdfaReading")) {
        std::string allowIdfaReadingString = command->getFirstParameterValue("allowIdfaReading");
        bool allowIdfaReading = (allowIdfaReadingString == "true");
        if (! allowIdfaReading) {
            adjustConfig->disableIdfaReading();
        }
    }

    if (this->command->containsParameter("allowAdServicesInfoReading")) {
        std::string allowAdServicesInfoReadingString = command->getFirstParameterValue("allowAdServicesInfoReading");
        bool allowAdServicesInfoReading = (allowAdServicesInfoReadingString == "true");
        if (! allowAdServicesInfoReading) {
            adjustConfig->disableAdServices();
        }
    }

    if (this->command->containsParameter("allowSkAdNetworkHandling")) {
        std::string allowSkAdNetworkHandlingString = command->getFirstParameterValue("allowSkAdNetworkHandling");
        bool allowSkAdNetworkHandling = (allowSkAdNetworkHandlingString == "true");
        if (allowSkAdNetworkHandling == false) {
            adjustConfig->disableSkanAttribution();
        }
    }

    if (this->command->containsParameter("sendInBackground")) {
        std::string sendInBackgroundString = command->getFirstParameterValue("sendInBackground");
        bool sendInBackground = (sendInBackgroundString == "true");
        if (sendInBackground) {
            adjustConfig->enableSendingInBackground();
        }
    }

    if (this->command->containsParameter("defaultTracker")) {
        std::string defaultTracker = command->getFirstParameterValue("defaultTracker");
        adjustConfig->setDefaultTracker(defaultTracker);
    }

    if (this->command->containsParameter("externalDeviceId")) {
        std::string externalDeviceId = command->getFirstParameterValue("externalDeviceId");
        adjustConfig->setExternalDeviceId(externalDeviceId);
    }

    if (this->command->containsParameter("playStoreKids")) {
        std::string playStoreKidsString = command->getFirstParameterValue("playStoreKids");
        if (playStoreKidsString == "true") {
            adjustConfig->enablePlayStoreKidsCompliance();
        }
    }

    if (this->command->containsParameter("attributionCallbackSendAll")) {
        localBasePath = this->basePath;
        adjustConfig->setAttributionCallback([](AdjustAttribution2dx attribution) {
            CCLOG("\n[AdjustCommandExecutor]: Attribution received: %s", attribution.getTrackerToken().c_str());
            TestLib2dx::addInfoToSend("tracker_token", attribution.getTrackerToken());
            TestLib2dx::addInfoToSend("tracker_name", attribution.getTrackerName());
            TestLib2dx::addInfoToSend("network", attribution.getNetwork());
            TestLib2dx::addInfoToSend("campaign", attribution.getCampaign());
            TestLib2dx::addInfoToSend("adgroup", attribution.getAdgroup());
            TestLib2dx::addInfoToSend("creative", attribution.getCreative());
            TestLib2dx::addInfoToSend("click_label", attribution.getClickLabel());
            TestLib2dx::addInfoToSend("cost_type", attribution.getCostType());
            std::ostringstream sstream;
            sstream << attribution.getCostAmount();
            std::string strCostAmount = sstream.str();
            TestLib2dx::addInfoToSend("cost_amount", strCostAmount);
            TestLib2dx::addInfoToSend("cost_currency", attribution.getCostCurrency());
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            TestLib2dx::addInfoToSend("fb_install_referrer", attribution.getFbInstallReferrer());
#endif
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

    if (this->command->containsParameter("transactionId")) {
        std::string transactionId = command->getFirstParameterValue("transactionId");
        adjustEvent->setTransactionId(transactionId);
    }

    if (this->command->containsParameter("productId")) {
        std::string productId = command->getFirstParameterValue("productId");
        adjustEvent->setProductId(productId);
    }

    if (this->command->containsParameter("deduplicationId")) {
        std::string deduplicationId = command->getFirstParameterValue("deduplicationId");
        adjustEvent->setDeduplicationId(deduplicationId);
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
    if (enabled) {
        Adjust2dx::enable();
    } else {
        Adjust2dx::disable();
    }
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
    if (enabled) {
        Adjust2dx::switchToOfflineMode();
    } else {
        Adjust2dx::switchBackToOnlineMode();
    }
}

void AdjustCommandExecutor::addGlobalCallbackParameter() {
    if (this->command->containsParameter("KeyValue")) {
        std::vector<std::string> keyValuePairs = command->getParameters("KeyValue");
        for (int i = 0; i < keyValuePairs.size(); i = i + 2) {
            std::string key = keyValuePairs[i];
            std::string value = keyValuePairs[i + 1];
            Adjust2dx::addGlobalCallbackParameter(key, value);
        }
    }
}

void AdjustCommandExecutor::addGlobalPartnerParameter() {
    if (this->command->containsParameter("KeyValue")) {
        std::vector<std::string> keyValuePairs = command->getParameters("KeyValue");
        for (int i = 0; i < keyValuePairs.size(); i = i + 2) {
            std::string key = keyValuePairs[i];
            std::string value = keyValuePairs[i + 1];
            Adjust2dx::addGlobalPartnerParameter(key, value);
        }
    }
}

void AdjustCommandExecutor::removeGlobalCallbackParameter() {
    if (this->command->containsParameter("key")) {
        std::vector<std::string> keys = command->getParameters("key");
        for (int i = 0; i < keys.size(); i++) {
            std::string key = keys[i];
            Adjust2dx::removeGlobalCallbackParameter(key);
        }
    }
}

void AdjustCommandExecutor::removeGlobalPartnerParameter() {
    if (this->command->containsParameter("key")) {
        std::vector<std::string> keys = command->getParameters("key");
        for (int i = 0; i < keys.size(); i++) {
            std::string key = keys[i];
            Adjust2dx::removeGlobalPartnerParameter(key);
        }
    }
}

void AdjustCommandExecutor::removeGlobalCallbackParameters() {
    Adjust2dx::removeGlobalCallbackParameters();
}

void AdjustCommandExecutor::removeGlobalPartnerParameters() {
    Adjust2dx::removeGlobalPartnerParameters();
}

void AdjustCommandExecutor::setPushToken() {
    std::string token = command->getFirstParameterValue("pushToken");
    Adjust2dx::setPushTokenAsString(token);
}

void AdjustCommandExecutor::openDeeplink() {
    std::string deeplink = command->getFirstParameterValue("deeplink");
    Adjust2dx::processDeeplink(deeplink);
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

void AdjustCommandExecutor::trackSubscription() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    std::string price = command->getFirstParameterValue("revenue");
    std::string currency = command->getFirstParameterValue("currency");
    std::string transactionId = command->getFirstParameterValue("transactionId");
    std::string transactionDate = command->getFirstParameterValue("transactionDate");
    std::string salesRegion = command->getFirstParameterValue("salesRegion");

    AdjustAppStoreSubscription2dx subscription = AdjustAppStoreSubscription2dx(
        price,
        currency,
        transactionId);
    subscription.setTransactionDate(transactionDate);
    subscription.setSalesRegion(salesRegion);

    if (this->command->containsParameter("callbackParams")) {
        std::vector<std::string> callbackParams = command->getParameters("callbackParams");
        for (int i = 0; i < callbackParams.size(); i = i + 2) {
            std::string key = callbackParams[i];
            std::string value = callbackParams[i + 1];
            subscription.addCallbackParameter(key, value);
        }
    }

    if (this->command->containsParameter("partnerParams")) {
        std::vector<std::string> partnerParams = command->getParameters("partnerParams");
        for (int i = 0; i < partnerParams.size(); i = i + 2) {
            std::string key = partnerParams[i];
            std::string value = partnerParams[i + 1];
            subscription.addPartnerParameter(key, value);
        }
    }

    Adjust2dx::trackAppStoreSubscription(subscription);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string price = command->getFirstParameterValue("revenue");
    std::string currency = command->getFirstParameterValue("currency");
    std::string sku = command->getFirstParameterValue("productId");
    std::string orderId = command->getFirstParameterValue("transactionId");
    std::string signature = command->getFirstParameterValue("receipt");
    std::string purchaseToken = command->getFirstParameterValue("purchaseToken");
    std::string purchaseTime = command->getFirstParameterValue("transactionDate");

    AdjustPlayStoreSubscription2dx subscription = AdjustPlayStoreSubscription2dx(
        price,
        currency,
        sku,
        orderId,
        signature,
        purchaseToken
    );
    subscription.setPurchaseTime(purchaseTime);

    if (this->command->containsParameter("callbackParams")) {
        std::vector<std::string> callbackParams = command->getParameters("callbackParams");
        for (int i = 0; i < callbackParams.size(); i = i + 2) {
            std::string key = callbackParams[i];
            std::string value = callbackParams[i + 1];
            subscription.addCallbackParameter(key, value);
        }
    }

    if (this->command->containsParameter("partnerParams")) {
        std::vector<std::string> partnerParams = command->getParameters("partnerParams");
        for (int i = 0; i < partnerParams.size(); i = i + 2) {
            std::string key = partnerParams[i];
            std::string value = partnerParams[i + 1];
            subscription.addPartnerParameter(key, value);
        }
    }

    Adjust2dx::trackPlayStoreSubscription(subscription);
#endif
}

void AdjustCommandExecutor::trackThirdPartySharing() {
    std::string enabled = command->getFirstParameterValue("isEnabled");
    AdjustThirdPartySharing2dx thirdPartySharing;
    if (enabled.empty()) {
        thirdPartySharing = AdjustThirdPartySharing2dx();
    } else {
        thirdPartySharing = AdjustThirdPartySharing2dx(enabled == "true" ? true : false);
    }

    if (this->command->containsParameter("granularOptions")) {
        std::vector<std::string> granularOptions = command->getParameters("granularOptions");
        for (int i = 0; i < granularOptions.size(); i = i + 3) {
            std::string partnerName = granularOptions[i];
            std::string key = granularOptions[i + 1];
            std::string value = granularOptions[i + 2];
            // Hack around null/undefined handling of json parsing
            if (partnerName.empty() || key.empty() || value.empty()) {
                continue;
            }
            thirdPartySharing.addGranularOption(partnerName, key, value);
        }
    }

    if (this->command->containsParameter("partnerSharingSettings")) {
        std::vector<std::string> partnerSharingSettings = command->getParameters("partnerSharingSettings");
        for (int i = 0; i < partnerSharingSettings.size(); i = i + 3) {
            std::string partnerName = partnerSharingSettings[i];
            std::string key = partnerSharingSettings[i + 1];
            bool value = (partnerSharingSettings[i + 2] == "true");
            // Hack around null/undefined handling of json parsing
            if (partnerName.empty() || key.empty()) {
                continue;
            }
            thirdPartySharing.addPartnerSharingSetting(partnerName, key, value);
        }
    }

    Adjust2dx::trackThirdPartySharing(thirdPartySharing);
}

void AdjustCommandExecutor::trackMeasurementConsent() {
    std::string enabled = command->getFirstParameterValue("isEnabled");
    Adjust2dx::trackMeasurementConsent(enabled == "true" ? true : false);
}

void AdjustCommandExecutor::trackAdRevenue() {
    std::string source = command->getFirstParameterValue("adRevenueSource");
    AdjustAdRevenue2dx *adjustAdRevenue = new AdjustAdRevenue2dx(source);

    if (this->command->containsParameter("revenue")) {
        std::vector<std::string> revenueParams = command->getParameters("revenue");
        std::string currency = revenueParams[0];
        double revenue = std::stod(revenueParams[1]);
        adjustAdRevenue->setRevenue(revenue, currency);
    }

    if (this->command->containsParameter("callbackParams")) {
        std::vector<std::string> callbackParams = command->getParameters("callbackParams");
        for (int i = 0; i < callbackParams.size(); i = i + 2) {
            std::string key = callbackParams[i];
            std::string value = callbackParams[i + 1];
            adjustAdRevenue->addCallbackParameter(key, value);
        }
    }

    if (this->command->containsParameter("partnerParams")) {
        std::vector<std::string> partnerParams = command->getParameters("partnerParams");
        for (int i = 0; i < partnerParams.size(); i = i + 2) {
            std::string key = partnerParams[i];
            std::string value = partnerParams[i + 1];
            adjustAdRevenue->addPartnerParameter(key, value);
        }
    }

    if (this->command->containsParameter("adImpressionsCount")) {
        int adImpressionsCount = std::stoi(command->getFirstParameterValue("adImpressionsCount"));
        adjustAdRevenue->setAdImpressionsCount(adImpressionsCount);
    }

    if (this->command->containsParameter("adRevenueNetwork")) {
        std::string adRevenueNetwork = command->getFirstParameterValue("adRevenueNetwork");
        adjustAdRevenue->setAdRevenueNetwork(adRevenueNetwork);
    }

    if (this->command->containsParameter("adRevenueUnit")) {
        std::string adRevenueUnit = command->getFirstParameterValue("adRevenueUnit");
        adjustAdRevenue->setAdRevenueUnit(adRevenueUnit);
    }

    if (this->command->containsParameter("adRevenuePlacement")) {
        std::string adRevenuePlacement = command->getFirstParameterValue("adRevenuePlacement");
        adjustAdRevenue->setAdRevenuePlacement(adRevenuePlacement);
    }

    Adjust2dx::trackAdRevenue(*adjustAdRevenue);
}

void AdjustCommandExecutor::getLastDeeplink() {
    localBasePath = this->basePath;
    Adjust2dx::lastDeeplinkCallback([](std::string lastDeeplink) {
        TestLib2dx::addInfoToSend("last_deeplink", lastDeeplink);
        TestLib2dx::sendInfoToServer(localBasePath);
    });
}

void AdjustCommandExecutor::verifyPurchase() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    std::string productId = command->getFirstParameterValue("productId");
    std::string transactionId = command->getFirstParameterValue("transactionId");

    AdjustAppStorePurchase2dx purchase =
        AdjustAppStorePurchase2dx(productId, transactionId);

    localBasePath = this->basePath;
    Adjust2dx::verifyAppStorePurchase(purchase, [](std::string verificationStatus, int code, std::string message) {
        TestLib2dx::addInfoToSend("verification_status", verificationStatus);
        TestLib2dx::addInfoToSend("code", std::to_string(code));
        TestLib2dx::addInfoToSend("message", message);
        TestLib2dx::sendInfoToServer(localBasePath);
    });
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string productId = command->getFirstParameterValue("productId");
    std::string purchaseToken = command->getFirstParameterValue("purchaseToken");

    AdjustPlayStorePurchase2dx purchase = AdjustPlayStorePurchase2dx(productId, purchaseToken);

    localBasePath = this->basePath;
    Adjust2dx::verifyPlayStorePurchase(purchase, [](std::string verificationStatus, int code, std::string message) {
        TestLib2dx::addInfoToSend("verification_status", verificationStatus);
        TestLib2dx::addInfoToSend("code", std::to_string(code));
        TestLib2dx::addInfoToSend("message", message);
        TestLib2dx::sendInfoToServer(localBasePath);
    });
#endif
}

void AdjustCommandExecutor::verifyTrack() {
    event();
    int eventNumber = 0;
    if (this->command->containsParameter("eventName")) {
        std::string eventName = command->getFirstParameterValue("eventName");
        std::string eventNameStr = eventName.substr (eventName.length() - 1, 1);
        eventNumber = std::stoi(eventNameStr);
    }

    AdjustEvent2dx *adjustEvent = this->savedEvents[eventNumber];

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    localBasePath = this->basePath;

    Adjust2dx::verifyAndTrackAppStorePurchase(*adjustEvent, [](std::string verificationStatus, int code, std::string message) {
        TestLib2dx::addInfoToSend("verification_status", verificationStatus);
        TestLib2dx::addInfoToSend("code", std::to_string(code));
        TestLib2dx::addInfoToSend("message", message);
        TestLib2dx::sendInfoToServer(localBasePath);
    });
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string productId = command->getFirstParameterValue("productId");
    std::string purchaseToken = command->getFirstParameterValue("purchaseToken");

    AdjustPlayStorePurchase2dx purchase = AdjustPlayStorePurchase2dx(productId, purchaseToken);

    localBasePath = this->basePath;
    Adjust2dx::verifyPlayStorePurchase(purchase, [](std::string verificationStatus, int code, std::string message) {
        TestLib2dx::addInfoToSend("verification_status", verificationStatus);
        TestLib2dx::addInfoToSend("code", std::to_string(code));
        TestLib2dx::addInfoToSend("message", message);
        TestLib2dx::sendInfoToServer(localBasePath);
    });
#endif

    this->savedEvents.erase(0);
}

void AdjustCommandExecutor::processDeeplink() {
    std::string deeplink = command->getFirstParameterValue("deeplink");
    localBasePath = this->basePath;
    Adjust2dx::processAndResolveDeeplink(deeplink, [](std::string resolvedLink) {
        TestLib2dx::addInfoToSend("resolved_link", resolvedLink);
        TestLib2dx::sendInfoToServer(localBasePath);
    });
}

void AdjustCommandExecutor::attributionGetter() {
    localBasePath = this->basePath;
    Adjust2dx::attributionCallback([](AdjustAttribution2dx attribution) {
        TestLib2dx::addInfoToSend("tracker_token", attribution.getTrackerToken());
        TestLib2dx::addInfoToSend("tracker_name", attribution.getTrackerName());
        TestLib2dx::addInfoToSend("network", attribution.getNetwork());
        TestLib2dx::addInfoToSend("campaign", attribution.getCampaign());
        TestLib2dx::addInfoToSend("adgroup", attribution.getAdgroup());
        TestLib2dx::addInfoToSend("creative", attribution.getCreative());
        TestLib2dx::addInfoToSend("click_label", attribution.getClickLabel());
        TestLib2dx::addInfoToSend("cost_type", attribution.getCostType());
        std::ostringstream sstream;
        sstream << attribution.getCostAmount();
        std::string strCostAmount = sstream.str();
        TestLib2dx::addInfoToSend("cost_amount", strCostAmount);
        TestLib2dx::addInfoToSend("cost_currency", attribution.getCostCurrency());
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        TestLib2dx::addInfoToSend("fb_install_referrer", attribution.getFbInstallReferrer());
#endif
        TestLib2dx::sendInfoToServer(localBasePath);
    });
}
