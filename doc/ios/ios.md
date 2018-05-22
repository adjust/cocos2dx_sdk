## Summary

This is the Cocos2d-x SDK of Adjust™. You can read more about Adjust™ at [Adjust.com].

## Table of contents

* [Basic integration](#basic-integration)
   * [Get the SDK](#sdk-get)
   * [Add the SDK to your project](#sdk-add)
   * [Add the frameworks to your project](#sdk-frameworks)
   * [Add additional linker flags](#sdk-linker-flags)
   * [Integrate the SDK into your app](#sdk-integrate)
   * [Adjust logging](#sdk-logging)
   * [Build your app](#sdk-build)
* [Additional features](#additional-features)
   * [Event tracking](#event-tracking)
      * [Revenue tracking](#revenue-tracking)
      * [Revenue deduplication](#revenue-deduplication)
      * [In-app purchase verification](#iap-verification)
      * [Callback parameters](#callback-parameters)
      * [Partner parameters](#partner-parameters)
   * [Session parameters](#session-parameters)
      * [Session callback parameters](#session-callback-parameters)
      * [Session partner parameters](#session-partner-parameters)
      * [Delay start](#delay-start)
   * [Attribution callback](#attribution-callback)
   * [Session and event callbacks](#session-event-callbacks)
   * [Disable tracking](#disable-tracking)
   * [Offline mode](#offline-mode)
   * [Event buffering](#event-buffering)
   * [GDPR right to be forgotten](#gdpr-forget-me)
   * [SDK signature](#sdk-signature)
   * [Background tracking](#background-tracking)
   * [Device IDs](#device-ids)
      * [iOS advertising identifier](#di-idfa)
      * [Adjust device identifier](#di-adid)
      * [User attribution](#user-attribution)
   * [Push token](#push-token)
   * [Pre-installed trackers](#pre-installed-trackers)
   * [Deep linking](#deeplinking)
      * [Standard deep linking](#deeplinking-standard)
      * [Deferred deep linking](#deeplinking-deferred)
      * [Deep link handling for iOS apps](#deeplinking-ios)
* [License](#license)

## <a id="basic-integration"></a>Basic integration

How to integrate the Adjust SDK into your Cocos2d-x iOS project.

### <a id="sdk-get"></a>Get the SDK

Download the latest version from our [releases page][releases]. Extract the archive into a directory of your choosing.

### <a id="sdk-add"></a>Add the SDK to your project

Take the files from the `Adjust` folder and add them to your iOS project.

![][add-ios-files]

### <a id="sdk-frameworks"></a>Add the frameworks to your project

You need to add the AdjustSdk, AdSupport, iAd and CoreTelephony frameworks to your project.

Before adding the `AdjustSdk.framework` to your project, ensure that you first copy it into the `proj.ios_mac/ios` folder of your project.

Select your project in the Project Navigator. In the left-hand side of the main view, select your target. In the `Build Phases` tab, expand the `Link Binary With Libraries` group. At the bottom of that section, click the `+` button, select the `AdjustSdk.framework` and click the `Add` button. Repeat these steps to add the `AdSupport.framework`, `iAd.framework` and `CoreTelephony.framework`.

![][add-the-frameworks]

### <a id="sdk-linker-flags"></a>Add additional linker flags

In order to support categories from the `AdjustSdk.framework`, you should add a linker flag. Go to the `Build Settings` part of Project Settings and look for the `Other Linker Flags` option. Add an `-ObjC` flag to it.

![][add-other-linker-flags]

### <a id="sdk-integrate"></a>Integrate the SDK into your app

In the Project Navigator, open the source file of your application delegate. Add the import statement at the top of the file, then add the following call to Adjust in the `applicationDidFinishLaunching` method of your app delegate:

```cpp
#include "Adjust/Adjust2dx.h"
// ...
std::string appToken = "{YourAppToken}";
std::string environment = AdjustEnvironmentSandbox2dx;

AdjustConfig2dx adjustConfig = AdjustConfig2dx(appToken, environment);

Adjust2dx::start(adjustConfig);
```

![][add-adjust2dx]

Replace `{YourAppToken}` with your app token. You can find this in your [dashboard].

Depending on whether you are building your app for testing or for production, you must set `environment` with one of these values:

```cpp
std::string environment = AdjustEnvironmentSandbox2dx;
std::string environment = AdjustEnvironmentProduction2dx;
```

**Important:** This value should only ever be set to `AdjustEnvironmentSandbox2dx` if you or someone else is testing your app. Make sure to set the environment to `AdjustEnvironmentProduction2dx` before you publish your app. Set it back to `AdjustEnvironmentSandbox2dx` again when you start developing and testing your app.

We use this environment to distinguish between real traffic and test traffic from test devices. It is imperative that you keep this value meaningful at all times, especially if you are tracking revenue.

### <a id="sdk-logging"></a>Adjust logging

You can increase or decrease the amount of logs you see in tests by calling `setLogLevel` on your `AdjustConfig2dx` instance with one of the following parameters:

```cpp
adjustConfig.setLogLevel(AdjustLogLevel2dxVerbose);     // enable all logging
adjustConfig.setLogLevel(AdjustLogLevel2dxDebug);       // enable more logging
adjustConfig.setLogLevel(AdjustLogLevel2dxInfo);        // the default
adjustConfig.setLogLevel(AdjustLogLevel2dxWarn);        // disable info logging
adjustConfig.setLogLevel(AdjustLogLevel2dxError);       // disable warnings as well
adjustConfig.setLogLevel(AdjustLogLevel2dxAssert);      // disable errors as well
adjustConfig.setLogLevel(AdjustLogLevel2dxSuppress);    // disable all log output
```

If you want to use the `suppress` log level, you should initialize the `AdjustConfig2dx` instance with the usage of a constructor that receives an additional `bool` parameter indicating whether the suppress log level should be enabled or not:

```cpp
std::string appToken = "{YourAppToken}";
std::string environment = AdjustEnvironmentSandbox2dx;

AdjustConfig2dx adjustConfig = AdjustConfig2dx(appToken, environment, true);
adjustConfig.setLogLevel(AdjustLogLevel2dxSuppress);
```

## <a id="sdk-build"></a>Build your app

Build and run your app. If the build is successful, carefully read through the SDK logs in the console. After the initial app launch, you should see an info log entry saying `Install tracked`.

![][run]

## <a id="additional-features"></a>Additional features

Once you integrate the Adjust SDK into your project, you can take advantage of the following features.

### <a id="event-tracking"></a>Event tracking

With Adjust, you can track any event that you want. 

Suppose you want to track every tap on a button. If you create a new event token in your [dashboard] - let's say that event token is `abc123` - you can add the following line in your button’s click handler method to track the click:

```cpp
AdjustEvent2dx adjustEvent = AdjustEvent2dx("abc123");
Adjust2dx::trackEvent(adjustEvent);
```

### <a id="revenue-tracking"></a>Revenue tracking

If your users can generate revenue by tapping on advertisements or making in-app purchases, then you can track that revenue through events. Let's say a tap is worth €0.01. You could track the revenue event like this:

```cpp
AdjustEvent2dx adjustEvent = AdjustEvent2dx("abc123");

adjustEvent.setRevenue(0.01, "EUR");

Adjust2dx::trackEvent(adjustEvent);
```

When you set a currency token, Adjust will automatically convert the incoming revenues into a reporting revenue of your choice. Read more about currency conversion [here][currency-conversion].

You can read more about revenue and event tracking in the [event tracking guide][event-tracking].

### <a id="revenue-deduplication"></a>Revenue deduplication

You can also add an optional transaction ID to avoid tracking duplicate revenues. The last ten transaction IDs are remembered, and revenue events with duplicate transaction IDs are skipped. This is especially useful for in-app purchase tracking. You can see an example below.

If you want to track in-app purchases, please make sure to call `trackEvent` only when the transaction has been completed. That way you can avoid tracking revenue that is not actually being generated.

```cpp
AdjustEvent2dx adjustEvent = AdjustEvent2dx("abc123");

adjustEvent.setRevenue(0.01, "EUR");
adjustEvent.setTransactionId("transactionID");

Adjust2dx::trackEvent(adjustEvent);
```

**Note**: Transaction ID is the iOS term; the unique identifier for successfully completed Android in-app purchases is **Order ID**.

### <a id="iap-verification"></a>In-app purchase verification

In-app purchase verification can be done with the Cocos2d-x purchase SDK, which is currently in development and will soon be made publicly available. For more information, please contact support@adjust.com.

### <a id="callback-parameters"></a>Callback parameters

You can register a callback URL for an event in your [dashboard]. We will send a GET request to that URL whenever the event is tracked. You can add callback parameters to an event by calling the `addCallbackParameter` method of the event before tracking it. We will then append these parameters to your callback URL.

For example, suppose you have registered the URL `http://www.adjust.com/callback` for your event with the event token `abc123`, and you execute the following lines:

```cpp
AdjustEvent2dx adjustEvent = AdjustEvent2dx("abc123");

adjustEvent.addCallbackParameter("key", "value");
adjustEvent.addCallbackParameter("foo", "bar");

Adjust2dx::trackEvent(adjustEvent);
```

In this case, we would track the event and send a request to:

```
http://www.adjust.com/callback?key=value&foo=bar
```

Adjust supports a variety of placeholders, like `{idfa}`, that can be used as parameter values. In the resulting callback, `{idfa}` would be replaced with the current device’s ID for Advertisers. Adjust does not store any of your custom parameters, but only appends them to your callbacks. If you haven't registered a callback for an event, these parameters won't even be read.

You can read more about using URL callbacks, including a full list of available values, in our [callbacks guide][callbacks-guide].

### <a id="partner-parameters"></a>Partner parameters

For any integrations that you have activated in your Adjust dashboard, you can add parameters to send to these network partners.

Partner parameters work similarly to the callback parameters mentioned above, but can be added by calling the `addPartnerParameter` method on your `AdjustEvent2dx` instance.

```cpp
AdjustEvent2dx adjustEvent = AdjustEvent2dx("abc123");

adjustEvent.addPartnerParameter("key", "value");
adjustEvent.addPartnerParameter("foo", "bar");

Adjust2dx::trackEvent(adjustEvent);
```

You can read more about special partners and how to integrate them in our [guide to special partners][special-partners].

### <a id="session-parameters"></a>Session parameters

Some parameters are saved to be sent in every event and session of the Adjust SDK. Once you have added any of these parameters, you don't need to add them again, since they will be saved locally. If you add the same parameter twice, there will be no effect.

These session parameters can be called before the Adjust SDK is launched to make sure they are sent even on install. If you need to send them with an install, but can only obtain the needed values after launch, it's possible to [delay](#delay-start) the first launch of the Adjust SDK to allow for this.

### <a id="session-callback-parameters"></a>Session callback parameters

You can save the same callback parameters that are registered for [events](#callback-parameters) to be sent in every event or session of the Adjust SDK.

Session callback parameters have a similar interface to event callback parameters, except that, instead of adding the key and its value to an event, they are added through a call to the `addSessionCallbackParameter` method of the `Adjust2dx` instance.

```cpp
Adjust2dx::addSessionCallbackParameter("foo", "bar");
```

Session callback parameters will be merged with the callback parameters you have added to an event. Callback parameters that have been added to an event take precedence over session callback parameters. If you add a callback parameter to an event with the same key as one added from the session, the callback parameter added to the event will prevail.

It's possible to remove a specific session callback parameter by passing the desired key to the `removeSessionCallbackParameter` method of the `Adjust2dx` instance.

```cpp
Adjust2dx::removeSessionCallbackParameter("foo");
```

If you wish to remove all keys and values from the session callback parameters, you can reset them with the `resetSessionCallbackParameters` method of the `Adjust2dx` instance.

```cpp
Adjust2dx::resetSessionCallbackParameters();
```

### <a id="session-partner-parameters"></a>Session partner parameters

In the same way that there are [session callback parameters](#session-callback-parameters) that are sent for every event or session of the Adjust SDK, there are also session partner parameters. These will be transmitted to any network partners that have been integrated and activated in your Adjust [dashboard].

Session partner parameters have a similar interface to event partner parameters, except that, instead of adding the key and its value to an event, they are added through a call to the `addSessionPartnerParameter` method of the `Adjust2dx` instance.

```cpp
Adjust2dx::addSessionPartnerParameter("foo", "bar");
```

Session partner parameters will be merged with the partner parameters that you have added to an event. The partner parameters that have been added to an event take precedence over session partner parameters. This means that if you add a partner parameter to an event with the same key as one added from the session, the partner parameter will prevail.

It is possible to remove a specific session partner parameter by passing the desired key to the `removeSessionPartnerParameter` method of the `Adjust2dx` instance.

```cpp
Adjust2dx::removeSessionPartnerParameter("foo");
```

If you wish to remove all keys and values from the session partner parameters, you can reset them with the `resetSessionPartnerParameters` method of the `Adjust2dx` instance.

```cpp
Adjust2dx::resetSessionPartnerParameters();
```

### <a id="delay-start"></a>Delay start

Delaying the start of the Adjust SDK allows your app some time to obtain session parameters, such as unique identifiers, so they can be sent upon install.

Set the initial delay time, in seconds, with the `setDelayStart` method of the `AdjustConfig2dx` instance:

```cpp
config.setDelayStart(5.5);
```

In this case, the Adjust SDK will wait 5.5 seconds before sending the initial install session and any events created. After this time has elapsed, or if you call `Adjust2dx::sendFirstPackages()` in the meantime, every session parameter will be added to the delayed install session and events, and the Adjust SDK will resume as usual.

**The maximum delay start time of the Adjust SDK is 10 seconds**.

### <a id="attribution-callback"></a>Attribution callback

Adjust can also send you a callback upon any change in attribution. Due to the different sources considered for attribution, this information cannot be provided synchronously. Follow these steps if you wish to implement the callback in your application:

1. Create a void method which receives an `AdjustAttribution2dx` parameter.

2. After creating an `AdjustConfig2dx` instance, call its `setAttributionCallback` method with the previously created method as a parameter.

The callback function will be called when the SDK receives the final attribution data. Within the callback function, you have access to the `attribution` parameter. Here is a quick summary of its properties:

- `std::string trackerToken` the tracker token of the current attribution.
- `std::string trackerName` the tracker name of the current attribution.
- `std::string network` the network grouping level of the current attribution.
- `std::string campaign` the campaign grouping level of the current attribution.
- `std::string adgroup` the ad group grouping level of the current attribution.
- `std::string creative` the creative grouping level of the current attribution.
- `std::string clickLabel` the click label of the current attribution.
- `std::string adid` the Adjust device identifier.

```cpp
#include "Adjust/Adjust2dx.h"

//...

static void attributionCallbackMethod(AdjustAttribution2dx attribution) {
    // Printing all attribution properties.
    CCLOG("\nAttribution changed!");
    CCLOG("\nTracker token: %s", attribution.getTrackerToken().c_str());
    CCLOG("\nTracker name: %s", attribution.getTrackerName().c_str());
    CCLOG("\nNetwork: %s", attribution.getNetwork().c_str());
    CCLOG("\nCampaign: %s", attribution.getCampaign().c_str());
    CCLOG("\nAdgroup: %s", attribution.getAdgroup().c_str());
    CCLOG("\nCreative: %s", attribution.getCreative().c_str());
    CCLOG("\nClick label: %s", attribution.getClickLabel().c_str());
    CCLOG("\nAdid: %s", attribution.getAdid().c_str());
    CCLOG("\n");
}

// ...

bool AppDelegate::applicationDidFinishLaunching() {
    std::string appToken = "{YourAppToken}";
    std::string environment = AdjustEnvironmentSandbox2dx;

    AdjustConfig2dx adjustConfig = AdjustConfig2dx(appToken, environment);
    adjustConfig.setLogLevel(AdjustLogLevel2dxVerbose);
    adjustConfig.setAttributionCallback(attributionCallbackMethod);

    Adjust2dx::start(adjustConfig);

    // ...
}
```

Please make sure to consider the [applicable attribution data policies][attribution-data].

### <a id="session-event-callbacks"></a>Session and event callbacks

You can register a callback to be notified of successfully tracked, as well as failed, events and/or sessions.

Follow the same steps as in the [attribution callback section above](#attribution-callback) to implement the following callback function for successfully tracked events:

```cpp
#include "Adjust/Adjust2dx.h"

//...

static void eventSuccessCallbackMethod(AdjustEventSuccess2dx eventSuccess) {
    CCLOG("\nEvent successfully tracked!");
    CCLOG("\nADID: %s", eventSuccess.getAdid().c_str());
    CCLOG("\nMessage: %s", eventSuccess.getMessage().c_str());
    CCLOG("\nTimestamp: %s", eventSuccess.getTimestamp().c_str());
    CCLOG("\nEvent token: %s", eventSuccess.getEventToken().c_str());
    CCLOG("\nJSON response: %s", eventSuccess.getJsonResponse().c_str());
    CCLOG("\n");
}

// ...

bool AppDelegate::applicationDidFinishLaunching() {
    std::string appToken = "{YourAppToken}";
    std::string environment = AdjustEnvironmentSandbox2dx;

    AdjustConfig2dx adjustConfig = AdjustConfig2dx(appToken, environment);
    adjustConfig.setLogLevel(AdjustLogLevel2dxVerbose);
    adjustConfig.setEventSuccessCallback(eventSuccessCallbackMethod);

    Adjust2dx::start(adjustConfig);

    // ...
}
```

The following callback function is used for failed events:

```cpp
#include "Adjust/Adjust2dx.h"

//...

static void eventFailureCallbackMethod(AdjustEventFailure2dx eventFailure) {
    CCLOG("\nEvent tracking failed!");
    CCLOG("\nADID: %s", eventFailure.getAdid().c_str());
    CCLOG("\nMessage: %s", eventFailure.getMessage().c_str());
    CCLOG("\nTimestamp: %s", eventFailure.getTimestamp().c_str());
    CCLOG("\nWill retry: %s", eventFailure.getWillRetry().c_str());
    CCLOG("\nEvent token: %s", eventFailure.getEventToken().c_str());
    CCLOG("\nJSON response: %s", eventFailure.getJsonResponse().c_str());
    CCLOG("\n");
}

// ...

bool AppDelegate::applicationDidFinishLaunching() {
    std::string appToken = "{YourAppToken}";
    std::string environment = AdjustEnvironmentSandbox2dx;

    AdjustConfig2dx adjustConfig = AdjustConfig2dx(appToken, environment);
    adjustConfig.setLogLevel(AdjustLogLevel2dxVerbose);
    adjustConfig.setEventFailureCallback(eventFailureCallbackMethod);

    Adjust2dx::start(adjustConfig);

    // ...
}
```

For successfully tracked sessions:

```cpp
#include "Adjust/Adjust2dx.h"

//...

static void sessionSuccessCallbackMethod(AdjustSessionSuccess2dx sessionSuccess) {
    CCLOG("\nSession successfully tracked!");
    CCLOG("\nADID: %s", sessionSuccess.getAdid().c_str());
    CCLOG("\nMessage: %s", sessionSuccess.getMessage().c_str());
    CCLOG("\nTimestamp: %s", sessionSuccess.getTimestamp().c_str());
    CCLOG("\nJSON response: %s", sessionSuccess.getJsonResponse().c_str());
    CCLOG("\n");
}

// ...

bool AppDelegate::applicationDidFinishLaunching() {
    std::string appToken = "{YourAppToken}";
    std::string environment = AdjustEnvironmentSandbox2dx;

    AdjustConfig2dx adjustConfig = AdjustConfig2dx(appToken, environment);
    adjustConfig.setLogLevel(AdjustLogLevel2dxVerbose);
    adjustConfig.setSessionSuccessCallback(sessionSuccessCallbackMethod);

    Adjust2dx::start(adjustConfig);

    // ...
}
```

And for session failures:

```cpp
#include "Adjust/Adjust2dx.h"

//...

static void sessionFailureCallbackMethod(AdjustSessionFailure2dx sessionFailure) {
    CCLOG("\nSession tracking failed!");
    CCLOG("\nADID: %s", sessionFailure.getAdid().c_str());
    CCLOG("\nMessage: %s", sessionFailure.getMessage().c_str());
    CCLOG("\nTimestamp: %s", sessionFailure.getTimestamp().c_str());
    CCLOG("\nWill retry: %s", sessionFailure.getWillRetry().c_str());
    CCLOG("\nJSON response: %s", sessionFailure.getJsonResponse().c_str());
    CCLOG("\n");
}

// ...

bool AppDelegate::applicationDidFinishLaunching() {
    std::string appToken = "{YourAppToken}";
    std::string environment = AdjustEnvironmentSandbox2dx;

    AdjustConfig2dx adjustConfig = AdjustConfig2dx(appToken, environment);
    adjustConfig.setLogLevel(AdjustLogLevel2dxVerbose);
    adjustConfig.setSessionFailureCallback(sessionFailureCallbackMethod);

    Adjust2dx::start(adjustConfig);

    // ...
}
```

The callback functions will be called after the SDK tries to send a package to the server. Within the callback, you have access to a response data object specifically for the callback. Here is a quick summary of the session response data properties:

- `std::string message` the message from the server or the error logged by the SDK.
- `std::string timestamp` timestamp from the server.
- `std::string adid` a unique device identifier provided by Adjust.
- `std::string jsonResponse` the JSON object with the response from the server.

Both event response data objects contain:

- `std::string eventToken` the event token, if the package tracked was an event.

And both event- and session-failed objects also contain:

- `std::string willRetry` indicates there will be an attempt to resend the package at a later time.

### <a id="disable-tracking"></a>Disable tracking

You can disable the Adjust SDK from tracking by invoking the `Adjust2dx::setEnabled` method with the enabled parameter set to `false`. This setting is **remembered between sessions**, but it can only be activated after the first session.

```cpp
Adjust2dx::setEnabled(false);
```

You can verify if the Adjust SDK is currently active by using the `Adjust2dx::isEnabled()` method. It is always possible to activate the Adjust SDK by invoking `Adjust2dx::setEnabled` with the parameter set to `true`.

### <a id="offline-mode"></a>Offline mode

You can put the Adjust SDK into offline mode, suspending transmissions to our servers while retaining tracked data to be sent later. When in offline mode, all information is saved in a file, so it is best not to trigger too many events while in offline mode.

You can activate offline mode by calling `Adjust2dx::setOfflineMode` with the parameter set to `true`.

```cpp
Adjust2dx::setOfflineMode(true);
```

Conversely, you can deactivate offline mode by calling `Adjust2dx::setOfflineMode` with the parameter set to `false`. When the Adjust SDK is put back in online mode, all saved information is sent to our servers with the correct time information.

Unlike when disabling tracking, **this setting is not remembered** between sessions. This means that the Adjust SDK always starts in online mode, even if the app was terminated in offline mode.

### <a id="event-buffering"></a>Event buffering

If your app makes heavy use of event tracking, you might want to delay some HTTP requests in order to send them in one batch every minute. You can enable event buffering through your `AdjustConfig2dx` instance by calling the `setEventBufferingEnabled` method:

```cpp
// ...

bool AppDelegate::applicationDidFinishLaunching() {
    std::string appToken = "{YourAppToken}";
    std::string environment = AdjustEnvironmentSandbox2dx;

    AdjustConfig2dx adjustConfig = AdjustConfig2dx(appToken, environment);
    adjustConfig.setLogLevel(AdjustLogLevel2dxVerbose);
    adjustConfig.setEventBufferingEnabled(true);

    Adjust2dx::start(adjustConfig);

    // ...
}
```

If nothing is set here, event buffering is **disabled by default**.

### <a id="gdpr-forget-me"></a>GDPR right to be forgotten

In accordance with article 17 of the EU's General Data Protection Regulation (GDPR), you can notify Adjust when a user has exercised their right to be forgotten. Calling the following method will instruct the Adjust SDK to communicate the user's choice to be forgotten to the Adjust backend:

```cpp
Adjust2dx::gdprForgetMe();
```

Upon receiving this information, Adjust will erase the user's data and the Adjust SDK will stop tracking the user. No requests from this device will be sent to Adjust in the future.

### <a id="sdk-signature"></a>SDK signature

An account manager must activate the Adjust SDK signature. Contact Adjust support (support@adjust.com) if you are interested in using this feature.

If the SDK signature has already been enabled on your account and you have access to App Secrets in your Adjust Dashboard, please use the method below to integrate the SDK signature into your app.

An App Secret is set by passing all secret parameters (`secretId`, `info1`, `info2`, `info3`, `info4`) to `setAppSecret` method of `AdjustConfig` instance:

```cpp
auto adjustConfig = AdjustConfig2dx(appToken, environment);

adjustConfig.setAppSecret(secretId, info1, info2, info3, info4);

Adjust2dx::start(adjustConfig);
```

### <a id="background-tracking"></a>Background tracking

The default behavior of the Adjust SDK is to **pause sending HTTP requests while the app is in the background**. You can change this in your `AdjustConfig2dx` instance by calling the `setSendInBackground` method:

```cpp
// ...

bool AppDelegate::applicationDidFinishLaunching() {
    std::string appToken = "{YourAppToken}";
    std::string environment = AdjustEnvironmentSandbox2dx;

    AdjustConfig2dx adjustConfig = AdjustConfig2dx(appToken, environment);
    adjustConfig.setLogLevel(AdjustLogLevel2dxVerbose);
    adjustConfig.setSendInBackground(true);

    Adjust2dx::start(adjustConfig);

    // ...
}
```

If nothing is set here, sending in the background is **disabled by default**.

### <a id="device-ids"></a>Device IDs

Certain services (such as Google Analytics) require you to coordinate device and client IDs in order to prevent duplicate reporting.

### <a id="di-idfa"></a>iOS Advertising Identifier

You can access the IDFA value on an iOS device by invoking the `getIdfa()` method of the `Adjust2dx` instance.

```cpp
std::string idfa = Adjust2dx::getIdfa();
```

### <a id="di-adid"></a>Adjust device identifier

For each device with your app installed, the Adjust backend generates a unique **Adjust device identifier** (**adid**). In order to obtain this identifier, you can call the following method on the `Adjust2dx` instance:

```cpp
std::string adid = Adjust2dx::getAdid();
```

**Note**: Information about the **adid** is only available after the Adjust backed has tracked your app's installation. From that moment on, the Adjust SDK has information about the device **adid** and you can access it with this method. So, **it is not possible** to access the **adid** before the SDK has been initialized and the installation of your app has been tracked successfully.

### <a id="user-attribution"></a>User attribution

Attribution callbacks are triggered via the method described in the [attribution callback section](#attribution-callback). They provide you with information about any changes to your users’ attribution values. If you wish to access information about a user's current attribution value at any other time, you can make a call to the following method of the `Adjust2dx` instance:

```cpp
AdjustAttribution2dx attribution = Adjust2dx::getAttribution();
```

**Note**: Information about a user’s current attribution value is only available after the Adjust backed has tracked your app's installation and an initial attribution callback has been triggered. From that moment on, the Adjust SDK has information about the user's attribution value and you can access it with this method. So, **it is not possible** to access a user's attribution value before the SDK has been initialized and an initial attribution callback has been triggered.

### <a id="push-token"></a>Push token

To send us a push notification token, add the following call to Adjust **whenever your app receives the token or it is updated**:

```cpp
Adjust2dx::setDeviceToken("YourPushNotificationToken");
```

Push tokens are used for the Adjust Audience Builder and client callbacks, and are required for the upcoming uninstall tracking feature.

### <a id="pre-installed-trackers"></a>Pre-installed trackers

If you want to use the Adjust SDK to recognize users whose devices came with your app pre-installed, follow these steps.

1. Create a new tracker in your [dashboard].
2. Open your app delegate and set the default tracker of your `AdjustConfig2dx` instance:

    ```cpp
    AdjustConfig2dx adjustConfig = AdjustConfig2dx(appToken, environment);

    adjustConfig.setDefaultTracker("{TrackerToken}");

    Adjust2dx::adjustConfig(config);
    ```

  Replace `{TrackerToken}` with the tracker token you created in step one. Please note that the dashboard displays a tracker URL (including `http://app.adjust.com/`). In your source code, you should specify only the six-character token and not the entire URL.

3. Build and run your app. You should see a line like the following in the app's log output:

    ```
    Default tracker: 'abc123'
    ```

### <a id="deeplinking"></a>Deep linking

If you are using the Adjust tracker URL with an option to deep link into your app from the URL, there is the possibility to get information about the deep link URL and its content. There are two scenarios when it comes to deep linking: standard and deferred. 

Standard deep linking is when a user already has your app installed. iOS offers native support for retrieving information about the deep link content in this scenario.

Deferred deep linking is when a user does not have your app installed. iOS does not offer native support for deferred deep linking. Instead, the Adjust SDK offers a way to retrieve information about the deep link content.

You need to set up deep link handling in your app **at a native level** - in your generated Xcode project.

### <a id="deeplinking-standard"></a>Standard deep linking

Unfortunately, in this scenario the information about the deep link can not be delivered to you in your Cocos2d-x C++ code. Once you have set up your app to handle deep linking, you will get information about the deep link at a native level. For more information, refer to our chapters below on how to enable deep linking for iOS apps.

### <a id="deeplinking-deferred"></a>Deferred deep linking

In order to get information about the URL content in a deferred deep-linking scenario, you will need to set a callback method on the `AdjustConfig2dx` object which will receive a `std::string` parameter, where the content of the URL will be delivered. You should set this method on the `AdjustConfig2dx` object instance by calling the `setDeferredDeeplinkCallback` method:

```cpp
#include "Adjust/Adjust2dx.h"

//...

static bool deferredDeeplinkCallbackMethod(std::string deeplink) {
    CCLOG("\nDeferred deep link received!");
    CCLOG("\nURL: %s", deeplink.c_str());
    CCLOG("\n");

    Adjust2dx::appWillOpenUrl(deeplink);

    return true;
}

// ...

bool AppDelegate::applicationDidFinishLaunching() {
    std::string appToken = "{YourAppToken}";
    std::string environment = AdjustEnvironmentSandbox2dx;

    AdjustConfig2dx adjustConfig = AdjustConfig2dx(appToken, environment);
    adjustConfig.setLogLevel(AdjustLogLevel2dxVerbose);
    adjustConfig.setDeferredDeeplinkCallback(deferredDeeplinkCallbackMethod);

    Adjust2dx::start(adjustConfig);

    // ...
}
```

<a id="deeplinking-deferred-open">In the deferred deep-linking scenario, there is one additional setting which can be set on the deferred deep link callback method. Once the Adjust SDK gets the deferred deep link information, you can choose whether our SDK opens this URL or not. To do this, set the return value of your deferred deep link callback method.

If nothing is set, **the Adjust SDK will always try to launch the URL by default**.

### <a id="deeplinking-ios"></a>Deep link handling for iOS apps

**This should be done in a native Xcode project.**

To set up your iOS app to handle deep linking at a native level, please follow our [guide][ios-deeplinking] in the official iOS SDK README.


[adjust]:       http://adjust.com
[dashboard]:    http://adjust.com
[adjust.com]:   http://adjust.com

[releases]:             https://github.com/adjust/cocos2dx_sdk/releases
[deeplinking]:          https://docs.adjust.com/en/tracker-generation/#deeplinking
[event-tracking]:       https://docs.adjust.com/en/event-tracking
[callbacks-guide]:      https://docs.adjust.com/en/callbacks
[ios-deeplinking]:      https://github.com/adjust/ios_sdk/#deeplinking
[special-partners]:     https://docs.adjust.com/en/special-partners
[attribution-data]:     https://github.com/adjust/sdks/blob/master/doc/attribution-data.md
[currency-conversion]:  https://docs.adjust.com/en/event-tracking/#tracking-purchases-in-different-currencies

[run]:                    https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/ios/run.png
[add-ios-files]:          https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/ios/add_ios_files.png
[add-adjust2dx]:          https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/ios/add_adjust2dx.png
[add-the-frameworks]:     https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/ios/add_the_frameworks.png
[add-other-linker-flags]: https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/ios/add_other_linker_flags.png

## <a id="license"></a>License

The Adjust SDK is licensed under the MIT License.

Copyright (c) 2012-2018 Adjust GmbH, http://www.adjust.com

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
