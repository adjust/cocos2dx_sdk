## Summary

This is the Cocos2d-x SDK of adjust™. You can read more about adjust™ at
[adjust.com].

## Basic integration into Cocos2d-x iOS project

We will describe the steps to integrate the adjust SDK into your Cocos2d-x iOS project.

### 1. Get the SDK

Download the latest version from our [releases page][releases]. Extract the
archive into a directory of your choice.

### 2. Add adjust source files to your solution

Take the files from the `iOS/Adjust` folder and add them to your iOS project.

![][add_ios_files]

### 3. Add the Adjust, AdSupport and iAd frameworks to your solution

Select your project in the Project Navigator. In the left hand side of the main view, select your target. 
In the tab `Build Phases` expand the group `Link Binary With Libraries`. On the bottom of that section click 
on the `+` button. Select the `Adjust.framework` and click the `Add` button. Repeat the same steps to add 
the `AdSupport.framework` and `iAd.framework`.

![][add_the_frameworks]

### 4. Add additional linker flags

If you are not using `Objective-C Automatic Reference Counting`, you should add two additional linker flags.
Go to the `Build Settings` part of Project Settings and look for `Other Linker Flags` option.
Add `-fobjc-arc` and `-ObjC` flags to it.

![][add_other_linker_flags]

### 5. Integrate Adjust into your app

In the Project Navigator, open the source file of your application delegate. 
Add the import statement at the top of the file, then add the following call to 
Adjust in the applicationDidFinishLaunching of your app delegate:

```cpp
#include "Adjust2dx.h"
// ...
std::string yourAppToken = "{YourAppToken}";
std::string environment = ADJEnvironmentSandbox2dx;

ADJConfig2dx adjustConfig = ADJConfig2dx(yourAppToken, environment);
Adjust2dx::appDidLaunch(adjustConfig);
```

![][add_adjust2dx]

Replace `{YourAppToken}` with your app token. You can find this in your
[dashboard].

Depending on whether you build your app for testing or for production, you must
set `environment` with one of these values:

```cpp
std::string environment = ADJEnvironmentSandbox2dx;
std::string environment = ADJEnvironmentProduction2dx;
```

**Important:** This value should be set to `ADJEnvironmentSandbox2dx` if and only
if you or someone else is testing your app. Make sure to set the environment to
`ADJEnvironmentProduction2dx` just before you publish the app. Set it back to
`ADJEnvironmentSandbox2dx` when you start developing and testing it again.

We use this environment to distinguish between real traffic and test traffic
from test devices. It is very important that you keep this value meaningful at
all times! This is especially important if you are tracking revenue.

#### Adjust Logging

You can increase or decrease the amount of logs you see in tests by calling
`setLogLevel` on your `ADJConfig2dx` instance with one of the following
parameters:

```cpp
adjustConfig.setLogLevel(ADJLogLevel2dxVerbose); // enable all logging
adjustConfig.setLogLevel(ADJLogLevel2dxDebug);   // enable more logging
adjustConfig.setLogLevel(ADJLogLevel2dxInfo);    // the default
adjustConfig.setLogLevel(ADJLogLevel2dxWarn);    // disable info logging
adjustConfig.setLogLevel(ADJLogLevel2dxError);   // disable warnings as well
adjustConfig.setLogLevel(ADJLogLevel2dxAssert);  // disable errors as well
```

### 5. Build your app

Build and run your app. If the build succeeds, you should carefully read the
SDK logs in the console. After the app launched for the first time, you should
see the info log `Install tracked`.

![][run]

## Additional features

Once you integrate the adjust SDK into your project, you can take advantage of
the following features.

### 6. Set up event tracking

You can use adjust to track events. You would create a new event token in your [dashboard],
which has an associated event token - looking something like `abc123`. In your
game you would then add the following lines to track the event you are interested in:

```cpp
ADJEvent2dx adjustEvent = ADJEvent2dx("abc123");
Adjust2dx::trackEvent(adjustEvent);
```

When this event is triggered, you should see `Event tracked` in the logs.

The event instance can be used to configure the event further before tracking
it.

#### Track revenue

If your users can generate revenue by tapping on advertisements or making
in-app purchases you can track those revenues with events. Lets say a tap is
worth one Euro cent. You could then track the revenue event like this:

```cpp
ADJEvent2dx adjustEvent = ADJEvent2dx("abc123");
adjustEvent.setRevenue(0.01, "EUR");
Adjust2dx::trackEvent(adjustEvent);
```

This can be combined with callback parameters of course.

When you set a currency token, adjust will automatically convert the incoming revenues into a reporting 
revenue of your choice. Read more about [currency conversion here.][currency-conversion]

You can read more about revenue and event tracking in the [event tracking guide.][event-tracking]

#### Add callback parameters

You can register a callback URL for your events in your [dashboard]. We will
send a GET request to that URL whenever the event gets tracked. You can add
callback parameters to that event by calling `addCallbackParameter` on the
event before tracking it. We will then append these parameters to your callback
URL.

For example, suppose you have registered the URL
`http://www.adjust.com/callback` then track an event like this:

```cpp
ADJEvent2dx adjustEvent = ADJEvent2dx("abc123");
adjustEvent.addCallbackParameter("key", "value");
adjustEvent.addCallbackParameter("foo", "bar");
Adjust2dx::trackEvent(adjustEvent);
```

In that case we would track the event and send a request to:

    http://www.adjust.com/callback?key=value&foo=bar

It should be mentioned that we support a variety of placeholders like `{idfa}`
that can be used as parameter values. In the resulting callback this
placeholder would be replaced with the ID for Advertisers of the current
device. Also note that we don't store any of your custom parameters, but only
append them to your callbacks. If you haven't registered a callback for an
event, these parameters won't even be read.

You can read more about using URL callbacks, including a full list of available
values, in our [callbacks guide][callbacks-guide].

#### Partner parameters

You can also add parameters to be transmitted to network partners, for the
integrations that have been activated in your adjust dashboard.

This works similarly to the callback parameters mentioned above, but can
be added by calling the `addPartnerParameter` method on your `ADJEvent2dx`
instance.

```cpp
ADJEvent2dx adjustEvent = ADJEvent2dx("abc123");
adjustEvent.addPartnerParameter("foo", "bar");
Adjust2dx::trackEvent(adjustEvent);
```

You can read more about special partners and these integrations in our
[guide to special partners.][special-partners]

### 7. Set up deep link reattributions

You can set up the adjust SDK to handle deep links that are used to open your
app via a custom URL scheme. We will only read certain adjust specific
parameters. This is essential if you are planning to run retargeting or
re-engagement campaigns with deep links.

In the Project Navigator open the source file of your App Controller. Find
or add the method `openURL` and add the following call to adjust:

```objc
- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url 
  sourceApplication:(NSString *)sourceApplication annotation:(id)annotation {
    [Adjust appWillOpenUrl:url];

    return YES;
}
```

You can read more about [deeplinking in our docs][deeplinking].

### 8. Enable event buffering

If your app makes heavy use of event tracking, you might want to delay some
HTTP requests in order to send them in one batch every minute. You can enable
event buffering with your `ADJConfig2dx` instance:

```cpp
adjustConfig.setEventBufferingEnabled(true);
```

### 9. Implement the attribution callback

You can register a delegate callback to be notified of tracker attribution
changes. Due to the different sources considered for attribution, this
information can not be provided synchronously. Follow these steps to implement
the optional delegate protocol in your app delegate:

Please make sure to consider our [applicable attribution data
policies.][attribution-data]

1. Open `AppDelegate.cpp` and add the following delegate callback function to
   your app delegate implementation.

    ```cpp
    void attributionCallbackMethod(ADJAttribution2dx attribution) {
    }
    ```

2. Set the delegate with your `ADJConfig2dx` instance:

    ```cpp
    adjustConfig.setAttributionCallback(attributionCallbackMethod);
    ```
    
As the delegate callback is configured using the `ADJConfig2dx` instance, you
should call `setAttributionCallback` before calling `Adjust2dx::appDidLaunch(adjustConfig)`.

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
