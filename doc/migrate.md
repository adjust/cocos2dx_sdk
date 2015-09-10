## Migrate your adjust SDK for Cocos2d-x to 4.1.0 from 4.0.x

### SDK initialization

We have changed API in comparison with 4.0.x versions and also some of the class names.
We have changed how you configure and start the adjust SDK.

Here is an example of how the setup might look before and after the migration:

#### iOS

##### Before:

```cpp
#include "Adjust2dx.h"
// ...
std::string yourAppToken = "{YourAppToken}";
std::string environment = ADJEnvironmentSandbox2dx;

ADJConfig2dx adjustConfig = ADJConfig2dx(yourAppToken, environment);
Adjust2dx::appDidLaunch(adjustConfig);
```

##### After:

```cpp
#include "Adjust/Adjust2dx.h"
// ...
std::string appToken = "{YourAppToken}";
std::string environment = AdjustEnvironmentSandbox2dx;

AdjustConfig2dx adjustConfig = AdjustConfig2dx(appToken, environment);

Adjust2dx::start(adjustConfig);
```

#### Android

There is no need anymore for you to initialise and start our SDK from Java code. You can do that now
entirely from C++ code.

##### Before:

```java
import com.adjust.sdk.Adjust;
import com.adjust.sdk.AdjustConfig;

public class YourApplicationClass extends Application {
    @Override
    public void onCreate() {
        super.onCreate();

        String appToken = "{YourAppToken}";
        String environment = AdjustConfig.ENVIRONMENT_SANDBOX;
        AdjustConfig config = new AdjustConfig(this, appToken, environment);
        Adjust.onCreate(config);
    }
}
```

##### After:

```cpp
#include "Adjust/Adjust2dx.h"
// ...
std::string appToken = "{YourAppToken}";
std::string environment = AdjustEnvironmentSandbox2dx;

AdjustConfig2dx adjustConfig = AdjustConfig2dx(appToken, environment);

Adjust2dx::start(adjustConfig);
```

### Event tracking

Again, an example of how it might look like before and after:

#### iOS

##### Before:

```cpp
ADJEvent2dx adjustEvent = ADJEvent2dx("abc123");
adjustEvent.addCallbackParameter("key", "value");
adjustEvent.addCallbackParameter("foo", "bar");
Adjust2dx::trackEvent(adjustEvent);
```

##### After:

```cpp
AdjustEvent2dx adjustEvent = AdjustEvent2dx("abc123");
adjustEvent.addCallbackParameter("key", "value");
adjustEvent.addCallbackParameter("foo", "bar");
Adjust2dx::trackEvent(adjustEvent);
```

### Session tracking

#### Android

Before, you needed to update each one of your activity with calls to `Adjust.onResume()` and `Adjust.onPause()`.
Not anymore. Everything you need to do now is to update `applicationDidEnterBackground` and 
`applicationWillEnterForeground` methods in your app delegate.

##### Before:

```java
import com.adjust.sdk.Adjust;
// ...
public class YourActivity extends Cocos2dxActivity {
    protected void onResume() {
        super.onResume();
        Adjust.onResume();
    }
    protected void onPause() {
        super.onPause();
        Adjust.onPause();
    }
    // ...
}
```

##### After:

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

### Implement the attribution callback

#### Android

Since SDK initialisation was done in Java code, attribution callback was needed to be implemented in there
as well. Now, you can do everything in C++ code.

##### Before:

```java
AdjustConfig config = new AdjustConfig(this, appToken, environment);

config.setOnAttributionChangedListener(new OnAttributionChangedListener() {
    @Override
    public void onAttributionChanged(AdjustAttribution attribution) {
    }
});

Adjust.onCreate(config);
```

##### After:

```cpp
void attributionCallbackMethod(AdjustAttribution2dx attribution) {
}

// ...

AdjustConfig2dx adjustConfig = AdjustConfig2dx(appToken, environment);
adjustConfig.setAttributionCallback(attributionCallbackMethod);
Adjust2dx::start(adjustConfig);
```

### Set up deep link reattributions

#### iOS

Instead of opening URL directly from Objective-C, we now offer C++ interface for you to do this.
Both should be still functional, though.

##### Before:

```objc
- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url 
  sourceApplication:(NSString *)sourceApplication annotation:(id)annotation {
    [Adjust appWillOpenUrl:url];

    return YES;
}
```

##### After:

```objc
- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url 
  sourceApplication:(NSString *)sourceApplication annotation:(id)annotation {
    NSString *urlNSString = [url absoluteString];
    std::string urlString = std::string([urlNSString UTF8String]);

    Adjust2dx::appWillOpenUrl(urlString);

    return YES;
}
```
