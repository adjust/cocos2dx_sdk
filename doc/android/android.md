## Summary

This is the Cocos2d-x SDK of Adjust™. You can read more about Adjust™ at [adjust.com].

## Table of contents

* [Basic integration](#basic-integration)
   * [Get the SDK](#sdk-get)
   * [Add the SDK to your project](#sdk-add)
   * [Add the C++ source file definitions](#sdk-cpp-files)
   * [Add the Adjust library to your project](#sdk-library)
   * [Add Google Play Services](#sdk-gps)
   * [Add permissions](#sdk-permissions)
   * [Add broadcast receiver](#sdk-broadcast-receiver)
   * [Proguard settings](#sdk-proguard)
   * [Integrate the SDK into your app](#sdk-integrate)
   * [Adjust logging](#sdk-logging)
   * [Session tracking](#sdk-session-tracking)
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
    * [Background tracking](#background-tracking)
    * [Device IDs](#device-ids)
      * [Google Play Services advertising identifier](#di-gps-adid)
      * [Adjust device identifier](#di-adid)
    * [User attribution](#user-attribution)
    * [Push token](#push-token)
    * [Pre-installed trackers](#pre-installed-trackers)
    * [Deep linking](#deeplinking)
        * [Standard deep linking](#deeplinking-standard)
        * [Deferred deep linking](#deeplinking-deferred)
        * [Deep link handling for Android apps](#deeplinking-android)
* [License](#license)


## <a id="basic-integration">Basic integration

How to integrate the Adjust SDK into your Cocos2d-x Android project.

### <a id="sdk-get">Get the SDK

Download the latest version from our [releases page][releases]. Extract the archive into a directory of your choosing.

### <a id="sdk-add">Add the SDK to your project

Throughout this guide, we assume that you are using `Android Studio` for development. If you are using `Eclipse`, please read our [Cocos2d-x Eclipse guide][eclipse-guide].

Take the files from the `Adjust` folder and add them to your Android project.

![][add-android-files]

### <a id="sdk-cpp-files">Add the C++ source file definitions.

Add the paths of the Adjust C++ files to the `LOCAL_SRC_FILES` section in your `Android.mk` file.

```mk
../../../Classes/Adjust/AdjustConfig2dx.cpp \
../../../Classes/Adjust/AdjustAttribution2dx.cpp \
../../../Classes/Adjust/AdjustProxy2dx.cpp \
../../../Classes/Adjust/AdjustEvent2dx.cpp \
../../../Classes/Adjust/Adjust2dx.cpp \
../../../Classes/Adjust/AdjustEventFailure2dx.cpp \
../../../Classes/Adjust/AdjustEventSuccess2dx.cpp \
../../../Classes/Adjust/AdjustSessionFailure2dx.cpp \
../../../Classes/Adjust/AdjustSessionSuccess2dx.cpp
```

![][add-to-android-mk]

### <a id="sdk-library">Add the Adjust library to your project

Take the `adjust-android.jar` library and copy it to your project's `libs` folder.

![][add-android-jar]

### <a id="sdk-gps">Add Google Play Services

Since August 1, 2014, apps in the Google Play Store must use the [Google Advertising ID][google-ad-id] to uniquely identify devices. To allow the Adjust SDK to use the Google Advertising ID, you must integrate [Google Play Services][google-play-services]. If you haven't done this yet, follow these steps:

1. Open the `build.gradle` file of your app and find the `dependencies` block. Add the following line:

    ```
    compile 'com.google.android.gms:play-services-analytics:9.3.0'
    ```

    ![][gps-gradle]

2. Skip this step if you are using version 7 or later of Google Play Services:
   In the Package Explorer, open the `AndroidManifest.xml` file of your Android project. Add the following `meta-data` tag inside the `<application>` element:

    ```xml
    <meta-data android:name="com.google.android.gms.version"
               android:value="@integer/google-play-services_version" />
    ```

    ![][gps-manifest]

### <a id="sdk-permissions">Add permissions

In the Package Explorer, open the `AndroidManifest.xml` file of your Android project. Add the `uses-permission` tag for `INTERNET` if it's not already present.

```xml
<uses-permission android:name="android.permission.INTERNET" />
```

If you are **not targeting the Google Play Store**, add both of these permissions instead:

```xml
<uses-permission android:name="android.permission.INTERNET" />
<uses-permission android:name="android.permission.ACCESS_WIFI_STATE" />
```

![][manifest-permissions]

### <a id="sdk-broadcast-receiver">Add broadcast receiver

In your `AndroidManifest.xml` file, add the following `receiver` tag inside the `application` tag:

```xml
<receiver
    android:name="com.adjust.sdk.AdjustReferrerReceiver"
    android:exported="true" >
    <intent-filter>
        <action android:name="com.android.vending.INSTALL_REFERRER" />
    </intent-filter>
</receiver>
```

![][broadcast-receiver]

We use this broadcast receiver to retrieve the install referrer in order to improve conversion tracking.

If you are already using a different broadcast receiver for the `INSTALL_REFERRER` intent, then follow [these instructions][referrer] to add the call to the Adjust broadcast receiver.

### <a id="sdk-proguard"></a>Proguard settings

If you are using Proguard, add these lines to your Proguard file:

```
-keep public class com.adjust.sdk.** { *; }
-keep class com.google.android.gms.common.ConnectionResult {
    int SUCCESS;
}
-keep class com.google.android.gms.ads.identifier.AdvertisingIdClient {
    com.google.android.gms.ads.identifier.AdvertisingIdClient$Info getAdvertisingIdInfo(android.content.Context);
}
-keep class com.google.android.gms.ads.identifier.AdvertisingIdClient$Info {
    java.lang.String getId();
    boolean isLimitAdTrackingEnabled();
}
-keep class dalvik.system.VMRuntime {
    java.lang.String getRuntime();
}
-keep class android.os.Build {
    java.lang.String[] SUPPORTED_ABIS;
    java.lang.String CPU_ABI;
}
-keep class android.content.res.Configuration {
    android.os.LocaledList getLocales();
    java.util.Locale locale;
}
-keep class android.os.LocaledList {
    java.util.Locale get(int);
}
```

If you are **not targeting the Google Play Store**, you can remove the `com.google.android.gms` rules.

### <a id="sdk-integrate">Integrate the SDK into your app

In the Package Explorer, open the source file of your app delegate. Add the import statement at the top of the file, then add the following call to Adjust in the `applicationDidFinishLaunching` method of your app delegate:

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

You must set `environment` with one of these values:

```cpp
std::string environment = AdjustEnvironmentSandbox2dx;
std::string environment = AdjustEnvironmentProduction2dx;
```

**Important:** This value should be set to `AdjustEnvironmentSandbox2dx` if and only if you or someone else is testing your app. Make sure to set the environment to `AdjustEnvironmentProduction2dx` before you publish your app. Set it back to `AdjustEnvironmentSandbox2dx` when you start developing and testing it again.

We use this environment to distinguish between real traffic and test traffic from test devices. It is imperative that you keep this value meaningful at all times, especially if you are tracking revenue.

### <a id="sdk-logging">Adjust logging

You can increase or decrease the amount of logs you see in tests by calling `setLogLevel` on the `AdjustConfig2dx` instance with one of the following parameters:

```cpp
adjustConfig.setLogLevel(AdjustLogLevel2dxVerbose);     // enable all logging
adjustConfig.setLogLevel(AdjustLogLevel2dxDebug);       // enable more logging
adjustConfig.setLogLevel(AdjustLogLevel2dxInfo);        // the default
adjustConfig.setLogLevel(AdjustLogLevel2dxWarn);        // disable info logging
adjustConfig.setLogLevel(AdjustLogLevel2dxError);       // disable warnings as well
adjustConfig.setLogLevel(AdjustLogLevel2dxAssert);      // disable errors as well
adjustConfig.setLogLevel(AdjustLogLevel2dxSuppress);    // disable all log output
```

If you want to use the suppress log level, you should initialize the `AdjustConfig2dx` instance with the usage of a constructor which receives an additional `bool` indicating whether the suppress log level should be enabled or not:

```cpp
std::string appToken = "{YourAppToken}";
std::string environment = AdjustEnvironmentSandbox2dx;

AdjustConfig2dx adjustConfig = AdjustConfig2dx(appToken, environment, true);
adjustConfig.setLogLevel(AdjustLogLevel2dxSuppress);
```

### <a id="sdk-session-tracking">Session tracking

**Please pay close attention to this chapter and ensure that you implement session tracking correctly in your app**.

To provide proper session tracking, it is necessary to call certain Adjust methods every time your app moves to the background or comes to the foreground. Otherwise, the SDK might miss a session start or end. In order to do this, follow these steps:

1. Open the app delegate file.
2. Add a call to the `onResume` method in the `applicationWillEnterForeground` method.
§. Add a call to the `onPause` method in the `applicationDidEnterBackground` method.

Following these steps, your app delegate should look like this:

```cpp
#include "Adjust/Adjust2dx.h"
// ...

void AppDelegate::applicationDidEnterBackground() {
    // ...

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Adjust2dx::onPause();
#endif
}

void AppDelegate::applicationWillEnterForeground() {
    // ...

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Adjust2dx::onResume();
#endif
}

// ...
```

![][on-resume-on-pause]

## <a id="sdk-build">Build your app

Build and run your Android app. In your LogCat viewer, you can set the filter to `tag:Adjust` to hide all other logs. After your app has launched, you should see the following Adjust log: `Install tracked`.

![][log-message]

## <a id="additional-features">Additional features

Once you integrate the Adjust SDK into your project, you can take advantage of the following features.

### <a id="event-tracking">Event tracking

Adjust lets you track any event that you want.

Suppose you want to track every tap on a button. If you create a new event token in your [dashboard] - let's say that event token is `abc123` - you can add the following line in your button’s click handler method to track the click:

```cpp
AdjustEvent2dx adjustEvent = AdjustEvent2dx("abc123");
Adjust2dx::trackEvent(adjustEvent);
```

### <a id="revenue-tracking">Revenue tracking

If your users can generate revenue by tapping on advertisements or making in-app purchases, you can track that revenue through events. Let's say a tap is worth €0.01. You could track the revenue event like this:

```cpp
AdjustEvent2dx adjustEvent = AdjustEvent2dx("abc123");

adjustEvent.setRevenue(0.01, "EUR");

Adjust2dx::trackEvent(adjustEvent);
```

When you set a currency token, Adjust will automatically convert the incoming revenue into a reporting revenue of your choice. Read more about [currency conversion here][currency-conversion].

You can read more about revenue and event tracking in the [event tracking guide][event-tracking].

### <a id="revenue-deduplication"></a>Revenue deduplication

You can add an optional transaction ID to avoid tracking duplicate revenues. The last ten transaction IDs are remembered, and revenue events with duplicate transaction IDs are skipped. This is especially useful for in-app-purchase tracking. You can see an example below.

If you want to track in-app purchases, please make sure to call `trackEvent` only when the transaction has been completed. That way you can avoid tracking revenue that is not actually being generated.

```cpp
AdjustEvent2dx adjustEvent = AdjustEvent2dx("abc123");

adjustEvent.setRevenue(0.01, "EUR");
adjustEvent.setTransactionId("transactionID");

Adjust2dx::trackEvent(adjustEvent);
```

**Note**: Transaction ID is the iOS term; the unique identifier for successfully completed Android in-app purchases is **Order ID**.

### <a id="iap-verification">In-app purchase verification

In-app purchase verification can be done with the Cocos2d-x Purchase SDK which is currently in development and will soon be made publicly available. For more information, please contact support@adjust.com.

### <a id="callback-parameters">Callback parameters

You can register a callback URL for an event in your [dashboard]. We will send a GET request to that URL whenever the event is tracked. You can add callback parameters to an event by calling the `addCallbackParameter` method of the event before tracking it. We will then append these parameters to your callback URL.

For example, suppose you have registered the URL `http://www.adjust.com/callback` for your event with the event token `abc123`, and you execute the following lines:

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

Adjust supports a variety of placeholders, like `{idfa}`, that can be used as parameter values. In the resulting callback, `{idfa}` would be replaced with the current device's ID for Advertisers. 

Adjust does not store any of your custom parameters, but only appends them to your callbacks. If you haven't registered a callback for an event, these parameters won't even be read.

You can read more about using URL callbacks, including a full list of available values, in our [callbacks guide][callbacks-guide].

### <a id="partner-parameters">Partner parameters

You can also add parameters to be transmitted to network partners. These will work for integrations that have been activated in your Adjust dashboard.

These work similarly to the callback parameters mentioned above, but can be added by calling the `addPartnerParameter` method on the `AdjustEvent2dx` instance.

```cpp
AdjustEvent2dx adjustEvent = AdjustEvent2dx("abc123");

adjustEvent.addPartnerParameter("key", "value");
adjustEvent.addPartnerParameter("foo", "bar");

Adjust2dx::trackEvent(adjustEvent);
```

You can read more about special partners and how to integration them in our [guide to special partners][special-partners].

### <a id="session-parameters">Session parameters

Some parameters are saved to be sent in every event and session of the Adjust SDK. Once you have added any of these parameters, you don't need to add them again, since they will be saved locally. If you add the same parameter twice, there will be no effect.

These session parameters can be called before the Adjust SDK is launched to make sure they are sent even on install. If you need to send them with an install but can only obtain the needed values after launch, it's possible to [delay](#delay-start) the first launch of the Adjust SDK to allow for this.

### <a id="session-callback-parameters"> Session callback parameters

The same callback parameters that are registered for [events](#callback-parameters) can be also saved to be sent in every event or session of the Adjust SDK.

The session callback parameters have a similar interface to event callback parameters, except that, instead of adding the key and its value to an event, they are added through a call to the `addSessionCallbackParameter` method of the `Adjust2dx` instance.

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

### <a id="session-partner-parameters">Session partner parameters

In the same way that there are [session callback parameters](#session-callback-parameters) that are sent for every event or session of the Adjust SDK, there are also session partner parameters.

These will be transmitted to any network partners that have been integrated and activated in your Adjust [dashboard].

Session partner parameters have a similar interface to event partner parameters, except that, instead of adding the key and its value to an event, they are added through a call to the `addSessionPartnerParameter` method of the `Adjust2dx` instance.

```cpp
Adjust2dx::addSessionPartnerParameter("foo", "bar");
```

Session partner parameters will be merged with the partner parameters that you have added to an event. The partner parameters that have been added to an event take precedence over session partner parameters. This means that if you add a partner parameter to an event with the same key as one added from the session, the partner parameter will prevail.

It's possible to remove a specific session partner parameter by passing the desired key to the `removeSessionPartnerParameter` method of the `Adjust2dx` instance.

```cpp
Adjust2dx::removeSessionPartnerParameter("foo");
```

If you wish to remove all keys and values from the session partner parameters, you can reset them with the `resetSessionPartnerParameters` method of the `Adjust2dx` instance.

```cpp
Adjust2dx::resetSessionPartnerParameters();
```

### <a id="delay-start">Delay start

Delaying the start of the Adjust SDK allows your app some time to obtain session parameters, such as unique identifiers, so they can be sent on install.

Set the initial delay time, in seconds, with the `setDelayStart` method of the `AdjustConfig2dx` instance:

```cpp
config.setDelayStart(5.5);
```

In this case, the Adjust SDK will wait 5.5 seconds before sending the initial install session and any events created. After this time has elapsed, or if you call `Adjust2dx::sendFirstPackages()` in the meantime, every session parameter will be added to the delayed install session and events, and the Adjust SDK will resume as usual.

**The maximum delay start time of the Adjust SDK is 10 seconds**.

### <a id="attribution-callback">Attribution callback

Adjust can send you a callback upon any change in attribution. Due to the different sources considered for attribution, this information cannot be provided synchronously. Follow these steps to implement an attribution callback in your application:

1. Create a void method which receives and `AdjustAttribution2dx` parameter.

2. After creating an `AdjustConfig2dx` instance, call its `setAttributionCallback` method with the previously created method as a parameter.

The callback function will be called when the SDK receives final attribution data. Within the callback function you have access to the `attribution` parameter. Here is a quick summary of its properties:

- `std::string trackerToken` the tracker token of the current install.
- `std::string trackerName` the tracker name of the current install.
- `std::string network` the network grouping level of the current install.
- `std::string campaign` the campaign grouping level of the current install.
- `std::string adgroup` the ad group grouping level of the current install.
- `std::string creative` the creative grouping level of the current install.
- `std::string clickLabel` the click label of the current install.
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

### <a id="session-event-callbacks">Session and event callbacks

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

### <a id="disable-tracking">Disable tracking

You can disable the Adjust SDK from tracking by invoking the `Adjust2dx::setEnabled` method with the enabled parameter set to `false`. This setting is **remembered between sessions**, but it can only be activated after the first session.

```cpp
Adjust2dx::setEnabled(false);
```

You can verify if the Adjust SDK is currently active by using the `Adjust2dx::isEnabled()` method. It is always possible to activate the Adjust SDK by invoking `Adjust2dx::setEnabled` with the parameter set to `true`.

### <a id="offline-mode">Offline mode

You can put the Adjust SDK in offline mode to suspend transmissions to our servers while retaining tracked data to be sent later. When in offline mode, all information is saved in a file, so it is best not to trigger too many events while in offline mode.

You can activate offline mode by calling `Adjust2dx::setOfflineMode` with the parameter set to `true`.

```cpp
Adjust2dx::setOfflineMode(true);
```

Conversely, you can deactivate offline mode by calling `Adjust2dx::setOfflineMode` with the parameter set to `false`. When the Adjust SDK is put back in online mode, all saved information is send to our servers with the correct time information.

Unlike when disabling tracking, **this setting is not remembered** between sessions. This means that the SDK always starts in online mode, even if the app was terminated in offline mode.

### <a id="event-buffering">Event buffering

If your app makes heavy use of event tracking, you might want to delay some HTTP requests in order to send them in one batch every minute. You can enable event buffering through the `AdjustConfig2dx` instance by calling the `setEventBufferingEnabled` method:

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

### <a id="background-tracking">Background tracking

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

### <a id="device-ids">Device IDs

Certain services (such as Google Analytics) require you to coordinate device and client IDs in order to prevent duplicated reporting.

### <a id="di-gps-adid"></a>Google Play Services advertising identifier

The Adjust SDK allows you to read the Google Advertising Identifier of the Android device on which your app is running. To do this, set the callback method which receives the `std::string` parameter. Next, invoke the `getGoogleAdId` method of the `Adjust2dx` instance and pass the defined callback method as a parameter. You will then get the Google Advertising Identifier value in your callback method:

```cpp
static void adIdCallbackMethod(std::string adId) {
    CCLOG("\nAdvertising identifier = %s", adId.c_str());
    CCLOG("\n");
}

// ...

Adjust2dx::getGoogleAdId(adIdCallbackMethod);
```

### <a id="di-adid"></a>Adjust device identifier

For each device with your app installed, the Adjust backend generates a unique **Adjust device identifier** (**adid**). In order to obtain this identifier, you can call the following method on the `Adjust2dx` instance:

```cpp
std::string adid = Adjust2dx::getAdid();
```

**Note**: Information about the **adid** is only available after the Adjust backed has tracked your app's installation. From that moment on, the Adjust SDK has information about the device **adid** and you can access it with this method. So, **it is not possible** to access the **adid** before the SDK has been initialized and the installation of your app has been tracked successfully.

### <a id="user-attribution"></a>User attribution

As described in the [attribution callback section](#attribution-callback), this callback is triggered to provide you with information about new attributions whenever there is a change. If you want to access information about a user's current attribution value at any other time, you can make a call to following method of the `Adjust2dx` instance:

```cpp
AdjustAttribution2dx attribution = Adjust2dx::getAttribution();
```

**Note**: Information about a user’s current attribution value is only available after the Adjust backed has tracked your app's installation and an initial attribution callback has been triggered. From that moment on, the Adjust SDK has information about the user's attribution value and you can access it with this method. So, **it is not possible** to access a user's attribution value before the SDK has been initialized and an initial attribution callback has been triggered.

### <a id="push-token">Push token

To send us a push notification token, add the following call to Adjust **whenever your app receives the token or it is updated**:

```cpp
Adjust2dx::setDeviceToken("YourPushNotificationToken");
```

### <a id="pre-installed-trackers">Pre-installed trackers

If you want to use the Adjust SDK to recognize users whose devices came with your app pre-installed, follow these steps:

1. Create a new tracker in your [dashboard].

2. Open your app delegate and set the default tracker of your `AdjustConfig2dx` instance:

    ```cpp
    AdjustConfig2dx adjustConfig = AdjustConfig2dx(appToken, environment);

    adjustConfig.setDefaultTracker("{TrackerToken}");

    Adjust2dx::adjustConfig(config);
    ```

  Replace `{TrackerToken}` with the tracker token you created in step one. Please note that the dashboard displays a tracker
  URL (including `http://app.adjust.com/`). In your source code, you should specify only the six-character token and not the
  entire URL.

3. Build and run your app. You should see a line like the following in the app's log output:

    ```
    Default tracker: 'abc123'
    ```

### <a id="deeplinking">Deep linking

If you are using the Adjust tracker URL with an option to deep link into your app from the URL, there is the possibility to get information about the deep link URL and its content. There are two scenarios when it comes to deep linking: standard and deferred.

Standard deep linking is when a user already has your app installed. Android offers native support for retrieving information about the deep link content in this scenario.

Deferred deep linking is when a user does not have your app installed. Android does not offer native support for deferred deep linking. Instead, the Adjust SDK offers a way to retrieve information about the deep link content.

You need to set up deep link handling in your app **at a native level** - in your generated Android project.

### <a id="deeplinking-standard">Standard deep linking

Unfortunately, in this scenario, the information about the deep link can not be delivered to you in your Cocos2d-x C++ code. Once you enable your app to handle deep linking, you will get information about the deep link at a native level. For more information, check our chapters below on how to enable deep linking in Android apps.

### <a id="deeplinking-deferred">Deferred deep linking

In order to get information about the URL content in a deferred-deep-linking scenario, you will need to set a callback method on the `AdjustConfig2dx` object which will receive a `std::string` parameter, where the content of the URL will be delivered. You should set this method on the `AdjustConfig2dx` object instance by calling the `setDeferredDeeplinkCallback` method:

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

If nothing is set here, **the Adjust SDK will always try to launch the URL by default**.

### <a id="deeplinking-android">Deep link handling for Android apps

**This should be done in a native Android project.**

To set up your Android app to handle deep linking at a native level, please follow our [guide][android-deeplinking] in the official Android SDK README.

[adjust]:       http://adjust.com
[dashboard]:    http://adjust.com
[adjust.com]:   http://adjust.com

[maven]:                http://maven.org
[example]:              https://github.com/adjust/android_sdk/tree/master/Adjust/example
[releases]:         https://github.com/adjust/cocos2dx_sdk/releases
[multidex]:             https://developer.android.com/tools/building/multidex.html
[referrer]:             https://github.com/adjust/android_sdk/blob/master/doc/referrer.md
[deeplinking]:          https://docs.adjust.com/en/tracker-generation/#deeplinking
[google-ad-id]:         https://developer.android.com/google/play-services/id.html
[eclipse-guide]:    https://github.com/adjust/cocos2dx_sdk/blob/master/doc/android/eclipse.md
[event-tracking]:       https://docs.adjust.com/en/event-tracking
[eclipse-library]:    http://developer.android.com/tools/projects/projects-eclipse.html#ReferencingLibraryProject
[callbacks-guide]:      https://docs.adjust.com/en/callbacks
[special-partners]:     https://docs.adjust.com/en/special-partners
[attribution-data]:     https://github.com/adjust/sdks/blob/master/doc/attribution-data.md
[application-name]:     http://developer.android.com/guide/topics/manifest/application-element.html#nm
[currency-conversion]:  https://docs.adjust.com/en/event-tracking/#tracking-purchases-in-different-currencies
[android-deeplinking]:  https://github.com/adjust/android_sdk#deeplinking
[android-application]:  http://developer.android.com/reference/android/app/Application.html
[google-launch-modes]:  http://developer.android.com/guide/topics/manifest/activity-element.html#lmode
[google-play-services]: http://developer.android.com/google/play-services/setup.html

[gps-gradle]:        https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/android/android_studio/gps_gradle.png
[log-message]:       https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/android/android_studio/log_message.png
[gps-manifest]:      https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/android/android_studio/gps_manifest.png
[add-adjust2dx]:     https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/android/android_studio/add_adjust2dx.png
[proguard-rules]:    https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/android/android_studio/proguard_rules.png
[add-android-jar]:   https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/android/android_studio/add_android_jar.png

[add-android-files]: https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/android/android_studio/add_android_files.png
[add-to-android-mk]: https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/android/android_studio/add_to_android_mk.png
[broadcast-receiver]: https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/android/android_studio/broadcast_receiver.png
[on-resume-on-pause]: https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/android/android_studio/on_resume_on_pause.png
[manifest-permissions]: https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/android/android_studio/manifest_permissions.png

## <a id="license">License

The Adjust SDK is licensed under the MIT License.

Copyright (c) 2012-2017 Adjust GmbH,
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
