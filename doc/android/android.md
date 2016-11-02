## Summary

This is the Cocos2d-x SDK of adjust™. You can read more about adjust™ at [adjust.com].

## Table of contents

* [Basic integration](#basic-integration)
   * [Get the SDK](#sdk-get)
   * [Add the SDK to your project](#sdk-add)
   * [Add the C++ source file definitions](#sdk-cpp-files)
   * [Add the adjust library to your project](#sdk-library)
   * [Add Google Play Services](#sdk-gps)
   * [Add permissions](#sdk-permissions)
   * [Add broadcast receiver](#sdk-broadcast-receiver)
   * [Integrate the SDK into your app](#sdk-integrate)
   * [Adjust logging](#sdk-logging)
   * [Session tracking](#sdk-session-tracking)
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
    * [Push token](#push-token)
    * [Pre-installed trackers](#pre-installed-trackers)
    * [Deep linking](#deeplinking)
        * [Standard deep linking scenario](#deeplinking-standard)
        * [Deferred deep linking scenario](#deeplinking-deferred)
        * [Deep linking handling for Android app](#deeplinking-android)
* [License](#license)


## <a id="basic-integration">Basic integration

We will describe the steps to integrate the adjust SDK into your Cocos2d-x Android project.

### <a id="sdk-get">Get the SDK

Download the latest version from our [releases page][releases]. Extract the archive into a directory of your choice.

### <a id="sdk-add">Add the SDK to your project

In this guide we assume that you are using `Android Studio` for development. If you are using `Eclipse`, please read our 
[Cocos2d-x Eclipse guide][eclipse_guide].

Take the files from the `Adjust` folder and add them to your Android project.

![][add_android_files]

### <a id="sdk-cpp-files">Add the C++ source file definitions

Make sure to also add the paths of the adjust C++ files to the `LOCAL_SRC_FILES` section in your `Android.mk` file.

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

![][add_to_android_mk]

### <a id="sdk-library">Add the adjust library to your project

Take the `adjust-android.jar` library and copy it to your project's `libs` folder.

![][add_android_jar]

### <a id="sdk-gps">Add Google Play Services

Since the 1st of August of 2014, apps in the Google Play Store must use the [Google Advertising ID][google_ad_id] to uniquely 
identify devices. To allow the adjust SDK to use the Google Advertising ID, you must integrate the [Google Play Services]
[google_play_services]. If you haven't done this yet, follow these steps:

1. Open the `build.gradle` file of your app and find the `dependencies` block. Add the following line:

    ```
    compile 'com.google.android.gms:play-services-analytics:9.3.0'
    ```

    ![][gps_gradle]

2. Skip this step if you are using version 7 or later of Google Play Services:
   In the Package Explorer open the `AndroidManifest.xml` of your Android project.  Add the following `meta-data` tag inside   
   the `<application>` element.

    ```xml
    <meta-data android:name="com.google.android.gms.version"
               android:value="@integer/google_play_services_version" />
    ```

    ![][gps_manifest]

### <a id="sdk-permissions">Add permissions

In the Package Explorer open the `AndroidManifest.xml` of your Android project. Add the `uses-permission` tag for `INTERNET` 
if it's not present already.

```xml
<uses-permission android:name="android.permission.INTERNET" />
```

If you are **not targeting the Google Play Store**, add both of these permissions instead:

```xml
<uses-permission android:name="android.permission.INTERNET" />
<uses-permission android:name="android.permission.ACCESS_WIFI_STATE" />
```

![][manifest_permissions]

If you are using Proguard, add these lines to your Proguard file:

```
-keepclassmembers enum * {
    public static **[] values();
    public static ** valueOf(java.lang.String);
}
-keep class com.adjust.sdk.plugin.MacAddressUtil {
    java.lang.String getMacAddress(android.content.Context);
}
-keep class com.adjust.sdk.plugin.AndroidIdUtil {
    java.lang.String getAndroidId(android.content.Context);
}
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
```

If you are **not targeting the Google Play Store**, you can remove the `com.google.android.gms` rules.

![][proguard_rules]

### <a id="sdk-permissions">Add broadcast receiver

In your `AndroidManifest.xml` add the following `receiver` tag inside the `application` tag.

```xml
<receiver
    android:name="com.adjust.sdk.AdjustReferrerReceiver"
    android:exported="true" >
    <intent-filter>
        <action android:name="com.android.vending.INSTALL_REFERRER" />
    </intent-filter>
</receiver>
```

![][broadcast_receiver]

We use this broadcast receiver to retrieve the install referrer, in order to improve conversion tracking.

If you are already using a different broadcast receiver for the `INSTALL_REFERRER` intent, then follow [these instructions]
[referrer] to add the call to the Adjust broadcast receiver.

### <a id="sdk-integrate">Integrate the SDK into your app

In the Package Explorer, open the source file of your app delegate.  Add the import statement at the top of the file, then add 
the following call to Adjust in the `applicationDidFinishLaunching` of your app delegate:

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

**Important:** This value should be set to `AdjustEnvironmentSandbox2dx` if and only if you or someone else is testing your 
app. Make sure to set the environment to `AdjustEnvironmentProduction2dx` just before you publish the app. Set it back to 
`AdjustEnvironmentSandbox2dx` when you start developing and testing it again.

We use this environment to distinguish between real traffic and test traffic from test devices. It is very important that you 
keep this value meaningful at all times! This is especially important if you are tracking revenue.

### <a id="sdk-logging">Adjust logging

You can increase or decrease the amount of logs you see in tests by calling `setLogLevel` on your `AdjustConfig2dx` instance 
with one of the following parameters:

```cpp
adjustConfig.setLogLevel(AdjustLogLevel2dxVerbose);     // enable all logging
adjustConfig.setLogLevel(AdjustLogLevel2dxDebug);       // enable more logging
adjustConfig.setLogLevel(AdjustLogLevel2dxInfo);        // the default
adjustConfig.setLogLevel(AdjustLogLevel2dxWarn);        // disable info logging
adjustConfig.setLogLevel(AdjustLogLevel2dxError);       // disable warnings as well
adjustConfig.setLogLevel(AdjustLogLevel2dxAssert);      // disable errors as well
adjustConfig.setLogLevel(AdjustLogLevel2dxSuppress);    // disable all log output
```

In case you want to use suppress log level, you should initialise `AdjustConfig2dx` instance with usage of constructor which 
receives additional `bool` parameter which indicates whether suppress log level should be enabled or not:

```cpp
std::string appToken = "{YourAppToken}";
std::string environment = AdjustEnvironmentSandbox2dx;

AdjustConfig2dx adjustConfig = AdjustConfig2dx(appToken, environment, true);
adjustConfig.setLogLevel(AdjustLogLevel2dxSuppress);
```

### <a id="sdk-session-tracking">Session tracking

**Please, pay attention to this chapter and implement session tracking properly in your app**.

To provide proper session tracking it is required to call certain Adjust methods every time app goes to background or comes to 
foreground. Otherwise the SDK might miss a session start or session end. In order to do so you should follow these steps:

1. Open the app delegate file.
2. Add call to `onResume` method in `applicationWillEnterForeground` method.
3. Add call to `onPause` method in `applicationDidEnterBackground` method.

After these steps your app delegate should look like this:

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

![][on_resume_on_pause]

## <a id="sdk-build">Build your app

Build and run your Android app. In your LogCat viewer you can set the filter `tag:Adjust` to hide all other logs. After your 
app has launched you should see the following Adjust log: `Install tracked`

![][log_message]

## <a id="additional-features">Additional features

Once you integrate the adjust SDK into your project, you can take advantage of the following features.

### <a id="event-tracking">Event tracking

With adjust, you can track every event that you want. Suppose you want to track every tap on a button. Simply create a new 
event token in your [dashboard]. Let's say that event token is `abc123`. You can add the following line in your button’s 
click handler method to track the click:

```cpp
AdjustEvent2dx adjustEvent = AdjustEvent2dx("abc123");
Adjust2dx::trackEvent(adjustEvent);
```

### <a id="revenue-tracking">Revenue tracking

If your users can generate revenue by tapping on advertisements or making In-App Purchases, then you can track those revenues 
with events. Let's say a tap is worth €0.01. You could track the revenue event like this:

```cpp
AdjustEvent2dx adjustEvent = AdjustEvent2dx("abc123");

adjustEvent.setRevenue(0.01, "EUR");

Adjust2dx::trackEvent(adjustEvent);
```

When you set a currency token, adjust will automatically convert the incoming revenues into a reporting revenue of your 
choice. Read more about [currency conversion here][currency-conversion].

You can read more about revenue and event tracking in the [event tracking guide][event-tracking].

### <a id="revenue-deduplication"></a>Revenue deduplication

You can also add an optional transaction ID to avoid tracking duplicate revenues. The last ten transaction IDs are 
remembered, and revenue events with duplicate transaction IDs are skipped. This is especially useful for In-App Purchase 
tracking. You can see an example below.

If you want to track in-app purchases, please make sure to call the `trackEvent` only if the transaction is finished and item 
is purchased. That way you can avoid tracking revenue that is not actually being generated.

```cpp
AdjustEvent2dx adjustEvent = AdjustEvent2dx("abc123");

adjustEvent.setRevenue(0.01, "EUR");
adjustEvent.setTransactionId("transactionID");

Adjust2dx::trackEvent(adjustEvent);
```

**Note**: Transaction ID is the iOS term, unique identifier for successfully finished Android In-App-Purchases is named 
**Order ID**.

### <a id="iap-verification">In-App Purchase verification

In-App purchase verification can be done with Cocos2d-x purchase SDK which is currently being developed and will soon be 
publicly available. For more information, please contact support@adjust.com.

### <a id="callback-parameters">Callback parameters

You can register a callback URL for your events in your [dashboard]. We will send a GET request to that URL whenever the 
event is tracked. You can add callback parameters to that event by calling `addCallbackParameter` on the event before 
tracking it. We will then append these parameters to your callback URL.

For example, suppose you have registered the URL `http://www.adjust.com/callback` for your event with event token `abc123`
and execute the following lines:

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

It should be mentioned that we support a variety of placeholders like `{idfa}` that can be used as parameter values. In the 
resulting callback this placeholder would be replaced with the ID for Advertisers of the current device. Also note that we 
don't store any of your custom parameters, but only append them to your callbacks. If you haven't registered a callback for 
an event, these parameters won't even be read.

You can read more about using URL callbacks, including a full list of available values, in our 
[callbacks guide][callbacks-guide].

### <a id="partner-parameters">Partner parameters

You can also add parameters to be transmitted to network partners, for the integrations that have been activated in your 
adjust dashboard.

This works similarly to the callback parameters mentioned above, but can be added by calling the `addPartnerParameter` method 
on your `AdjustEvent2dx` instance.

```cpp
AdjustEvent2dx adjustEvent = AdjustEvent2dx("abc123");

adjustEvent.addPartnerParameter("key", "value");
adjustEvent.addPartnerParameter("foo", "bar");

Adjust2dx::trackEvent(adjustEvent);
```

You can read more about special partners and these integrations in our [guide to special partners][special-partners].

### <a id="session-parameters">Session parameters

Some parameters are saved to be sent in every event and session of the adjust SDK. Once you have added any of these
parameters, you don't need to add them every time, since they will be saved locally. If you add the same parameter twice,
there will be no effect.

These session parameters can be called before the adjust SDK is launched to make sure they are sent even on install. If you
need to send them with an install, but can only obtain the needed values after launch, it's possible to
[delay](#delay-start) the first launch of the adjust SDK to allow this behaviour.

### <a id="session-callback-parameters"> Session callback parameters

The same callback parameters that are registered for [events](#callback-parameters) can be also saved to be sent in every
event or session of the adjust SDK.

The session callback parameters have a similar interface of the event callback parameters. Instead of adding the key and
it's value to an event, it's added through a call to method `addSessionCallbackParameter` of the `Adjust2dx` instance.

```cpp
Adjust2dx::addSessionCallbackParameter("foo", "bar");
```

The session callback parameters will be merged with the callback parameters added to an event. The callback parameters added 
to an event have precedence over the session callback parameters. Meaning that, when adding a callback parameter to an event 
with the same key to one added from the session, the value that prevails is the callback parameter added to the event.

It's possible to remove a specific session callback parameter by passing the desiring key to the method 
`removeSessionCallbackParameter` of the `Adjust2dx` instance.

```cpp
Adjust2dx::removeSessionCallbackParameter("foo");
```

If you wish to remove all key and values from the session callback parameters, you can reset it with the method
`resetSessionCallbackParameters` of the `Adjust2dx` instance.

```cpp
Adjust2dx::resetSessionCallbackParameters();
```

### <a id="session-partner-parameters">Session partner parameters

In the same way that there is [session callback parameters](#session-callback-parameters) that are sent for every event or
session of the adjust SDK, there is also session partner parameters.

These will be transmitted to network partners, for the integrations that have been activated in your adjust [dashboard].

The session partner parameters have a similar interface to the event partner parameters. Instead of adding the key and its
value to an event, it's added through a call to method `addSessionPartnerParameter` of the `Adjust2dx` instance.

```cpp
Adjust2dx::addSessionPartnerParameter("foo", "bar");
```

The session partner parameters will be merged with the partner parameters added to an event. The partner parameters added
to an event have precedence over the session partner parameters. Meaning that, when adding a partner parameter to an event
with the same key to one added from the session, the value that prevails is the partner parameter added to the event.

It's possible to remove a specific session partner parameter by passing the desiring key to the method
`removeSessionPartnerParameter` of the `Adjust2dx` instance.

```cpp
Adjust2dx::removeSessionPartnerParameter("foo");
```

If you wish to remove all keys and values from the session partner parameters, you can reset it with the method
`resetSessionPartnerParameters` of the `Adjust2dx` instance.

```cpp
Adjust2dx::resetSessionPartnerParameters();
```

### <a id="delay-start">Delay start

Delaying the start of the adjust SDK allows your app some time to obtain session parameters, such as unique identifiers, to
be sent on install.

Set the initial delay time in seconds with the `setDelayStart` method of the `AdjustConfig2dx` instance:

```cpp
config.setDelayStart(5.5);
```

In this case this will make the adjust SDK not send the initial install session and any event created for 5.5 seconds.
After this time is expired or if you call `Adjust2dx::sendFirstPackages()` in the meanwhile, every session parameter will be
added to the delayed install session and events and the adjust SDK will resume as usual.

**The maximum delay start time of the adjust SDK is 10 seconds**.

### <a id="attribution-callback">Attribution callback

adjust can also send you a callback upon change of attribution. Due to the different sources considered for attribution, this 
information cannot be provided synchronously. Follow these steps to implement the optional callback in your application:

1. Create void method which receives parameter of type `AdjustAttribution2dx`.

2. After creating instance of `AdjustConfig2dx`, call its `setAttributionCallback` method with the previously created method 
   as parameter.

The callback function will get called when the SDK receives final attribution data. Within the callback function you have 
access to the `attribution` parameter. Here is a quick summary of its properties:

- `std::string trackerToken` the tracker token of the current install.
- `std::string trackerName` the tracker name of the current install.
- `std::string network` the network grouping level of the current install.
- `std::string campaign` the campaign grouping level of the current install.
- `std::string adgroup` the ad group grouping level of the current install.
- `std::string creative` the creative grouping level of the current install.
- `std::string clickLabel` the click label of the current install.

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

The callback functions will be called after the SDK tries to send a package to the server. Within the callback you have
access to a response data object specifically for the callback. Here is a quick summary of the session response data
properties:

- `std::string message` the message from the server or the error logged by the SDK.
- `std::string timestamp` timestamp from the server.
- `std::string adid` a unique device identifier provided by adjust.
- `std::string jsonResponse` the JSON object with the response from the server.

Both event response data objects contain:

- `std::string eventToken` the event token, if the package tracked was an event.

And both event and session failed objects also contain:

- `std::string willRetry` indicates there will be an attempt to resend the package at a later time.

### <a id="disable-tracking">Disable tracking

You can disable the adjust SDK from tracking by invoking the method `Adjust2dx::setEnabled` with the enabled parameter as
`false`. This setting is **remembered between sessions**, but it can only be activated after the first session.

```cpp
Adjust2dx::setEnabled(false);
```

You can verify if the adjust SDK is currently active with the method `Adjust2dx::isEnabled()`. It is always possible to  
activate the adjust SDK by invoking `Adjust2dx::setEnabled` with the parameter set to `true`.

### <a id="offline-mode">Offline mode

You can put the adjust SDK in offline mode to suspend transmission to our servers while retaining tracked data to be sent
later. When in offline mode, all information is saved in a file, so be careful not to trigger too many events while in 
offline mode.

You can activate offline mode by calling `Adjust2dx::setOfflineMode` with the parameter `true`.

```cpp
Adjust2dx::setOfflineMode(true);
```

Conversely, you can deactivate offline mode by calling `Adjust2dx::setOfflineMode` with `false`. When the adjust SDK is put 
back in online mode, all saved information is send to our servers with the correct time information.

Unlike disabling tracking, **this setting is not remembered** between sessions. This means that the SDK is in online mode
whenever it is started, even if the app was terminated in offline mode.

### <a id="event-buffering">Event buffering

If your app makes heavy use of event tracking, you might want to delay some HTTP requests in order to send them in one batch
every minute. You can enable event buffering with your `AdjustConfig2dx` instance by calling `setEventBufferingEnabled` 
method:

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

The default behaviour of the adjust SDK is to **pause sending HTTP requests while the app is in the background**. You can 
change this in your `AdjustConfig2dx` instance by calling `setSendInBackground` method:

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

Certain services (such as Google Analytics) require you to coordinate Device and Client IDs in order to prevent duplicated
reporting.

The adjust SDK provides you with the possibility to read Google Advertising Identifier of the Android device on which your 
app is running. In order to do that, you can set the callback method which receives the `std::string` parameter. After  
setting this, if you invoke the method `getGoogleAdId` of the `Adjust2dx` instance and pass the defined callback method as a 
parameter, you will get the Google Advertising Identifier value in your callback method:

```cpp
static void adIdCallbackMethod(std::string adId) {
    CCLOG("\nAdvertising identifier = %s", adId.c_str());
    CCLOG("\n");
}

// ...

Adjust2dx::getGoogleAdId(adIdCallbackMethod);
```

### <a id="push-token">Push token

To send us the push notifications token, then add the following call to Adjust **whenever you get your token in the app or 
when it gets updated**:

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

If you are using the adjust tracker URL with an option to deep link into your app from the URL, there is the possibility to
get info about the deep link URL and its content. Hitting the URL can happen when the user has your app already installed
(standard deep linking scenario) or if they don't have the app on their device (deferred deep linking scenario). In the
standard deep linking scenario, Android platform natively offers the possibility for you to get the info about the deep link
content. Deferred deep linking scenario is something which Android platform doesn't support out of box and for this case,
the adjust SDK will offer you the mechanism to get the info about the deep link content.

You need to set up deep linking handling in your app **on native level** - in your generated Android project.

### <a id="deeplinking-standard">Standard deep linking scenario

Unfortunatelly, in this scenario the information about the deep link can not be delivered to you in your Cocos2d-x C++ code.
Once you enable your app to handle deep linking, you will get information about the deep link on native level. For more
information check our chapters below on how to enable deep linking for Android apps.

### <a id="deeplinking-deferred">Deferred deep linking scenario

In order to get info about the URL content in a deferred deep linking scenario, you should set a callback method on the
`AdjustConfig2dx` object which will receive one `std::string` parameter where the content of the URL will be delivered. You
should set this method on the `AdjustConfig2dx` object instance by calling the method `setDeferredDeeplinkCallback`:

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

<a id="deeplinking-deferred-open">In deferred deep linking scenario, there is one additional setting which can be set on the
deferred deep link callback method. Once the adjust SDK gets the deferred deep link info, we are offering you the possibility 
to choose whether our SDK should open this URL or not. You can choose to set this option by setting the return value of your 
deferred deep link callback method.

If nothing is set, **the adjust SDK will always try to launch the URL by default**.

### <a id="deeplinking-android">Deep linking handling for Android app

**This should be done in native Android project.**

To set up your Android app to handle deep linking on native level, please follow our [guide][android-deeplinking] in the 
official Android SDK README.

[adjust]:	http://adjust.com
[dashboard]:    http://adjust.com
[adjust.com]:  	http://adjust.com

[maven]:                http://maven.org
[example]:              https://github.com/adjust/android_sdk/tree/master/Adjust/example
[releases]:      	https://github.com/adjust/cocos2dx_sdk/releases
[multidex]:             https://developer.android.com/tools/building/multidex.html
[referrer]:             https://github.com/adjust/android_sdk/blob/master/doc/referrer.md
[deeplinking]:          https://docs.adjust.com/en/tracker-generation/#deeplinking
[google_ad_id]:         https://developer.android.com/google/play-services/id.html
[eclipse_guide]:	https://github.com/adjust/cocos2dx_sdk/blob/master/doc/android/eclipse.md
[event-tracking]:       https://docs.adjust.com/en/event-tracking
[eclipse_library]:	http://developer.android.com/tools/projects/projects-eclipse.html#ReferencingLibraryProject
[callbacks-guide]:      https://docs.adjust.com/en/callbacks
[special-partners]:     https://docs.adjust.com/en/special-partners
[attribution-data]:     https://github.com/adjust/sdks/blob/master/doc/attribution-data.md
[application_name]:     http://developer.android.com/guide/topics/manifest/application-element.html#nm
[currency-conversion]:  https://docs.adjust.com/en/event-tracking/#tracking-purchases-in-different-currencies
[android-deeplinking]:	https://github.com/adjust/android_sdk#deeplinking
[android_application]:  http://developer.android.com/reference/android/app/Application.html
[google-launch-modes]:  http://developer.android.com/guide/topics/manifest/activity-element.html#lmode
[google_play_services]: http://developer.android.com/google/play-services/setup.html

[gps_gradle]:	     https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/android/android_studio/gps_gradle.png
[log_message]: 	     https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/android/android_studio/log_message.png
[gps_manifest]:      https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/android/android_studio/gps_manifest.png
[add_adjust2dx]:     https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/android/android_studio/add_adjust2dx.png
[proguard_rules]:    https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/android/android_studio/proguard_rules.png
[add_android_jar]:   https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/android/android_studio/add_android_jar.png
[add_android_files]: https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/android/android_studio/add_android_files.png
[add_to_android_mk]: https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/android/android_studio/add_to_android_mk.png

[broadcast_receiver]:	https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/android/android_studio/broadcast_receiver.png
[on_resume_on_pause]:	https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/android/android_studio/on_resume_on_pause.png
[manifest_permissions]:	https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/android/android_studio/manifest_permissions.png

## <a id="license">License

The adjust SDK is licensed under the MIT License.

Copyright (c) 2012-2016 adjust GmbH,
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
