### Version 4.11.1 (7th April 2017)
#### Fixed
- **[AND]** Fixed issue of creating and destroying lots of threads on certain Android API levels (https://github.com/adjust/android_sdk/issues/265).

#### Changed
- **[AND]** Removed connection validity checks.
- **[AND]** Refactored native networking code.
- **[iOS]** Updated native iOS SDK to version **4.11.3**.
- **[AND]** Updated native Android SDK to version **4.11.3**.
- **[REPO]** Introduced `[iOS]`, `[AND]`, `[WIN]` and `[REPO]` tags to `CHANGELOG` to highlight the platform the change is referring to.

#### Native SDKs
- **[iOS]** [iOS SDK 4.11.3][ios_sdk_v4.11.3]
- **[AND]** [Android SDK 4.11.3][android_sdk_v4.11.3]
- **[WIN]** [Windows@4.0.3][windows_sdk_v4.0.3]

---

### Version 4.11.0 (6th February 2017)
**Note: All changes in this release are for iOS and Android platform only.**
#### Added
- **[iOS][AND]** Added `adid` property to the attribution callback response.
- **[iOS][AND]** Added `getAdid()` method of the `Adjust2dx` instance to be able to get adid value at any time after obtaining it, not only when session/event callbacks have been triggered.
- **[iOS][AND]** Added `getAttribution()` method of the `Adjust2dx` instance to be able to get current attribution value at any time after obtaining it, not only when an attribution callback has been triggered.
- **[iOS]** Added method swizzling for iOS platform so that only implemented callbacks in Cocos2d-x are getting implemented and called in iOS.
- **[AND]** Added sending of **Amazon Fire Advertising Identifier** for Android platform.
- **[AND]** Added possibility to set default tracker for the app by adding `adjust_config.properties` file to the `assets` folder of your Android app. Mostly meant to be used by the `Adjust Store & Pre-install Tracker Tool` (https://github.com/adjust/android_sdk/blob/master/doc/english/pre_install_tracker_tool.md).

#### Fixed
- **[iOS][AND]** Now reading push token value from activity state file when sending package.
- **[iOS]** Fixed memory leak by closing network session for iOS platform.
- **[iOS]** Fixed `TARGET_OS_TV` pre-processor check for iOS platform.

#### Changed
- **[iOS][AND]** Firing attribution request as soon as install has been tracked, regardless of presence of attribution callback implementation in user's app.
- **[iOS]** Saving iAd/AdSearch details to prevent sending duplicated `sdk_click` packages for iOS platform.
- **[iOS]** Updated native iOS SDK to version **4.11.0**.
- **[AND]** Updated native Android SDK to version **4.11.0**.
- **[REPO]** Updated docs.
- **[REPO]** Changed Makefiles with bash scripts.

#### Native SDKs
- **[iOS]** [iOS SDK 4.11.0][ios_sdk_v4.11.0]
- **[AND]** [Android SDK 4.11.0][android_sdk_v4.11.0]
- **[WIN]** [Windows@4.0.3][windows_sdk_v4.0.3]

---

### Version 4.10.0 (7th November 2016)
**Note: All changes in this release are for iOS and Android platform only.**
#### Added
- **[iOS]** Added support for iOS 10.
- **[AND]** Added revenue deduplication for Android platform.
- **[iOS][AND]** Added an option for enabling/disabling tracking while app is in background.
- **[iOS][AND]** Added a callback to be triggered if event is successfully tracked.
- **[iOS][AND]** Added a callback callback to be triggered if event tracking failed.
- **[iOS][AND]** Added a callback to be triggered if session is successfully tracked.
- **[iOS][AND]** Added a callback to be triggered if session tracking failed.
- **[iOS][AND]** Added possibility to set session callback and partner parameters with `addSessionCallbackParameter` and `addSessionPartnerParameter` methods.
- **[iOS][AND]** Added possibility to remove session callback and partner parameters by key with `removeSessionCallbackParameter` and `removeSessionPartnerParameter` methods.
- **[iOS][AND]** Added possibility to remove all session callback and partner parameters with `resetSessionCallbackParameters` and `resetSessionPartnerParameters` methods.
- **[iOS][AND]** Added new Suppress log level.
- **[iOS][AND]** Added possibility to delay initialisation of the SDK while maybe waiting to obtain some session callback or partner parameters with delayed start feature on adjust config instance.
- **[iOS][AND]** Added callback method to get deferred deep link content into the app.
- **[iOS][AND]** Added possibility to decide whether the SDK should launch the deferred deep link or not.
- **[iOS][AND]** Added possibility to set user agent manually on adjust config instance.

#### Fixed
- **[AND]** Fixed `setEventBufferingEnabled` JNI signature.

#### Changed
- **[iOS][AND]** Deferred deep link info will now arrive as part of the attribution response and not as part of the answer to first session.
- **[iOS]** Updated native iOS SDK to version 4.10.2.
- **[AND]** Updated native Android SDK to version 4.10.2.
- **[REPO]** Updated docs.

#### Native SDKs
- [iOS@v4.10.2][ios_sdk_v4.10.2]
- [Android@v4.10.2][android_sdk_v4.10.2]
- [Windows@4.0.3][windows_sdk_v4.0.3]

---

### Version 4.2.0 (12th February 2016)
#### Added
- **[WIN]** Added support for Windows platform.
- **[iOS]** Added `getIdfa` method for getting `IDFA` on iOS device.
- **[AND]** Added `getGoogleAdId` method for getting `Google Play Services Ad Id` on Android device.
- **[WIN]** Added `getWindowsAdId` method for getting `Windows Advertisement Id` on Windows device.
- **[REPO]** Added `CHANGELOG.md`.
- **[REPO]** Added instructions for `Android Studio` in `Android README`.

#### Changed
- **[iOS]** Renamed `Adjust.framework` to `AdjustSdk.framework`.
- **[iOS]** Removed `MAC MD5` tracking feature for `iOS platform` completely.
- **[iOS]** Updated native iOS SDK to version **4.5.4**.
- **[AND]** Updated native Android SDK to version **4.2.3**.
- **[REPO]** Updated docs.

#### Native SDKs
- **[iOS]** [iOS@v4.5.4][ios_sdk_v4.5.4]
- **[AND]** [Android@v4.2.3][android_sdk_v4.2.3]
- **[WIN]** [Windows@4.0.3][windows_sdk_v4.0.3]

---

### Version 4.1.0 (17th September 2015)
#### Added
- **[AND]** Added additional methods to C++ interface.

#### Changed
- **[AND]** Moved calls from Java code to C++.
- **[iOS]** Updated native iOS SDK to version **4.3.0**.
- **[AND]** Updated native Android SDK to version **4.1.2**.

#### Native SDKs
- **[iOS]** [iOS@v4.3.0][ios_sdk_v4.3.0]
- **[AND]** [Android@v4.1.2][android_sdk_v4.1.2]

---

### Version 4.0.1 (17th July 2015)
#### Changed
- **[iOS]** Updated native iOS SDK to version **4.2.7**.
- **[AND]** Updated native Android SDK to version **4.1.0**.
- **[REPO]** Updated docs.

#### Native SDKs
- **[iOS]** [iOS@v4.2.7][ios_sdk_v4.2.7]
- **[AND]** [Android@v4.1.0][android_sdk_v4.1.0]

---

### Version 4.0.0 (25th June 2015)
#### Added
- **[iOS][AND]** Initial release of the adjust SDK for Cocos2d-x. Supported platforms: `iOS` and `Android`.

#### Native SDKs
- **[iOS]** [iOS@v4.2.6][ios_sdk_v4.2.6]
- **[AND]** [Android@v4.0.8][android_sdk_v4.0.8]

[ios_sdk_v4.2.6]: https://github.com/adjust/ios_sdk/tree/v4.2.6
[ios_sdk_v4.2.7]: https://github.com/adjust/ios_sdk/tree/v4.2.7
[ios_sdk_v4.3.0]: https://github.com/adjust/ios_sdk/tree/v4.3.0
[ios_sdk_v4.5.4]: https://github.com/adjust/ios_sdk/tree/v4.5.4
[ios_sdk_v4.10.2]: https://github.com/adjust/ios_sdk/tree/v4.10.2
[ios_sdk_v4.11.0]: https://github.com/adjust/ios_sdk/tree/v4.11.0
[ios_sdk_v4.11.3]: https://github.com/adjust/ios_sdk/tree/v4.11.3

[android_sdk_v4.0.8]: https://github.com/adjust/android_sdk/tree/v4.0.8
[android_sdk_v4.1.0]: https://github.com/adjust/android_sdk/tree/v4.1.0
[android_sdk_v4.1.2]: https://github.com/adjust/android_sdk/tree/v4.1.2
[android_sdk_v4.2.3]: https://github.com/adjust/android_sdk/tree/v4.2.3
[android_sdk_v4.10.2]: https://github.com/adjust/android_sdk/tree/v4.10.2
[android_sdk_v4.11.0]: https://github.com/adjust/android_sdk/tree/v4.11.0
[android_sdk_v4.11.1]: https://github.com/adjust/android_sdk/tree/v4.11.1
[android_sdk_v4.11.3]: https://github.com/adjust/android_sdk/tree/v4.11.3

[windows_sdk_v4.0.3]: https://github.com/adjust/windows_sdk/tree/v4.0.3
