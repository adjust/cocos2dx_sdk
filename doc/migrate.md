## Migrate your adjust SDK for Cocos2d-x to 4.10.0 from 4.0.x

### SDK initialization

We have changed the API in comparison with 4.0.x versions, as well as some of the class names.
We also changed how you configure and start the adjust SDK.

Here is an example of how the setup might look before and after the migration:

#### iOS

##### Before:

```cpp
#include "Adjust2dx.h"
// ...
ADJConfig2dx adjustConfig = ADJConfig2dx(yourAppToken, environment);
```

##### After:

```cpp
#include "Adjust/Adjust2dx.h"
// ...
AdjustConfig2dx adjustConfig = AdjustConfig2dx(appToken, environment);
```

#### Android

There is no longer a need for you to initialize and start our SDK using Java code. You can now use C++ code.

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
// ...
```

##### After:

```cpp
AdjustEvent2dx adjustEvent = AdjustEvent2dx("abc123");
// ...
```

### Session tracking

#### Android

Previously, you needed to update each activity with calls to `Adjust.onResume()` and `Adjust.onPause()`.

Not anymore. All you need to do now is to update the `applicationDidEnterBackground` and
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

Since the SDK initialization was done in Java code, attribution callbacks had to be implemented in Java as well. Now, you can do everything in C++ code.

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

Instead of opening a URL directly from Objective-C, we now offer a C++ interface for you to do this.
Both are functional and you can choose one from those two methods.

##### Objective-C code

Scenario used so far:

```objc
- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url 
  sourceApplication:(NSString *)sourceApplication annotation:(id)annotation {
    [Adjust appWillOpenUrl:url];

    return YES;
}
```

##### C++ code

Newly offered scenario:

```objc
- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url 
  sourceApplication:(NSString *)sourceApplication annotation:(id)annotation {
    Adjust2dx::appWillOpenUrl(url);

    return YES;
}
```
