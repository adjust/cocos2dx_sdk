## Summary

This is the Cocos2d-x SDK of Adjust™. You can read more about Adjust™ at [adjust.com].

## Table of contents

* [Basic integration](#basic-integration)
   * [Get the SDK](#sdk-get)
   * [Add the SDK to your project](#sdk-add)
   * [Add Adjust Windows Runtime Component project to your solution](#sdk-winrt)
   * [Integrate the SDK into your app](#sdk-integrate)
   * [Adjust logging](#sdk-logging)
   * [Build your app](#sdk-build)
* [Additional features](#additional-features)
   * [Event tracking](#event-tracking)
      * [Revenue tracking](#revenue-tracking)
      * [Callback parameters](#callback-parameters)
      * [Partner parameters](#partner-parameters)
    * [Attribution callback](#attribution-callback)
    * [Disable tracking](#disable-tracking)
    * [Offline mode](#offline-mode)
    * [Event buffering](#event-buffering)
* [License](#license)

## <a id="basic-integration">Basic integration

How to integrate the Adjust SDK into your Cocos2d-x Windows or Windows Phone project.

### <a id="sdk-get">Get the SDK

Download the latest version from our [releases page][releases]. Extract the archive into a directory of your choice.

### <a id="sdk-add">Add the SDK to your project

Take the `Adjust` folder and copy it to your project's `Classes` folder. Add it, along with all the files inside, to your Visual Studio project as part of the `Classes` folder.

![][add-windows-files]

### <a id="sdk-winrt">Add the Adjust Windows Runtime Component project to your solution

The project which Cocos2d-x generates for you is unmanaged and written in pure C++. Our Windows SDK is managed and written in C#. In order to facilitate communication between your unmanaged app and our managed SDK, we created a Windows Runtime Component project that can be added to your app as a reference. It wraps our Windows SDK and can be used with unmanaged C++ code.

Depending on the platform you are building your app for, you should choose the appropriate Windows Runtime Component project to add to your solution. The Windows Runtime Component projects can be found in the `Windows` folder. You can choose one of the following projects:

* `AdjustUAP10WinRT` - Use this if you are developing your app for Windows 10
* `AdjustWP81WinRT` - Use this if you are developing your app for Windows Phone 8.1
* `AdjustWS81WinRT` - Use this if you are developing your app for Windows 8.1

![][add-winrt-project]

After you have added one of these projects to your solution, add the reference to it in your app's project.

![][add-winrt-project-reference]

With this, you have implemented the Adjust Cocos2d-x SDK for Windows into your Visual Studio project.

### <a id="sdk-integrate">Integrate the SDK into your app

In the Project Navigator, open the source file of your application delegate. Add the import statement at the top of the file. Next, add the following call to Adjust in the `applicationDidFinishLaunching` method of your app delegate:

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

Depending on whether you build your app for testing or for production, you must set `environment` with one of these values:

```cpp
std::string environment = AdjustEnvironmentSandbox2dx;
std::string environment = AdjustEnvironmentProduction2dx;
```

**Important:** This value should be set to `AdjustEnvironmentSandbox2dx` if and only if you or someone else is testing your app. Make sure to set the environment to `AdjustEnvironmentProduction2dx` before you publish your app. Set it back to `AdjustEnvironmentSandbox2dx` when you start developing and testing it again.

We use this environment to distinguish between real traffic and test traffic from test devices. It is imperative that you keep this value meaningful at all times, especially if you are tracking revenue.

### <a id="sdk-logging">Adjust logging

To see the log output from our library, which is created in `released mode`, you need to redirect the log output to your app while testing it in `debug mode`.

To do this, define a custom method to handle the log output and set this as the second parameter of the `setLogLevel` method of the config object. The custom method you create should be defined with no return value (void) and it should get one parameter of a `const char*` type.

```cpp
#include "Adjust/Adjust2dx.h"

// ...

static void printLog(const char* logLine) {
    std::string logLineAsString(logLine);
    CCLog(logLineAsString.c_str());
}

//...

std::string appToken = "{YourAppToken}";
std::string environment = AdjustEnvironmentSandbox2dx;

AdjustConfig2dx adjustConfig = AdjustConfig2dx(appToken, environment);
adjustConfig.setLogLevel(AdjustLogLevel2dxVerbose, printLog);

Adjust2dx::start(adjustConfig);
// ...
```

You can increase or decrease the amount of logs you see in tests by calling `setLogLevel` on your `AdjustConfig2dx` instance with one of the following parameters as the first method parameter:

```cpp
adjustConfig.setLogLevel(AdjustLogLevel2dxVerbose, printLog); // enable all logging
adjustConfig.setLogLevel(AdjustLogLevel2dxDebug, printLog);   // enable more logging
adjustConfig.setLogLevel(AdjustLogLevel2dxInfo, printLog);    // the default
adjustConfig.setLogLevel(AdjustLogLevel2dxWarn, printLog);    // disable info logging
adjustConfig.setLogLevel(AdjustLogLevel2dxError, printLog);   // disable warnings as well
adjustConfig.setLogLevel(AdjustLogLevel2dxAssert, printLog);  // disable errors as well
```

### <a id="sdk-build">Build your app

Build and run your app. If the build succeeds, you should carefully read the SDK logs in the console. After your app has launched, you should see the following info log: `Install tracked`.

![][run]

## <a id="additional-features">Additional features

Once you have integrated the Adjust SDK into your project, you can take advantage of the following features.

### <a id="event-tracking">Event tracking

Adjust lets you track any event that you want. Suppose you want to track every tap on a button. If you create a new event token in your [dashboard] - let's say that event token is `abc123` - you can add the following line in your button’s click handler method to track the click:

```cpp
AdjustEvent2dx adjustEvent = AdjustEvent2dx("abc123");
Adjust2dx::trackEvent(adjustEvent);
```

When this event is triggered, you should see `Event tracked` in the logs.

The event instance can be used to configure the event before tracking it.

### <a id="revenue-tracking">Revenue tracking

If your users can generate revenue by tapping on advertisements or making In-App Purchases, then you can track those revenues with events. Let's say a tap is worth €0.01. You could track the revenue event like this:

```cpp
AdjustEvent2dx adjustEvent = AdjustEvent2dx("abc123");

adjustEvent.setRevenue(0.01, "EUR");

Adjust2dx::trackEvent(adjustEvent);
```

When you set a currency token, Adjust will automatically convert the incoming revenues into a reporting revenue of your choice. Read more about [currency conversion here][currency-conversion].

You can read more about revenue and event tracking in the [event tracking guide][event-tracking].

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

It should be mentioned that we support a variety of placeholders, like `{idfa}`, that can be used as parameter values. In the resulting callback this placeholder would be replaced with the current device's ID for Advertisers. Adjust does not store any of your custom parameters, but only appends them to your callbacks. If you haven't registered a callback for an event, these parameters won't even be read.

You can read more about using URL callbacks, including a full list of available values, in our [callbacks guide][callbacks-guide].

### <a id="partner-parameters">Partner parameters

For any integrations that have been activated in your Adjust dashboard, you can add parameters to send to these network partners.

Partner parameters work similarly to the callback parameters mentioned above, but can be added by calling the `addPartnerParameter` method on your `AdjustEvent2dx` instance.

```cpp
AdjustEvent2dx adjustEvent = AdjustEvent2dx("abc123");

adjustEvent.addPartnerParameter("key", "value");
adjustEvent.addPartnerParameter("foo", "bar");

Adjust2dx::trackEvent(adjustEvent);
```

You can read more about special partners and how to integrate them in our [guide to special partners][special-partners].

### <a id="attribution-callback">Attribution callback

Adjust can also send you a callback upon any change in attribution. Due to the different sources considered for attribution, this information cannot be provided synchronously. Follow these steps if you wish to implement the callback in your application:

1. Create a void method which receives an `AdjustAttribution2dx` parameter.

2. After creating an `AdjustConfig2dx` instance, call its `setAttributionCallback` method with the previously created method as parameter.

The callback function will be called when the SDK receives the final attribution data. Within the callback function you have access to the `attribution` parameter. Here is a quick summary of its properties:

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

Please make sure to consider the [applicable attribution data policies][attribution-data].

### <a id="disable-tracking">Disable tracking

You can disable the Adjust SDK from tracking by invoking the `Adjust2dx::setEnabled` method with the enabled parameter set to `false`. This setting is **remembered between sessions**, but it can only be activated after the first session.

```cpp
Adjust2dx::setEnabled(false);
```

You can verify if the Adjust SDK is currently active by using the `Adjust2dx::isEnabled()` method. It is always possible to activate the Adjust SDK by invoking `Adjust2dx::setEnabled` with the parameter set to `true`.

### <a id="offline-mode">Offline mode

You can put the Adjust SDK in offline mode, suspending transmission to our servers while retaining tracked data to be sent later. When in offline mode, all information is saved in a file, so it is best not to trigger too many events while in offline mode.

You can activate offline mode by calling `Adjust2dx::setOfflineMode` with the parameter set to `true`.

```cpp
Adjust2dx::setOfflineMode(true);
```

Conversely, you can deactivate offline mode by calling `Adjust2dx::setOfflineMode` with the parameter set to `false`. When the Adjust SDK is put back in online mode, all saved information is send to our servers with the correct time information.

Unlike when disabling tracking, **this setting is not remembered** between sessions. This means that the SDK always starts in online mode, even if the app was terminated in offline mode.

### <a id="event-buffering">Event buffering

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

If nothing set here, event buffering is **disabled by default**.


[dashboard]:    http://adjust.com
[adjust.com]:   http://adjust.com

[releases]:             https://github.com/adjust/cocos2dx_sdk/releases
[event-tracking]:       https://docs.adjust.com/en/event-tracking
[callbacks-guide]:      https://docs.adjust.com/en/callbacks
[special-partners]:     https://docs.adjust.com/en/special-partners
[attribution-data]:     https://github.com/adjust/sdks/blob/master/doc/attribution-data.md
[currency-conversion]:  https://docs.adjust.com/en/event-tracking/#tracking-purchases-in-different-currencies

[run]:                  https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/windows/run.png
[add-adjust2dx]:        https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/windows/add_adjust2dx.png
[add-windows-files]:    https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/windows/add_windows_files.png
[add-winrt-project]:    https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/windows/add_winrt_project.png

[add-winrt-project-reference]: https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/windows/add_winrt_project_reference.png

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