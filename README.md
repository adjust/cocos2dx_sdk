## Summary

This is the Cocos2d-x SDK of Adjust™. You can read more about Adjust™ at [Adjust.com].

## Table of contents

* [Basic integration](#basic-integration)
   * [Get the SDK](#sdk-get)
   * [Add the SDK to your project](#sdk-add)
   * [Adjust project settings](#sdk-project-settings)
      * [[Android] SDK JAR library](#android-sdk-jar)
      * [[Android] Permissions](#android-permissions)
      * [[Android] Google Play Services](#android-gps)
      * [[Android] Proguard settings](#android-proguard)
      * [[Android] Install referrer](#android-referrer)
         * [Google Play Referrer API](#android-referrer-gpr-api)
         * [Google Play Store intent](#android-referrer-gps-intent)
         * [Huawei Referrer API](#android-huawei-referrer-api)
      * [[iOS] Frameworks](#ios-frameworks)
      * [[iOS] Additional linker flags](#ios-linker-flags)
   * [Integrate the SDK into your app](#sdk-integrate)
   * [Adjust logging](#sdk-logging)
   * [Android session tracking](#sdk-android-session-tracking)
   * [Build your app](#sdk-build)
* [Additional features](#additional-features)
   * [AppTrackingTransparency framework](#att-framework)
      * [App-tracking authorisation wrapper](#ata-wrapper)
      * [Get current authorisation status](#ata-getter)
      * [Check for ATT status change](#att-status-change)
   * [SKAdNetwork framework](#skadn-framework)
      * [Update SKAdNetwork conversion value](#skadn-update-conversion-value)
      * [Conversion value updated callback](#skadn-cv-updated-callback)
   * [Event tracking](#event-tracking)
      * [Revenue tracking](#revenue-tracking)
      * [Revenue deduplication](#revenue-deduplication)
      * [Callback parameters](#callback-parameters)
      * [Partner parameters](#partner-parameters)
      * [Callback identifier](#callback-id)
   * [Subscription tracking](#subscription-tracking)
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
   * [Third-party sharing](#third-party-sharing)
      * [Disable third-party sharing](#disable-third-party-sharing)
      * [Enable third-party sharing](#enable-third-party-sharing)
   * [Measurement consent](#measurement-consent)
   * [SDK signature](#sdk-signature)
   * [Background tracking](#background-tracking)
   * [Device IDs](#device-ids)
      * [iOS advertising identifier](#di-idfa)
      * [Google Play Services advertising identifier](#di-gps-adid)
      * [Amazon advertising identifier](#di-fire-adid)
      * [Adjust device identifier](#di-adid)
   * [Set external device ID](#set-external-device-id)
   * [User attribution](#user-attribution)
   * [Push token](#push-token)
   * [Pre-installed trackers](#pre-installed-trackers)
   * [Deep linking](#deeplinking)
      * [Standard deep linking](#deeplinking-standard)
      * [Deferred deep linking](#deeplinking-deferred)
      * [Deep link handling for iOS apps](#deeplinking-ios)
      * [Deep link handling for Android apps](#deeplinking-android)
   * [Data residency](#data-residency)
   * [COPPA compliance](#coppa-compliance)
   * [Play Store Kids Apps](#play-store-kids-apps)
* [License](#license)

## <a id="basic-integration"></a>Basic integration

These are the minimal steps required to integrate the Adjust SDK into your Cocos2d-x project.

### <a id="sdk-get"></a>Get the SDK

Download the latest version from our [releases page][releases]. Extract the archive into a directory of your choosing.

### <a id="sdk-add"></a>Add the SDK to your project

Take the C++ source files from the `src` folder and add them to your Cocos2d-x project.

Inside Android Studio project, you need to add the paths of the Adjust C++ files to the `LOCAL_SRC_FILES` section in your `Android.mk` file:

```mk
$(LOCAL_PATH)/../../../Classes/Adjust/AdjustConfig2dx.cpp \
$(LOCAL_PATH)/../../../Classes/Adjust/AdjustAttribution2dx.cpp \
$(LOCAL_PATH)/../../../Classes/Adjust/AdjustProxy2dx.cpp \
$(LOCAL_PATH)/../../../Classes/Adjust/AdjustEvent2dx.cpp \
$(LOCAL_PATH)/../../../Classes/Adjust/Adjust2dx.cpp \
$(LOCAL_PATH)/../../../Classes/Adjust/AdjustEventFailure2dx.cpp \
$(LOCAL_PATH)/../../../Classes/Adjust/AdjustEventSuccess2dx.cpp \
$(LOCAL_PATH)/../../../Classes/Adjust/AdjustSessionFailure2dx.cpp \
$(LOCAL_PATH)/../../../Classes/Adjust/AdjustSessionSuccess2dx.cpp \
$(LOCAL_PATH)/../../../Classes/Adjust/AdjustAppStoreSubscription2dx.cpp \
$(LOCAL_PATH)/../../../Classes/Adjust/AdjustPlayStoreSubscription2dx.cpp \
$(LOCAL_PATH)/../../../Classes/Adjust/AdjustThirdPartySharing2dx.cpp \
$(LOCAL_PATH)/../../../Classes/Adjust/AdjustAdRevenue2dx.cpp
```

### <a id="sdk-project-settings"></a>Adjust project settings

Once the Adjust SDK has been added to your app, certain tweaks need to be performed so that the Adjust SDK can work properly. Below you can find a description of every additional thing that you need to do after you've added the Adjust SDK into to your app.

### <a id="android-sdk-jar"></a>[Android] SDK JAR library

Take the `adjust-android.jar` library and copy it to your project's `libs` folder.

**Note**: Please, have in mind that `adjust-android.jar` library, which is being published as part of each Cocos2d-x Github release, **is not the same** as `adjust-android.jar` which you may find in Maven repository or as part of our official Android SDK Github releases. `adjust-android.jar` which is published with each Cocos2d-x release is specifically tweaked for Cocos2d-x SDK and only official versions of this file which are part of Cocos2d-x Github releases should be used inside of your app. **Do not** use `adjust-android.jar` files from official Android SDK releases.

### <a id="android-permissions"></a>[Android] Permissions

Please add the following permissions, which the Adjust SDK needs, if they are not already present in your `AndroidManifest.xml` file:

```xml
<uses-permission android:name="android.permission.INTERNET"/>
<uses-permission android:name="android.permission.ACCESS_NETWORK_STATE"/>
```

If you are **not targeting the Google Play Store**, please also add the following permission:

```xml
<uses-permission android:name="android.permission.ACCESS_WIFI_STATE"/>
```

#### <a id="gps-adid-permission"></a>Add permission to gather Google advertising ID

If you are targeting Android 12 and above (API level 31), you need to add the `com.google.android.gms.AD_ID` permission to read the device's advertising ID. Add the following line to your `AndroidManifest.xml` to enable the permission.

```xml
<uses-permission android:name="com.google.android.gms.permission.AD_ID"/>
```

For more information, see [Google's `AdvertisingIdClient.Info` documentation](https://developers.google.com/android/reference/com/google/android/gms/ads/identifier/AdvertisingIdClient.Info#public-string-getid).

### <a id="android-gps"></a>[Android] Google Play Services

Since August 1, 2014, apps in the Google Play Store must use the [Google advertising ID][google-ad-id] to uniquely identify each device. To allow the Adjust SDK to use the Google advertising ID, you must integrate [Google Play Services][google-play-services].

Open the `build.gradle` file of your app and find the `dependencies` block. Add the following line:

```
implementation 'com.google.android.gms:play-services-analytics:16.0.1'
```

To check whether the analytics part of the Google Play Services library has been successfully added to your app, you should start your app by configuring the SDK to run in **sandbox** mode and set the log level to **verbose**. After that, track a session or some events in your app and observe the list of parameters in the verbose logs which are being read once the session or event has been tracked. If you see a parameter called `gps_adid` in there, you have successfully added the analytics part of the Google Play Services library to your app and our SDK is reading the necessary information from it.

**If you are using Eclipse as your IDE:**

In order to add Google Play Services to your project, you should add `google-play-services_lib` from Android SDK folder into your app project in Eclipse. `google-play-services_lib` is part of the Android SDK, which you may already have installed.

There are two main ways to download the Android SDK. If you are using any tool which has the `Android SDK Manager`, you should download `Android SDK Tools`. Once installed, you can find the libraries in the `SDK_FOLDER/extras/google/google_play_services/libproject/` folder.

If you are not using any tool which has Android SDK Manager, you should download the standalone version of Android SDK from [official page][android-sdk-download]. By downloading this, you will have only a basic version of the Android SDK which doesn't include the Android SDK Tools. There are more detailed instructions on how to download these in the readme file provided by Google, called `SDK Readme.txt`, which is placed in Android SDK folder.

After this, open the `AndroidManifest.xml` file of your Android project and add the following `meta-data` tag inside the `<application>` element:

```xml
<meta-data android:name="com.google.android.gms.version"
           android:value="@integer/google-play-services_version" />
```

### <a id="android-proguard"></a>[Android] Proguard settings

If you are using Proguard, add these lines to your Proguard file:

```
-keep class com.adjust.sdk.** { *; }
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
-keep public class com.android.installreferrer.** { *; }
```

### <a id="android-referrer"></a>[Android] Install referrer

In order to correctly attribute an install of your Android app to its source, Adjust needs information about the **install referrer**. This can be obtained by using the **Google Play Referrer API** or by catching the **Google Play Store intent** with a broadcast receiver.

**Important**: The Google Play Referrer API is newly introduced by Google with the express purpose of providing a more reliable and secure way of obtaining install referrer information and to aid attribution providers in the fight against click injection. It is **strongly advised** that you support this in your application. The Google Play Store intent is a less secure way of obtaining install referrer information. It will continue to exist in parallel with the new Google Play Referrer API temporarily, but it is set to be deprecated in future.

#### <a id="android-referrer-gpr-api"></a>Google Play Referrer API

In order to support this in your app, please make sure to add following dependency to your `build.gradle` file:

```
implementation 'com.android.installreferrer:installreferrer:2.2'
```

Also, make sure that you have paid attention to the [Proguard settings](#android-proguard) chapter and that you have added all the rules mentioned in it, especially the one needed for this feature:

```
-keep public class com.android.installreferrer.** { *; }
```

This feature is supported if you are using the **Adjust SDK v4.12.0 or above**.

**If you are using Eclipse as your IDE:**

Google doesn't have any official documentation on how to integrate install referrer library in Eclipse project since Android Studio is official IDE for Android development. However, install library is an AAR library which can be downloaded and added to your Eclipse project (either as AAR library or JAR library if you extract it). Official install referrer library AAR library can be downloaded from [here][install-referrer-aar].

#### <a id="android-referrer-gps-intent"></a>Google Play Store intent

The Google Play Store `INSTALL_REFERRER` intent should be captured with a broadcast receiver. If you are **not using your own broadcast receiver** to receive the `INSTALL_REFERRER` intent, add the following `receiver` tag inside the `application` tag in your `AndroidManifest.xml`.

```xml
<receiver
    android:name="com.adjust.sdk.AdjustReferrerReceiver"
    android:exported="true" >
    <intent-filter>
        <action android:name="com.android.vending.INSTALL_REFERRER" />
    </intent-filter>
</receiver>
```

We use this broadcast receiver to retrieve the install referrer and pass it to our backend.

Please bear in mind that, if you are using your own broadcast receiver which handles the `INSTALL_REFERRER` intent, you don't need the Adjust broadcast receiver to be added to your manifest file. You can remove it, but, inside your own receiver, add the call to the Adjust broadcast receiver as described in our [Android guide][broadcast-receiver-custom].

#### <a id="android-huawei-referrer-api"></a>Huawei Referrer API

As of v4.22.0, the Adjust SDK supports install tracking on Huawei devices with Huawei App Gallery version 10.4 and higher. No additional integration steps are needed to start using the Huawei Referrer API.

### <a id="ios-frameworks"></a>[iOS] Frameworks

Select your project in the Project Navigator. In the left hand side of the main view, select your target. In the tab `Build Phases`, expand the group `Link Binary with Libraries`. On the bottom of that section click on the `+` button. Select below mentined frameworks and make sure to change the `Status` of frameworks to `Optional`. Adjust SDK uses these frameworks with following purpose:

* `iAd.framework` - to support Apple Search Ads campaigns
* `AdServices.framework` - to support Apple Search Ads campaigns
* `AdSupport.framework` - to read iOS Advertising Id (IDFA) value
* `StoreKit.framework` - to communicate with `SKAdNetwork` framework
* `AppTrackingTransparency.framework` - to ask for user's consent to be tracked and obtain status of that consent

### <a id="ios-linker-flags"></a>[iOS] Additional linker flags

In order to support categories from the `AdjustSdk.framework`, you should add a linker flag. Go to the `Build Settings` part of Project Settings and look for the `Other Linker Flags` option. Add an `-ObjC` flag to it.

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

### <a id="sdk-android-session-tracking"></a>Android session tracking

**Please pay close attention to this chapter and ensure that you implement session tracking correctly in your Android app**.

To provide proper session tracking, it is necessary to call certain Adjust methods every time your app moves to the background or comes to the foreground. Otherwise, the SDK might miss a session start or end. In order to do this, follow these steps:

- Open the app delegate file.
- Add a call to the `onResume` method in the `applicationWillEnterForeground` method.
- Add a call to the `onPause` method in the `applicationDidEnterBackground` method.

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

Adjust SDK is subscribed to iOS system notifications to get this information, so no need to add anything in particular in iOS app case.

## <a id="sdk-build"></a>Build your app

Build and run your app. If the build is successful, carefully read through the SDK logs in the console. After the initial app launch, you should see an **info** log entry saying `Install tracked`.

## <a id="additional-features"></a>Additional features

Once you integrate the Adjust SDK into your project, you can take advantage of the following features.

### <a id="att-framework"></a>AppTrackingTransparency framework

**Note**: This feature exists only in iOS platform.

For each package sent, the Adjust backend receives one of the following four (4) states of consent for access to app-related data that can be used for tracking the user or the device:

- Authorized
- Denied
- Not Determined
- Restricted

After a device receives an authorization request to approve access to app-related data, which is used for user device tracking, the returned status will either be Authorized or Denied.

Before a device receives an authorization request for access to app-related data, which is used for tracking the user or device, the returned status will be Not Determined.

If authorization to use app tracking data is restricted, the returned status will be Restricted.

The SDK has a built-in mechanism to receive an updated status after a user responds to the pop-up dialog, in case you don't want to customize your displayed dialog pop-up. To conveniently and efficiently communicate the new state of consent to the backend, Adjust SDK offers a wrapper around the app tracking authorization method described in the following chapter, App-tracking authorization wrapper.

### <a id="ata-wrapper"></a>App-tracking authorisation wrapper

**Note**: This feature exists only in iOS platform.

Adjust SDK offers the possibility to use it for requesting user authorization in accessing their app-related data. Adjust SDK has a wrapper built on top of the [requestTrackingAuthorizationWithCompletionHandler:](https://developer.apple.com/documentation/apptrackingtransparency/attrackingmanager/3547037-requesttrackingauthorizationwith?language=objc) method, where you can as well define the callback method to get information about a user's choice. Also, with the use of this wrapper, as soon as a user responds to the pop-up dialog, it's then communicated back using your callback method. The SDK will also inform the backend of the user's choice. Integer value will be delivered via your callback method with the following meaning:

- 0: `ATTrackingManagerAuthorizationStatusNotDetermined`
- 1: `ATTrackingManagerAuthorizationStatusRestricted`
- 2: `ATTrackingManagerAuthorizationStatusDenied`
- 3: `ATTrackingManagerAuthorizationStatusAuthorized`

To use this wrapper, you can call it as such:

```cpp
static void authorizationStatusCallback(int status) {
    switch (status) {
        case 0:
            // ATTrackingManagerAuthorizationStatusNotDetermined case
            break;
        case 1:
            // ATTrackingManagerAuthorizationStatusRestricted case
            break;
        case 2:
            // ATTrackingManagerAuthorizationStatusDenied case
            break;
        case 3:
            // ATTrackingManagerAuthorizationStatusAuthorized case
            break;
    }
}

// ...

Adjust2dx::requestTrackingAuthorizationWithCompletionHandler(authorizationStatusCallback);
```

### <a id="ata-getter"></a>Get current authorisation status

**Note**: This feature exists only in iOS platform.

To get the current app tracking authorization status you can call `getAppTrackingAuthorizationStatus` method of `Adjust2dx` class that will return one of the following possibilities:

* `0`: The user hasn't been asked yet
* `1`: The user device is restricted
* `2`: The user denied access to IDFA
* `3`: The user authorized access to IDFA
* `-1`: The status is not available

### <a id="att-status-change"></a>Check for ATT status change

In cases where you are not using [Adjust app-tracking authorization wrapper](#ata-wrapper), Adjust SDK will not be able to know immediately upon answering the dialog what is the new value of app-tracking status. In situations like this, if you would want Adjust SDK to read the new app-tracking status value and communicate it to our backend, make sure to make a call to this method:

```cpp
Adjust2dx::checkForNewAttStatus();
```

### <a id="skadn-framework"></a>SKAdNetwork framework

**Note**: This feature exists only in iOS platform.

If you have implemented the Adjust iOS SDK v4.23.0 or above and your app is running on iOS 14 and above, the communication with SKAdNetwork will be set on by default, although you can choose to turn it off. When set on, Adjust automatically registers for SKAdNetwork attribution when the SDK is initialized. If events are set up in the Adjust dashboard to receive conversion values, the Adjust backend sends the conversion value data to the SDK. The SDK then sets the conversion value. After Adjust receives the SKAdNetwork callback data, it is then displayed in the dashboard.

In case you don't want the Adjust SDK to automatically communicate with SKAdNetwork, you can disable that by calling the following method on configuration object:

```cpp
adjustConfig.deactivateSKAdNetworkHandling();
```

### <a id="skadn-update-conversion-value"></a>Update SKAdNetwork conversion value

**Note**: This feature exists only in iOS platform.

You can use Adjust SDK wrapper method `updateConversionValue` to update SKAdNetwork conversion value for your user:

```js
Adjust2dx::updateConversionValue(6);
```

### <a id="skadn-cv-updated-callback"></a>Conversion value updated callback

**Note**: This feature exists only in iOS platform.

You can register callback to get notified each time when Adjust SDK updates conversion value for the user.

```cpp
#include "Adjust/Adjust2dx.h"

// ...

static void conversionValueUpdatedCallbackMethod(int conversionValue) {
    CCLOG("\nConversion value updated!");
    CCLOG("\nConversion value: %d", conversionValue);
}

// ...

bool AppDelegate::applicationDidFinishLaunching() {
    std::string appToken = "{YourAppToken}";
    std::string environment = AdjustEnvironmentSandbox2dx;

    AdjustConfig2dx adjustConfig = AdjustConfig2dx(appToken, environment);
    adjustConfig.setLogLevel(AdjustLogLevel2dxVerbose);
    adjustConfig.setConversionValueUpdatedCallback(conversionValueUpdatedCallbackMethod);
    Adjust2dx::start(adjustConfig);

    // ...
}
```

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

It should be mentioned that we support a variety of placeholders, like `{idfa}` for iOS or `{gps_adid}` for Android, that can be used as parameter values.  In the resulting callback, the `{idfa}` placeholder would be replaced with the ID for advertisers of the current device for iOS and the `{gps_adid}` would be replaced with the Google advertising ID of the current device for Android. Also note that we don't store any of your custom parameters, but only append them to your callbacks. If you haven't registered a callback for an event, these parameters won't even be read.

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

### <a id="callback-id"></a>Callback identifier

You can also add custom string identifier to each event you want to track. This identifier will later be reported in event success and/or event failure callbacks to enable you to keep track on which event was successfully tracked or not. You can set this identifier by calling the `setCallbackId` method on your `AdjustEvent2dx` instance:

```cpp
AdjustEvent2dx adjustEvent = AdjustEvent2dx("abc123");
adjustEvent.setCallbackId("Your-Custom-Id");
Adjust2dx::trackEvent(adjustEvent);
```

### <a id="subscription-tracking"></a>Subscription tracking

**Note**: This feature is only available in the SDK v4.22.0 and above.

You can track App Store and Play Store subscriptions and verify their validity with the Adjust SDK. After a subscription has been successfully purchased, make the following call to the Adjust SDK:

**For App Store subscription:**

```cpp
AdjustAppStoreSubscription2dx subscription = AdjustAppStoreSubscription2dx(
    price,
    currency,
    transactionId,
    receipt
);
subscription.setTransactionDate(transactionDate);
subscription.setSalesRegion(salesRegion);

Adjust2dx::trackAppStoreSubscription(subscription);
```

**For Play Store subscription:**

```cpp
AdjustPlayStoreSubscription2dx subscription = AdjustPlayStoreSubscription2dx(
    price,
    currency,
    sku,
    orderId,
    signature,
    purchaseToken
);
subscription.setPurchaseTime(purchaseTime);

Adjust2dx::trackPlayStoreSubscription(subscription);
```

Subscription tracking parameters for App Store subscription:

- [price](https://developer.apple.com/documentation/storekit/skproduct/1506094-price?language=objc)
- currency (you need to pass [currencyCode](https://developer.apple.com/documentation/foundation/nslocale/1642836-currencycode?language=objc) of the [priceLocale](https://developer.apple.com/documentation/storekit/skproduct/1506145-pricelocale?language=objc) object)
- [transactionId](https://developer.apple.com/documentation/storekit/skpaymenttransaction/1411288-transactionidentifier?language=objc)
- [receipt](https://developer.apple.com/documentation/foundation/nsbundle/1407276-appstorereceipturl)
- [transactionDate](https://developer.apple.com/documentation/storekit/skpaymenttransaction/1411273-transactiondate?language=objc)
- salesRegion (you need to pass [countryCode](https://developer.apple.com/documentation/foundation/nslocale/1643060-countrycode?language=objc) of the [priceLocale](https://developer.apple.com/documentation/storekit/skproduct/1506145-pricelocale?language=objc) object)

Subscription tracking parameters for Play Store subscription:

- [price](https://developer.android.com/reference/com/android/billingclient/api/SkuDetails#getpriceamountmicros)
- [currency](https://developer.android.com/reference/com/android/billingclient/api/SkuDetails#getpricecurrencycode)
- [sku](https://developer.android.com/reference/com/android/billingclient/api/Purchase#getsku)
- [orderId](https://developer.android.com/reference/com/android/billingclient/api/Purchase#getorderid)
- [signature](https://developer.android.com/reference/com/android/billingclient/api/Purchase#getsignature)
- [purchaseToken](https://developer.android.com/reference/com/android/billingclient/api/Purchase#getpurchasetoken)
- [purchaseTime](https://developer.android.com/reference/com/android/billingclient/api/Purchase#getpurchasetime)

**Note:** Subscription tracking API offered by Adjust SDK expects all parameters to be passed as `string` values. Parameters described above are the ones which API exects you to pass to subscription object prior to tracking subscription. There are various libraries which are handling in app purchases in Cocos2d-x and each one of them should return information described above in some form upon successfully completed subscription purchase. You should locate where these parameters are placed in response you are getting from library you are using for in app purchases, extract those values and pass them to Adjust API as string values.

Just like with event tracking, you can attach callback and partner parameters to the subscription object as well:

**For App Store subscription:**

```cpp
AdjustAppStoreSubscription2dx subscription = AdjustAppStoreSubscription2dx(
    price,
    currency,
    transactionId,
    receipt
);
subscription.setTransactionDate(transactionDate);
subscription.setSalesRegion(salesRegion);

// add callback parameters
subscription.addCallbackParameter("key", "value");
subscription.addCallbackParameter("foo", "bar");

// add partner parameters
subscription.addPartnerParameter("key", "value");
subscription.addPartnerParameter("foo", "bar");

Adjust2dx::trackAppStoreSubscription(subscription);
```

**For Play Store subscription:**

```cpp
AdjustPlayStoreSubscription2dx subscription = AdjustPlayStoreSubscription2dx(
    price,
    currency,
    sku,
    orderId,
    signature,
    purchaseToken
);
subscription.setPurchaseTime(purchaseTime);

// add callback parameters
subscription.addCallbackParameter("key", "value");
subscription.addCallbackParameter("foo", "bar");

// add partner parameters
subscription.addPartnerParameter("key", "value");
subscription.addPartnerParameter("foo", "bar");

Adjust2dx::trackPlayStoreSubscription(subscription);
```

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

- Create a void method which receives an `AdjustAttribution2dx` parameter.
- After creating an `AdjustConfig2dx` instance, call its `setAttributionCallback` method with the previously created method as a parameter.

The callback function will be called when the SDK receives the final attribution data. Within the callback function, you have access to the `attribution` parameter. Here is a quick summary of its properties:

- `std::string trackerToken` the tracker token of the current attribution.
- `std::string trackerName` the tracker name of the current attribution.
- `std::string network` the network grouping level of the current attribution.
- `std::string campaign` the campaign grouping level of the current attribution.
- `std::string adgroup` the ad group grouping level of the current attribution.
- `std::string creative` the creative grouping level of the current attribution.
- `std::string clickLabel` the click label of the current attribution.
- `std::string adid` the Adjust device identifier.
- `std::string costType` the cost type.
- `double costAmount` the cost amount.
- `std::string costCurrency` the cost currency.

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
    CCLOG("\nCost type: %s", attribution.getCostType().c_str());
    CCLOG("\nCost amount: %f", attribution.getCostAmount());
    CCLOG("\nCost currency: %s", attribution.getCostCurrency().c_str());
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

**Note**: The cost data - `costType`, `costAmount` & `costCurrency` are only available when configured in `AdjustConfig2dx` by calling `setNeedsCost` method. If not configured or configured, but not being part of the attribution, string fields will have value `null` and double field will be 0. This feature is available in SDK v4.29.0 and above.

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
    CCLOG("\Callback ID: %s", eventSuccess.getCallbackId().c_str());
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
    CCLOG("\Callback ID: %s", eventFailure.getCallbackId().c_str());
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
- `std::string callbackId` the custom defined callback ID set on event object.

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

## <a id="third-party-sharing"></a>Third-party sharing for specific users

You can notify Adjust when a user disables, enables, and re-enables data sharing with third-party partners.

### <a id="disable-third-party-sharing"></a>Disable third-party sharing for specific users

Call the following method to instruct the Adjust SDK to communicate the user's choice to disable data sharing to the Adjust backend:

```cpp
AdjustThirdPartySharing2dx adjustThirdPartySharing = new AdjustThirdPartySharing2dx(false);
Adjust2dx::trackThirdPartySharing(adjustThirdPartySharing);
```

Upon receiving this information, Adjust will block the sharing of that specific user's data to partners and the Adjust SDK will continue to work as usual.

### <a id="enable-third-party-sharing">Enable or re-enable third-party sharing for specific users</a>

Call the following method to instruct the Adjust SDK to communicate the user's choice to share data or change data sharing, to the Adjust backend:

```cpp
AdjustThirdPartySharing2dx adjustThirdPartySharing = new AdjustThirdPartySharing2dx(true);
Adjust2dx::trackThirdPartySharing(adjustThirdPartySharing);
```

Upon receiving this information, Adjust changes sharing the specific user's data to partners. The Adjust SDK will continue to work as expected.

Call the following method to instruct the Adjust SDK to send the granular options to the Adjust backend:

```cpp
AdjustThirdPartySharing2dx adjustThirdPartySharing = new AdjustThirdPartySharing2dx();
adjustThirdPartySharing.addGranularOption("PartnerA", "foo", "bar");
Adjust2dx::trackThirdPartySharing(adjustThirdPartySharing);
```

### <a id="measurement-consent"></a>Consent measurement for specific users

You can notify Adjust when a user exercises their right to change data sharing with partners for marketing purposes, but they allow data sharing for statistical purposes. 

Call the following method to instruct the Adjust SDK to communicate the user's choice to change data sharing, to the Adjust backend:

```cpp
Adjust2dx::trackMeasurementConsent(true);
```

Upon receiving this information, Adjust changes sharing the specific user's data to partners. The Adjust SDK will continue to work as expected.

### <a id="sdk-signature"></a>SDK signature

An account manager must activate the Adjust SDK signature. Contact Adjust support (support@adjust.com) if you are interested in using this feature.

If the SDK signature has already been enabled on your account and you have access to App Secrets in your Adjust Dashboard, please use the method below to integrate the SDK signature into your app.

An App Secret is set by passing all secret parameters (`secretId`, `info1`, `info2`, `info3`, `info4`) to `setAppSecret` method of `AdjustConfig` instance:

```cpp
AdjustConfig2dx adjustConfig = AdjustConfig2dx(appToken, environment);
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

### <a id="di-gps-adid"></a>Google Play Services advertising identifier

The Google Play Services Advertising Identifier (Google advertising ID) is a unique identifier for a device. Users can opt out of sharing their Google advertising ID by toggling the "Opt out of Ads Personalization" setting on their device. When a user has enabled this setting, the Adjust SDK returns a string of zeros when trying to read the Google advertising ID.

> **Important**: If you are targeting Android 12 and above (API level 31), you need to add the [`com.google.android.gms.AD_ID` permission](#gps-adid-permission) to your app. If you do not add this permission, you will not be able to read the Google advertising ID even if the user has not opted out of sharing their ID.

The Adjust SDK allows you to read the Google Advertising Identifier of the Android device on which your app is running. To do this, set the callback method which receives the `std::string` parameter. Next, invoke the `getGoogleAdId` method of the `Adjust2dx` instance and pass the defined callback method as a parameter. You will then get the Google Advertising Identifier value in your callback method:

```cpp
static void adIdCallbackMethod(std::string adId) {
    CCLOG("\nAdvertising identifier = %s", adId.c_str());
    CCLOG("\n");
}

// ...

Adjust2dx::getGoogleAdId(adIdCallbackMethod);
```

### <a id="di-fire-adid"></a>Amazon advertising identifier

If you need to obtain the Amazon advertising ID, you can call the `getAmazonAdId` method of the `Adjust` instance and pass your callback as a parameter to which the Amazon advertising ID value will be sent once obtained:

```cpp
std::string amazonAdId = Adjust2dx::getAmazonAdId();
```

### <a id="di-adid"></a>Adjust device identifier

For each device with your app installed, the Adjust backend generates a unique **Adjust device identifier** (**adid**). In order to obtain this identifier, you can call the following method on the `Adjust2dx` instance:

```cpp
std::string adid = Adjust2dx::getAdid();
```

**Note**: Information about the **adid** is only available after the Adjust backed has tracked your app's installation. From that moment on, the Adjust SDK has information about the device **adid** and you can access it with this method. So, **it is not possible** to access the **adid** before the SDK has been initialized and the installation of your app has been tracked successfully.

### <a id="set-external-device-id"></a>Set external device ID

> **Note** If you want to use external device IDs, please contact your Adjust representative. They will talk you through the best approach for your use case.

An external device identifier is a custom value that you can assign to a device or user. They can help you to recognize users across sessions and platforms. They can also help you to deduplicate installs by user so that a user isn't counted as multiple new installs.

You can also use an external device ID as a custom identifier for a device. This can be useful if you use these identifiers elsewhere and want to keep continuity.

Check out our [external device identifiers article](https://help.adjust.com/en/article/external-device-identifiers) for more information.

> **Note** This setting requires Adjust SDK v4.22.0 or later.

To set an external device ID, assign the identifier to the `externalDeviceId` property of your config instance. Do this before you initialize the Adjust SDK.

```cpp
AdjustConfig2dx adjustConfig = AdjustConfig2dx(appToken, environment);
adjustConfig.setExternalDeviceId("{Your-External-Device-Id}");
Adjust2dx::adjustConfig(config);
```

> **Important**: You need to make sure this ID is **unique to the user or device** depending on your use-case. Using the same ID across different users or devices could lead to duplicated data. Talk to your Adjust representative for more information.

If you want to use the external device ID in your business analytics, you can pass it as a session callback parameter. See the section on [session callback parameters](#session-callback-parameters) for more information.

You can import existing external device IDs into Adjust. This ensures that the backend matches future data to your existing device records. If you want to do this, please contact your Adjust representative.

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

- Create a new tracker in your [dashboard].
- Open your app delegate and set the default tracker of your `AdjustConfig2dx` instance:

    ```cpp
    AdjustConfig2dx adjustConfig = AdjustConfig2dx(appToken, environment);
    adjustConfig.setDefaultTracker("{TrackerToken}");
    Adjust2dx::adjustConfig(config);
    ```

  Replace `{TrackerToken}` with the tracker token you created in step one. Please note that the dashboard displays a tracker URL (including `http://app.adjust.com/`). In your source code, you should specify only the six-character token and not the entire URL.

- Build and run your app. You should see a line like the following in the app's log output:

    ```
    Default tracker: 'abc123'
    ```

### <a id="deeplinking"></a>Deep linking

If you are using the Adjust tracker URL with an option to deep link into your app from the URL, there is the possibility to get information about the deep link URL and its content. There are two scenarios when it comes to deep linking: standard and deferred. 

Standard deep linking is when a user already has your app installed. iOS and Android offer native support for retrieving information about the deep link content in this scenario.

Deferred deep linking is when a user does not have your app installed. iOS and Android do not offer native support for deferred deep linking. Instead, the Adjust SDK offers a way to retrieve information about the deep link content.

You need to set up deep link handling in your app **at a native level** - in your generated Xcode and Android Studio projects.

### <a id="deeplinking-standard"></a>Standard deep linking

Unfortunately, in this scenario the information about the deep link can not be delivered to you in your Cocos2d-x C++ code. Once you have set up your app to handle deep linking, you will get information about the deep link at a native level. For more information, refer to our chapters below on how to enable deep linking for iOS and Android apps.

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

### <a id="deeplinking-android"></a>Deep link handling for Android apps

**This should be done in a native Android project.**

To set up your Android app to handle deep linking at a native level, please follow our [guide][android-deeplinking] in the official Android SDK README.

### <a id="data-residency"></a>Data residency

In order to enable data residency feature, make sure to call `setUrlStrategy` method of the `AdjustConfig2dx` instance with one of the following constants:

```js
adjustConfig.setUrlStrategy(AdjustDataResidencyEU); // for EU data residency region
adjustConfig.setUrlStrategy(AdjustDataResidencyTR); // for Turkey data residency region
adjustConfig.setUrlStrategy(AdjustDataResidencyUS); // for US data residency region
```

### <a id="coppa-compliance"></a>COPPA compliance

By default Adjust SDK doesn't mark app as COPPA compliant. In order to mark your app as COPPA compliant, make sure to call `setCoppaCompliantEnabled` method of `AdjustConfig2dx` instance with boolean parameter `true`:

```cpp
adjustConfig.setCoppaCompliantEnabled(true);
```

**Note:** By enabling this feature, third-party sharing will be automatically disabled for the users. If later during the app lifetime you decide not to mark app as COPPA compliant anymore, third-party sharing **will not be automatically re-enabled**. Instead, next to not marking your app as COPPA compliant anymore, you will need to explicitly re-enable third-party sharing in case you want to do that.

### <a id="play-store-kids-apps"></a>Play Store Kids Apps

By default Adjust SDK doesn't mark Android app as Play Store Kids App. In order to mark your app as the app which is targetting kids in Play Store, make sure to call `setPlayStoreKidsAppEnabled` method of `AdjustConfig2dx` instance with boolean parameter `true`:

```cpp
adjustConfig.setPlayStoreKidsAppEnabled(true);
```

[adjust]:       http://adjust.com
[dashboard]:    http://adjust.com
[adjust.com]:   http://adjust.com

[releases]:             https://github.com/adjust/cocos2dx_sdk/releases
[multidex]:             https://developer.android.com/tools/building/multidex.html
[referrer]:             https://github.com/adjust/android_sdk/blob/master/doc/english/referrer.md
[deeplinking]:          https://docs.adjust.com/en/tracker-generation/#deeplinking
[google-ad-id]:         https://developer.android.com/google/play-services/id.html
[event-tracking]:       https://docs.adjust.com/en/event-tracking
[callbacks-guide]:      https://docs.adjust.com/en/callbacks
[ios-deeplinking]:      https://github.com/adjust/ios_sdk/#deeplinking
[special-partners]:     https://docs.adjust.com/en/special-partners
[attribution-data]:     https://github.com/adjust/sdks/blob/master/doc/attribution-data.md
[currency-conversion]:  https://docs.adjust.com/en/event-tracking/#tracking-purchases-in-different-currencies
[android-deeplinking]:  https://github.com/adjust/android_sdk#deeplinking
[android-application]:  http://developer.android.com/reference/android/app/Application.html
[google-launch-modes]:  http://developer.android.com/guide/topics/manifest/activity-element.html#lmode
[google-play-services]: http://developer.android.com/google/play-services/setup.html
[android-sdk-download]: https://developer.android.com/sdk/index.html#Other
[install-referrer-aar]: https://maven.google.com/com/android/installreferrer/installreferrer/1.0/installreferrer-1.0.aar
[broadcast-receiver-custom]:  https://github.com/adjust/android_sdk/blob/master/doc/english/referrer.md

## <a id="license"></a>License

The Adjust SDK is licensed under the MIT License.

Copyright (c) 2015-Present Adjust GmbH, http://www.adjust.com

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
