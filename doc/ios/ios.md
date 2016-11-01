## Summary

This is the Cocos2d-x SDK of adjust™. You can read more about adjust™ at [adjust.com].

## Table of contents

* [Basic integration](#basic-integration)
   * [Get the SDK](#sdk-get)
   * [Add the SDK to your project](#sdk-add)
   * [Integrate the SDK into your app](#sdk-integrate)
   * [Adjust logging](#adjust-logging)
   * [Android manifest](#android-manifest)
   * [Google Play Services](#google-play-services)
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
        * [Deep linking setup for Android](#deeplinking-android)
        * [Deep linking setup for iOS](#deeplinking-ios)
        * [Reattribution via deep links](#deeplinking-reattribution)
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

Before adding `AdjustSdk.framework` to your project, please make sure that you first copy it to the `proj.ios_mac` folder to 
your project.

Select your project in the Project Navigator. In the left hand side of the main view, select your target. In the tab `Build 
Phases` expand the group `Link Binary With Libraries`. On the bottom of that section click on the `+` button. Select the 
`AdjustSdk.framework` and click the `Add` button. Repeat the same steps to add the `AdSupport.framework` and `iAd.framework`.

![][add_the_frameworks]

### <a id="sdk-linker-flags">Add additional linker flags

In order to support categories from `AdjustSdk.framework`, you should add an additional linker flag. Go to the `Build 
Settings` part of Project Settings and look for `Other Linker Flags` option. Add `-ObjC` flag to it.

![][add_other_linker_flags]

### <a id="sdk-integrate">Integrate the SDK into your app

In the Project Navigator, open the source file of your application delegate. Add the import statement at the top of the file, 
then add the following call to Adjust in the `applicationDidFinishLaunching` of your app delegate:

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

## <a id="sdk-build">Build your app

Build and run your app. If the build succeeds, you should carefully read the SDK logs in the console. After the app launched 
for the first time, you should see the info log `Install tracked`.

![][run]

## <a id="additional-features">Additional features

Once you integrate the adjust SDK into your project, you can take advantage of the following features.

### <a id="event-tracking">Event tracking

With adjust, you can track every event that you want. Suppose you want to track every tap on a button. Simply create a new 
event token in your [dashboard]. Let's say that event token is `abc123`. You can add the following line in your button’s click
handler method to track the click:

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

You can also add an optional transaction ID to avoid tracking duplicate revenues. The last ten transaction IDs are remembered, 
and revenue events with duplicate transaction IDs are skipped. This is especially useful for In-App Purchase tracking. You can 
see an example below.

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

#### Add callback parameters

You can register a callback URL for your events in your [dashboard]. We will send a GET request to that URL whenever the event 
is tracked. You can add callback parameters to that event by calling `addCallbackParameter` on the event before tracking it. 
We will then append these parameters to your callback URL.

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
don't store any of your custom parameters, but only append them to your callbacks. If you haven't registered a callback for an 
event, these parameters won't even be read.

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

The session callback parameters will be merged with the callback parameters added to an event. The callback parameters
added to an event have precedence over the session callback parameters. Meaning that, when adding a callback parameter to
an event with the same key to one added from the session, the value that prevails is the callback parameter added to the
event.

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










### 7. Set up deep link reattributions

You can set up the adjust SDK to handle deep links used to open your
app via a custom URL scheme. We will only read certain adjust specific
parameters. This is essential if you are planning to run retargeting or
re-engagement campaigns with deep links.

In the Project Navigator open the source file of your iOS App Controller. Find
or add the method `openURL` and add __one__ of the following calls to adjust:

```objc
- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url 
  sourceApplication:(NSString *)sourceApplication annotation:(id)annotation {
    // Like it was in previous versions:
    [Adjust appWillOpenUrl:url];
    
    // OR use new C++ interface:
    Adjust2dx::appWillOpenUrl(url);

    return YES;
}
```

You can read more about [deeplinking in our docs][deeplinking].

### 8. Enable event buffering

If your app makes heavy use of event tracking, you might want to delay some
HTTP requests in order to send them in one batch every minute. You can enable
event buffering with your `AdjustConfig2dx` instance:

```cpp
adjustConfig.setEventBufferingEnabled(true);
```

### 9. Implement the attribution callback

You can register a delegate callback to be notified of tracker attribution
changes. Due to the different sources considered for attribution, this
information cannot be provided synchronously. Follow these steps to implement
the optional delegate protocol in your app delegate:

Please make sure to consider our [applicable attribution data
policies.][attribution-data]

1. Open `AppDelegate.cpp` and add the following delegate callback function to
   your app delegate implementation.

    ```cpp
    void attributionCallbackMethod(AdjustAttribution2dx attribution) {
    }
    ```

2. Set the delegate with your `AdjustConfig2dx` instance:

    ```cpp
    adjustConfig.setAttributionCallback(attributionCallbackMethod);
    ```
    
As the delegate callback is configured using the `AdjustConfig2dx` instance, you
should call `setAttributionCallback` before calling `Adjust2dx::start(adjustConfig)`.

The delegate function will be called when the SDK receives final attribution data.
Within the delegate function you have access to the `attribution` parameter.
Here is a quick summary of its properties:

- `std::string trackerToken` the tracker token of the current install.
- `std::string trackerName` the tracker name of the current install.
- `std::string network` the network grouping level of the current install.
- `std::string campaign` the campaign grouping level of the current install.
- `std::string adgroup` the ad group grouping level of the current install.
- `std::string creative` the creative grouping level of the current install.
- `std::string clickLabel` the click label of the current install.

### 10. Disable tracking

You can disable the adjust SDK from tracking any activities of the current
device by calling `setEnabled` with parameter `false`. This setting is remembered
between sessions, but it can only be activated after the first session.

```objc
Adjust2dx::setEnabled(false);
```

You can check if the adjust SDK is currently enabled by calling the function
`isEnabled`. It is always possible to activate the adjust SDK by invoking
`setEnabled` with the enabled parameter as `true`.

### 11. Offline mode

You can put the adjust SDK in offline mode to suspend transmission to our servers, 
while retaining tracked data to be sent later. While in offline mode, all information is saved
in a file, so be careful not to trigger too many events while in offline mode.

You can activate offline mode by calling `setOfflineMode` with the parameter `true`.

```objc
Adjust2dx::setOfflineMode(true);
```

Conversely, you can deactivate offline mode by calling `setOfflineMode` with `false`.
When the adjust SDK is put back in online mode, all saved information is send to our servers 
with the correct time information.

Unlike disabling tracking, this setting is *not remembered*
bettween sessions. This means that the SDK is in online mode whenever it is started,
even if the app was terminated in offline mode.

[adjust.com]: http://adjust.com
[dashboard]: http://adjust.com
[releases]: https://github.com/adjust/cocos2dx_sdk/releases
[add_ios_files]: https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/ios/add_ios_files.png
[add_the_frameworks]: https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/ios/add_the_frameworks.png
[add_other_linker_flags]: https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/ios/add_other_linker_flags.png
[add_adjust2dx]: https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/ios/add_adjust2dx.png
[run]: https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/ios/run.png
[attribution-data]: https://github.com/adjust/sdks/blob/master/doc/attribution-data.md
[callbacks-guide]: https://docs.adjust.com/en/callbacks
[event-tracking]: https://docs.adjust.com/en/event-tracking
[special-partners]: https://docs.adjust.com/en/special-partners
[currency-conversion]: https://docs.adjust.com/en/event-tracking/#tracking-purchases-in-different-currencies
[deeplinking]: https://docs.adjust.com/en/tracker-generation/#deeplinking

## License

The adjust SDK is licensed under the MIT License.

Copyright (c) 2015-2016 adjust GmbH,
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

