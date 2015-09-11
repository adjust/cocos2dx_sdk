## Summary

This is the Cocos2d-x SDK of adjust™. You can read more about adjust™ at
[adjust.com].

## Basic integration into Cocos2d-x iOS project

We will describe the steps to integrate the adjust SDK into your Cocos2d-x iOS project.

### 1. Get the SDK

Download the latest version from our [releases page][releases]. Extract the
archive into a directory of your choice.

### 2. Add adjust source files to your solution

Take the files from the `Adjust` folder and add them to your iOS project.

![][add_ios_files]

### 3. Add the Adjust, AdSupport and iAd frameworks to your solution

Select your project in the Project Navigator. In the left hand side of the main view, select your target. 
In the tab `Build Phases` expand the group `Link Binary With Libraries`. On the bottom of that section click 
on the `+` button. Select the `Adjust.framework` and click the `Add` button. Repeat the same steps to add 
the `AdSupport.framework` and `iAd.framework`.

![][add_the_frameworks]

### 4. Add additional linker flags

In order to support categories from `Adjust.framework`, you should add an additional linker flag.
Go to the `Build Settings` part of Project Settings and look for `Other Linker Flags` option.
Add `-ObjC` flag to it.

![][add_other_linker_flags]

### 5. Integrate Adjust into your app

In the Project Navigator, open the source file of your application delegate. 
Add the import statement at the top of the file, then add the following call to 
Adjust in the `applicationDidFinishLaunching` of your app delegate:

```cpp
#include "Adjust/Adjust2dx.h"
// ...
std::string appToken = "{YourAppToken}";
std::string environment = AdjustEnvironmentSandbox2dx;

AdjustConfig2dx adjustConfig = AdjustConfig2dx(appToken, environment);

Adjust2dx::start(adjustConfig);
```

![][add_adjust2dx]

Replace `{YourAppToken}` with your app token. You can find this in your
[dashboard].

Depending on whether you build your app for testing or for production, you must
set `environment` with one of these values:

```cpp
std::string environment = AdjustEnvironmentSandbox2dx;
std::string environment = AdjustEnvironmentProduction2dx;
```

**Important:** This value should be set to `AdjustEnvironmentSandbox2dx` if and only
if you or someone else is testing your app. Make sure to set the environment to
`AdjustEnvironmentProduction2dx` just before you publish the app. Set it back to
`AdjustEnvironmentSandbox2dx` when you start developing and testing it again.

We use this environment to distinguish between real traffic and test traffic
from test devices. It is very important that you keep this value meaningful at
all times! This is especially important if you are tracking revenue.

#### Adjust Logging

You can increase or decrease the amount of logs you see in tests by calling
`setLogLevel` on your `AdjustConfig2dx` instance with one of the following
parameters:

```cpp
adjustConfig.setLogLevel(AdjustLogLevel2dxVerbose); // enable all logging
adjustConfig.setLogLevel(AdjustLogLevel2dxDebug);   // enable more logging
adjustConfig.setLogLevel(AdjustLogLevel2dxInfo);    // the default
adjustConfig.setLogLevel(AdjustLogLevel2dxWarn);    // disable info logging
adjustConfig.setLogLevel(AdjustLogLevel2dxError);   // disable warnings as well
adjustConfig.setLogLevel(AdjustLogLevel2dxAssert);  // disable errors as well
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
AdjustEvent2dx adjustEvent = AdjustEvent2dx("abc123");
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
AdjustEvent2dx adjustEvent = AdjustEvent2dx("abc123");
adjustEvent.setRevenue(0.01, "EUR");
Adjust2dx::trackEvent(adjustEvent);
```

This can be combined with callback parameters of course.

When you set a currency token, adjust will automatically convert the incoming revenues into a reporting 
revenue of your choice. Read more about [currency conversion here.][currency-conversion]

You can read more about revenue and event tracking in the [event tracking guide.][event-tracking]

##### <a id="deduplication"></a> Revenue deduplication

You can also pass in an optional transaction ID to avoid tracking duplicate revenues. The last ten transaction 
IDs are remembered and revenue events with duplicate transaction IDs are skipped. This is especially useful for 
in-app purchase tracking. See an example below.

If you want to track in-app purchases, please make sure to call `trackEvent` only if the transaction is finished
and item is purchased. That way you can avoid tracking revenue that is not actually being generated.

```cpp
AdjustEvent2dx adjustEvent = AdjustEvent2dx("abc123");
adjustEvent.setRevenue(0.01, "EUR");
adjustEvent.setTransactionId("transactionID");
Adjust2dx::trackEvent(adjustEvent);
```

##### Receipt verification

If you track in-app purchases, you can also attach the receipt to the tracked event. In that case our servers 
will verify that receipt with Apple and discard the event if the verification failed. To make this work, you 
also need to send us the transaction ID of the purchase. The transaction ID will also be used for SDK side 
deduplication as explained [above](#deduplication):

```cpp
AdjustEvent2dx adjustEvent = AdjustEvent2dx("abc123");
adjustEvent.setRevenue(0.01, "EUR");
adjustEvent.setReceipt("receipt", "transactionID");
Adjust2dx::trackEvent(adjustEvent);
```

#### Add callback parameters

You can register a callback URL for your events in your [dashboard]. We will
send a GET request to that URL whenever the event gets tracked. You can add
callback parameters to that event by calling `addCallbackParameter` on the
event before tracking it. We will then append these parameters to your callback
URL.

For example, suppose you have registered the URL
`http://www.adjust.com/callback` then track an event like this:

```cpp
AdjustEvent2dx adjustEvent = AdjustEvent2dx("abc123");
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
be added by calling the `addPartnerParameter` method on your `AdjustEvent2dx`
instance.

```cpp
AdjustEvent2dx adjustEvent = AdjustEvent2dx("abc123");
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
information can not be provided synchronously. Follow these steps to implement
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
[add_ios_files]: https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/ios/4.1.0/add_ios_files.png
[add_the_frameworks]: https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/ios/4.1.0/add_the_frameworks.png
[add_other_linker_flags]: https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/ios/4.1.0/add_other_linker_flags.png
[add_adjust2dx]: https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/ios/4.1.0/add_adjust2dx.png
[run]: https://raw.github.com/adjust/sdks/master/Resources/cocos2dx/ios/4.1.0/run.png
[attribution-data]: https://github.com/adjust/sdks/blob/master/doc/attribution-data.md
[callbacks-guide]: https://docs.adjust.com/en/callbacks
[event-tracking]: https://docs.adjust.com/en/event-tracking
[special-partners]: https://docs.adjust.com/en/special-partners
[currency-conversion]: https://docs.adjust.com/en/event-tracking/#tracking-purchases-in-different-currencies
[deeplinking]: https://docs.adjust.com/en/tracker-generation/#deeplinking

## License

The adjust SDK is licensed under the MIT License.

Copyright (c) 2012-2015 adjust GmbH,
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

