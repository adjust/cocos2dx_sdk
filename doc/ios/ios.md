## Summary

This is the Cocos2d-x SDK of adjust™. You can read more about adjust™ at [adjust.com].

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
      * [In-App Purchase verification](#iap-verification)
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
    * [Background tracking](#background-tracking)
    * [Device IDs](#device-ids)
      * [iOS Advertising Identifier](#di-idfa)
      * [Adjust device identifier](#di-adid)
    * [User attribution](#user-attribution)
    * [Push token](#push-token)
    * [Pre-installed trackers](#pre-installed-trackers)
    * [Deep linking](#deeplinking)
        * [Standard deep linking scenario](#deeplinking-standard)
        * [Deferred deep linking scenario](#deeplinking-deferred)
        * [Deep linking handling for iOS app](#deeplinking-ios)
* [License](#license)

## <a id="basic-integration">Basic integration

We will describe the steps to integrate the adjust SDK into your Cocos2d-x iOS project.

### <a id="sdk-get">Get the SDK

Download the latest version from our [releases page][releases]. Extract the archive into a directory of your choice.

### <a id="sdk-add">Add the SDK to your project

Take the files from the `Adjust` folder and add them to your iOS project.

![][add_ios_files]

### <a id="sdk-frameworks">Add the frameworks to your project

You need to add the AdjustSdk, AdSupport and iAd frameworks to your project.

Before adding `AdjustSdk.framework` to your project, please make sure that you first copy it to the `proj.ios_mac` folder of your project.

Select your project in the Project Navigator. In the left hand side of the main view, select your target. In the tab `Build Phases` expand the group `Link Binary With Libraries`. On the bottom of that section click on the `+` button. Select the `AdjustSdk.framework` and click the `Add` button. Repeat the same steps to add the `AdSupport.framework` and `iAd.framework`.

![][add_the_frameworks]

### <a id="sdk-linker-flags">Add additional linker flags

In order to support categories from `AdjustSdk.framework`, you should add an additional linker flag. Go to the `Build Settings` part of Project Settings and look for `Other Linker Flags` option. Add `-ObjC` flag to it.

![][add_other_linker_flags]

### <a id="sdk-integrate">Integrate the SDK into your app

In the Project Navigator, open the source file of your application delegate. Add the import statement at the top of the file, then add the following call to Adjust in the `applicationDidFinishLaunching` of your app delegate:

```cpp
#include "Adjust/Adjust2dx.h"
// ...
std::string appToken = "{YourAppToken}";
std::string environment = AdjustEnvironmentSandbox2dx;

AdjustConfig2dx adjustConfig = AdjustConfig2dx(appToken, environment);

Adjust2dx::start(adjustConfig);
```

![][add_adjust2dx]

Replace `{YourAppToken}` with your app token. You can find this in your [dashboard].

Depending on whether you build your app for testing or for production, you must set `environment` with one of these values:

```cpp
std::string environment = AdjustEnvironmentSandbox2dx;
std::string environment = AdjustEnvironmentProduction2dx;
```

**Important:** This value should be set to `AdjustEnvironmentSandbox2dx` if and only if you or someone else is testing your app. Make sure to set the environment to `AdjustEnvironmentProduction2dx` just before you publish the app. Set it back to `AdjustEnvironmentSandbox2dx` when you start developing and testing it again.

We use this environment to distinguish between real traffic and test traffic from test devices. It is very important that you keep this value meaningful at all times! This is especially important if you are tracking revenue.

### <a id="sdk-logging">Adjust logging

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

In case you want to use suppress log level, you should initialise `AdjustConfig2dx` instance with usage of constructor which receives additional `bool` parameter which indicates whether suppress log level should be enabled or not:

```cpp
std::string appToken = "{YourAppToken}";
std::string environment = AdjustEnvironmentSandbox2dx;

AdjustConfig2dx adjustConfig = AdjustConfig2dx(appToken, environment, true);
adjustConfig.setLogLevel(AdjustLogLevel2dxSuppress);
```

## <a id="sdk-build">Build your app

Build and run your app. If the build succeeds, you should carefully read the SDK logs in the console. After the app has launched for the first time, you should see the info log `Install tracked`.

![][run]

## <a id="additional-features">Additional features

Once you integrate the adjust SDK into your project, you can take advantage of the following features.

### <a id="event-tracking">Event tracking

With adjust, you can track any event that you want. Suppose you want to track every tap on a button. Simply create a new event token in your [dashboard]. Let's say that event token is `abc123`. You can add the following line in your button’s click handler method to track the click:

```cpp
AdjustEvent2dx adjustEvent = AdjustEvent2dx("abc123");
Adjust2dx::trackEvent(adjustEvent);
```

### <a id="revenue-tracking">Revenue tracking

If your users can generate revenue by tapping on advertisements or making In-App Purchases, then you can track those revenues with events. Let's say a tap is worth €0.01. You could track the revenue event like this:

```cpp
AdjustEvent2dx adjustEvent = AdjustEvent2dx("abc123");

adjustEvent.setRevenue(0.01, "EUR");

Adjust2dx::trackEvent(adjustEvent);
```

When you set a currency token, adjust will automatically convert the incoming revenues into a reporting revenue of your choice. Read more about [currency conversion here][currency-conversion].

You can read more about revenue and event tracking in the [event tracking guide][event-tracking].

### <a id="revenue-deduplication"></a>Revenue deduplication

You can also add an optional transaction ID to avoid tracking duplicate revenues. The last ten transaction IDs are remembered, and revenue events with duplicate transaction IDs are skipped. This is especially useful for In-App Purchase tracking. You can see an example below.

If you want to track in-app purchases, please make sure to call the `trackEvent` only if the transaction is finished and item is purchased. That way you can avoid tracking revenue that is not actually being generated.

```cpp
AdjustEvent2dx adjustEvent = AdjustEvent2dx("abc123");

adjustEvent.setRevenue(0.01, "EUR");
adjustEvent.setTransactionId("transactionID");

Adjust2dx::trackEvent(adjustEvent);
```

**Note**: Transaction ID is the iOS term, unique identifier for successfully finished Android In-App-Purchases is named **Order ID**.

### <a id="iap-verification">In-App Purchase verification

In-App purchase verification can be done with Cocos2d-x purchase SDK which is currently being developed and will soon be publicly available. For more information, please contact support@adjust.com.

### <a id="callback-parameters">Callback parameters

You can register a callback URL for your events in your [dashboard]. We will send a GET request to that URL whenever the event is tracked. You can add callback parameters to that event by calling `addCallbackParameter` method on the event before tracking it. We will then append these parameters to your callback URL.

For example, suppose you have registered the URL `http://www.adjust.com/callback` for your event with event token `abc123` and execute the following lines:

```cpp
AdjustEvent2dx adjustEvent = AdjustEvent2dx("abc123");

adjustEvent.addCallbackParameter("key", "value");
adjustEvent.addCallbackParameter("foo", "bar");

Adjust2dx::trackEvent(adjustEvent);
```

In that case, we would track the event and send a request to:

```
http://www.adjust.com/callback?key=value&foo=bar
```

It should be mentioned that we support a variety of placeholders like `{idfa}` that can be used as parameter values. In the resulting callback this placeholder would be replaced with the ID for Advertisers of the current device. Also note that we don't store any of your custom parameters, but only append them to your callbacks. If you haven't registered a callback for an event, these parameters won't even be read.

You can read more about using URL callbacks, including a full list of available values, in our [callbacks guide][callbacks-guide].

### <a id="partner-parameters">Partner parameters

You can also add parameters to be transmitted to network partners, for the integrations that have been activated in your adjust dashboard.

This works similarly to the callback parameters mentioned above, but can be added by calling the `addPartnerParameter` method on your `AdjustEvent2dx` instance.

```cpp
AdjustEvent2dx adjustEvent = AdjustEvent2dx("abc123");

adjustEvent.addPartnerParameter("key", "value");
adjustEvent.addPartnerParameter("foo", "bar");

Adjust2dx::trackEvent(adjustEvent);
```

You can read more about special partners and these integrations in our [guide to special partners][special-partners].

### <a id="session-parameters">Session parameters

Some parameters are saved to be sent in every event and session of the adjust SDK. Once you have added any of these parameters, you don't need to add them every time, since they will be saved locally. If you add the same parameter twice, there will be no effect.

These session parameters can be called before the adjust SDK is launched to make sure they are sent even on install. If you need to send them with an install, but can only obtain the needed values after launch, it's possible to [delay](#delay-start) the first launch of the adjust SDK to allow this behaviour.

### <a id="session-callback-parameters"> Session callback parameters

The same callback parameters that are registered for [events](#callback-parameters) can be also saved to be sent in every event or session of the adjust SDK.

The session callback parameters have a similar interface of the event callback parameters. Instead of adding the key and it's value to an event, it's added through a call to method `addSessionCallbackParameter` of the `Adjust2dx` instance.

```cpp
Adjust2dx::addSessionCallbackParameter("foo", "bar");
```

The session callback parameters will be merged with the callback parameters added to an event. The callback parameters added to an event have precedence over the session callback parameters. Meaning that, when adding a callback parameter to an event with the same key to one added from the session, the value that prevails is the callback parameter added to the event.

It's possible to remove a specific session callback parameter by passing the desiring key to the method `removeSessionCallbackParameter` of the `Adjust2dx` instance.

```cpp
Adjust2dx::removeSessionCallbackParameter("foo");
```

If you wish to remove all key and values from the session callback parameters, you can reset it with the method `resetSessionCallbackParameters` of the `Adjust2dx` instance.

```cpp
Adjust2dx::resetSessionCallbackParameters();
```

### <a id="session-partner-parameters">Session partner parameters

In the same way that there is [session callback parameters](#session-callback-parameters) that are sent for every event or session of the adjust SDK, there is also session partner parameters.

These will be transmitted to network partners, for the integrations that have been activated in your adjust [dashboard].

The session partner parameters have a similar interface to the event partner parameters. Instead of adding the key and it's value to an event, it's added through a call to method `addSessionPartnerParameter` of the `Adjust2dx` instance.

```cpp
Adjust2dx::addSessionPartnerParameter("foo", "bar");
```

The session partner parameters will be merged with the partner parameters added to an event. The partner parameters added to an event have precedence over the session partner parameters. Meaning that, when adding a partner parameter to an event with the same key to one added from the session, the value that prevails is the partner parameter added to the event.

It's possible to remove a specific session partner parameter by passing the desiring key to the method `removeSessionPartnerParameter` of the `Adjust2dx` instance.

```cpp
Adjust2dx::removeSessionPartnerParameter("foo");
```

If you wish to remove all keys and values from the session partner parameters, you can reset it with the method `resetSessionPartnerParameters` of the `Adjust2dx` instance.

```cpp
Adjust2dx::resetSessionPartnerParameters();
```

### <a id="delay-start">Delay start

Delaying the start of the adjust SDK allows your app some time to obtain session parameters, such as unique identifiers, to be sent on install.

Set the initial delay time in seconds with the `setDelayStart` method of the `AdjustConfig2dx` instance:

```cpp
config.setDelayStart(5.5);
```

In this case this will make the adjust SDK not send the initial install session and any event created for 5.5 seconds. After this time is expired or if you call `Adjust2dx::sendFirstPackages()` in the meanwhile, every session parameter will be added to the delayed install session and events and the adjust SDK will resume as usual.

**The maximum delay start time of the adjust SDK is 10 seconds**.

### <a id="attribution-callback">Attribution callback

adjust can also send you a callback upon change of attribution. Due to the different sources considered for attribution, this information cannot be provided synchronously. Follow these steps to implement the optional callback in your application:

1. Create void method which receives parameter of type `AdjustAttribution2dx`.

2. After creating instance of `AdjustConfig2dx`, call its `setAttributionCallback` method with the previously created method as parameter.

The callback function will get called when the SDK receives final attribution data. Within the callback function you have access to the `attribution` parameter. Here is a quick summary of its properties:

- `std::string trackerToken` the tracker token of the current install.
- `std::string trackerName` the tracker name of the current install.
- `std::string network` the network grouping level of the current install.
- `std::string campaign` the campaign grouping level of the current install.
- `std::string adgroup` the ad group grouping level of the current install.
- `std::string creative` the creative grouping level of the current install.
- `std::string clickLabel` the click label of the current install.
- `std::string adid` the adjust device identifier.

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

Please make sure to consider [applicable attribution data policies][attribution-data].

### <a id="session-event-callbacks">Session and event callbacks

You can register a callback to be notified of successful and failed tracked events and/or sessions.

Follow the same steps to implement the following callback function for successfully tracked events:

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

The following callback function for failed tracked events:

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

And for failed tracked sessions:

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

The callback functions will be called after the SDK tries to send a package to the server. Within the callback you have access to a response data object specifically for the callback. Here is a quick summary of the session response data properties:

- `std::string message` the message from the server or the error logged by the SDK.
- `std::string timestamp` timestamp from the server.
- `std::string adid` a unique device identifier provided by adjust.
- `std::string jsonResponse` the JSON object with the response from the server.

Both event response data objects contain:

- `std::string eventToken` the event token, if the package tracked was an event.

And both event and session failed objects also contain:

- `std::string willRetry` indicates there will be an attempt to resend the package at a later time.

### <a id="disable-tracking">Disable tracking

You can disable the adjust SDK from tracking by invoking the method `Adjust2dx::setEnabled` with the enabled parameter as `false`. This setting is **remembered between sessions**, but it can only be activated after the first session.

```cpp
Adjust2dx::setEnabled(false);
```

You can verify if the adjust SDK is currently active with the method `Adjust2dx::isEnabled()`. It is always possible to activate the adjust SDK by invoking `Adjust2dx::setEnabled` with the parameter set to `true`.

### <a id="offline-mode">Offline mode

You can put the adjust SDK in offline mode to suspend transmission to our servers while retaining tracked data to be sent later. When in offline mode, all information is saved in a file, so be careful not to trigger too many events while in offline mode.

You can activate offline mode by calling `Adjust2dx::setOfflineMode` with the parameter `true`.

```cpp
Adjust2dx::setOfflineMode(true);
```

Conversely, you can deactivate offline mode by calling `Adjust2dx::setOfflineMode` with `false`. When the adjust SDK is put back in online mode, all saved information is sent to our servers with the correct time information.

Unlike disabling tracking, **this setting is not remembered** between sessions. This means that the SDK is in online mode whenever it is started, even if the app was terminated in offline mode.

### <a id="event-buffering">Event buffering

If your app makes heavy use of event tracking, you might want to delay some HTTP requests in order to send them in one batch every minute. You can enable event buffering with your `AdjustConfig2dx` instance by calling `setEventBufferingEnabled` method:

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

If nothing set, event buffering is **disabled by default**.

### <a id="background-tracking">Background tracking

The default behaviour of the adjust SDK is to **pause sending HTTP requests while the app is in the background**. You can change this in your `AdjustConfig2dx` instance by calling `setSendInBackground` method:

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

If nothing is set, sending in background is **disabled by default**.

### <a id="device-ids">Device IDs

Certain services (such as Google Analytics) require you to coordinate Device and Client IDs in order to prevent duplicated reporting.

### <a id="di-idfa">iOS Advertising Identifier

You can access to IDFA value on iOS device by invoking `getIdfa()` method of the `Adjust2dx` instance.

```cpp
std::string idfa = Adjust2dx::getIdfa();
```

### <a id="di-adid"></a>Adjust device identifier

For each device with your app installed, adjust backend generates unique **adjust device identifier** (**adid**). In order to obtain this identifier, you can make a call to following the method on the `Adjust2dx` instance:

```cpp
std::string adid = Adjust2dx::getAdid();
```

**Note**: Information about the **adid** is available after the app's installation has been tracked by the adjust backend. From that moment on, the adjust SDK has information about the device **adid** and you can access it with this method. So, **it is not possible** to access the **adid** before the SDK has been initialised and the installation of your app has been tracked successfully.

### <a id="user-attribution"></a>User attribution

The attribution callback will be triggered as described in the [attribution callback section](#attribution-callback), providing you with the information about any new attribution when ever it changes. In any other case, where you want to access information about your user's current attribution, you can make a call to the following method of the `Adjust2dx` instance:

```cpp
AdjustAttribution2dx attribution = Adjust2dx::getAttribution();
```

**Note**: Information about current attribution is available after app installation has been tracked by the adjust backend and attribution callback has been initially triggered. From that moment on, adjust SDK has information about your user's attribution and you can access it with this method. So, **it is not possible** to access user's attribution value before the SDK has been initialised and attribution callback has been initially triggered.

### <a id="push-token">Push token

To send us the push notifications token, then add the following call to Adjust **whenever you get your token in the app or when it gets updated**:

```cpp
Adjust2dx::setDeviceToken("YourPushNotificationToken");
```

### <a id="pre-installed-trackers">Pre-installed trackers

If you want to use the adjust SDK to recognize users that found your app pre-installed on their device, follow these steps.

1. Create a new tracker in your [dashboard]. Let's assume that new tracker token is `abc123`.
2. Open your app delegate and add set the default tracker of your `AdjustConfig2dx` instance:

    ```cpp
    AdjustConfig2dx adjustConfig = AdjustConfig2dx(appToken, environment);

    adjustConfig.setDefaultTracker("abc123");

    Adjust2dx::adjustConfig(config);
    ```

  Replace `{TrackerToken}` with the tracker token you created in step 2. Please note that the dashboard displays a tracker
  URL (including `http://app.adjust.com/`). In your source code, you should specify only the six-character token and not the
  entire URL.

3. Build and run your app. You should see a line like the following in the app's log output:

    ```
    Default tracker: 'abc123'
    ```

### <a id="deeplinking">Deep linking

If you are using the adjust tracker URL with an option to deep link into your app from the URL, there is the possibility to get info about the deep link URL and its content. Hitting the URL can happen when the user has your app already installed (standard deep linking scenario) or if they don't have the app on their device (deferred deep linking scenario). In the standard deep linking scenario, Android platform natively offers the possibility for you to get the info about the deep link content. Deferred deep linking scenario is something which Android platform doesn't support out of box and for this case, the adjust SDK will offer you the mechanism to get the info about the deep link content.

You need to set up deep linking handling in your app **on native level** - in your generated Xcode project.

### <a id="deeplinking-standard">Standard deep linking scenario

Unfortunatelly, in this scenario the information about the deep link can not be delivered to you in your Cocos2d-x C++ code. Once you enable your app to handle deep linking, you will get information about the deep link on native level. For more information check our chapters below on how to enable deep linking for iOS apps.

### <a id="deeplinking-deferred">Deferred deep linking scenario

In order to get info about the URL content in a deferred deep linking scenario, you should set a callback method on the `AdjustConfig2dx` object which will receive one `std::string` parameter where the content of the URL will be delivered. You should set this method on the `AdjustConfig2dx` object instance by calling the method `setDeferredDeeplinkCallback`:

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

<a id="deeplinking-deferred-open">In deferred deep linking scenario, there is one additional setting which can be set on the deferred deep link callback method. Once the adjust SDK gets the deferred deep link info, we offer you the possibility to choose whether our SDK should open this URL or not. You can choose to set this option by setting the return value of your deferred deep link callback method.

If nothing is set, **the adjust SDK will always try to launch the URL by default**.

### <a id="deeplinking-ios">Deep linking handling for iOS app

**This should be done in native Xcode project.**

To set up your iOS app to handle deep linking on native level, please follow our [guide][ios-deeplinking] in the official iOS SDK README.


[adjust]:	      http://adjust.com
[dashboard]:    http://adjust.com
[adjust.com]:  	http://adjust.com

[releases]:             https://github.com/adjust/cocos2dx_sdk/releases
[deeplinking]:          https://docs.adjust.com/en/tracker-generation/#deeplinking
[event-tracking]:       https://docs.adjust.com/en/event-tracking
[callbacks-guide]:      https://docs.adjust.com/en/callbacks
[ios-deeplinking]:      https://github.com/adjust/ios_sdk/#deeplinking
[special-partners]:     https://docs.adjust.com/en/special-partners
[attribution-data]:     https://github.com/adjust/sdks/blob/master/doc/attribution-data.md
[currency-conversion]:  https://docs.adjust.com/en/event-tracking/#tracking-purchases-in-different-currencies

[run]:                    https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/ios/run.png
[add_ios_files]:          https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/ios/add_ios_files.png
[add_adjust2dx]:          https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/ios/add_adjust2dx.png
[add_the_frameworks]:     https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/ios/add_the_frameworks.png
[add_other_linker_flags]: https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/ios/add_other_linker_flags.png

## <a id="license">License

The adjust SDK is licensed under the MIT License.

Copyright (c) 2012-2017 adjust GmbH,
http://www.adjust.com

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

