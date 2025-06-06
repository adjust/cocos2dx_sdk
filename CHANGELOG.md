### Version 5.4.0 (6th June 2025)
#### Added
- Added support for configuring store information via the `AdjustStoreInfo2dx` object. You can now specify the store name and store app ID via `setStoreInfo` method on your `AdjustConfig2dx` instance. This enables the SDK to record the intended app store source during initialization. For more details about this feature, refer to the [official documentation](https://dev.adjust.com/en/sdk/cocos2dx/setup/store-type).
**Note**: This feature introduces a new class named `AdjustStoreInfo2dx` Make sure to add it to your `Android.mk` / `CMakeLists.txt` and Xcode project.
- Added ability to initialize the SDK for the first session in delayed mode. You can start the SDK in the delayed mode by calling the `enableFirstSessionDelay` method on your `AdjustConfig2dx` instance. To end the delay, make sure to call `endFirstSessionDelay` method of `Adjust2dx` instance. For more details about this feature, refer to the [official documentation](https://dev.adjust.com/en/sdk/cocos2dx/features/first-session-delay).
- Added ability to send organic search referrer together with deep link. You can send it via `setReferrer` method of the `AdjustDeeplink2dx` instance. For more details about this feature, refer to the [official documentation](https://dev.adjust.com/en/sdk/cocos2dx/features/deep-links#handling-deeplinks-with-referrer).
- Added ability to disable SDK's interaction with `AppTrackingTransparency.framework` API. You can disable it by calling the `disableAppTrackingTransparencyUsage` method on your `AdjustConfig2dx` instance. For more details about this feature, refer to the [official documentation](https://dev.adjust.com/en/sdk/cocos2dx/features/att#disable-att-framework).
- Added `jsonResponse` member to `AdjustAttribution2dx` class which represents the JSON string sent by the backend as part of the attribution response.

#### Native SDKs
- [iOS@v5.4.0][ios_sdk_v5.4.0]
- [Android@v5.4.0][android_sdk_v5.4.0]

---

### Version 5.0.2 (7th February 2025)
#### Added
- Added sending of the additional parameter to improve troubleshooting of `SKAdNetwork` related issues.

#### Fixed
- Fixed occasional occurrences in which ATT waiting interval timer was not being started.
- Pinned version 3.35.2 of the Adjust signature library, which addresses occasional crashes on iOS 18 (https://github.com/adjust/ios_sdk/issues/742).

#### Changed
- Switched to depending on a specific version of the signature library.

#### Native SDKs
- [iOS@v5.0.2][ios_sdk_v5.0.2]
- [Android@v5.0.2][android_sdk_v5.0.2]

---

### Version 5.0.1 (5th November 2024)
#### Fixed
- Added missing `unordered_map` imports to header files.

#### Native SDKs
- [iOS@v5.0.1][ios_sdk_v5.0.1]
- [Android@v5.0.1][android_sdk_v5.0.1]

---

### Version 5.0.0 (2nd October 2024)

We're excited to release our major new SDK version (v5). Among many internal improvements, our spoofing protection solution is now included out of the box, reinforcing our commitment to accurate, actionable, and fraud-free data.

To try out SDK v5 in your app, you can follow our new v4 to v5 [migration guide](https://dev.adjust.com/en/sdk/migration/cocos2dx/v4-to-v5).

If you are a current Adjust client and have questions about SDK v5, please email [sdk-v5@adjust.com](mailto:sdk-v5@adjust.com).

In case you were using beta version of the SDK v5, please switch to the official v5 release.

#### Native SDKs
- [iOS@v5.0.1][ios_sdk_v5.0.1]
- [Android@v5.0.1][android_sdk_v5.0.1]

---

### Version 4.37.0 (22nd January 2024)
#### Added
- Added support for SKAD 4.0.
- Added ability to verify purchase events.
- Added ability to read App Set ID on Android platform in case you opt in by adding the `com.google.android.gms:play-services-appset` dependency to your Android app.
- Added ability to delay SDK start on iOS platform in order to wait for an answer to the ATT dialog. You can set the number of seconds to wait (capped internally to 120) by calling the `setAttConsentWaitingInterval` method of the `AdjustConfig2dx` instance.
- Added support for SigV3 library. Update authorization header building logic to use `adj_signing_id`.
- Added ability to indicate if only final Android attribution is needed in attribution callback (by default attribution callback return intermediate attribution as well before final attribution if not enabled with this setter method) calling the `setFinalAttributionEnabled` method of the `AdjustConfig2dx` instance.
- Added ability to get IDFV value of the iOS device. You can achieve this by invoking `getIdfv()` method of the `Adjust2dx` instance.
- Added support for Meta install referrer.
- Added support for Google Play Games on PC.
- Added support for `TopOn` and `AD(X)` ad revenue tracking.
- Added `setReadDeviceInfoOnceEnabled` method to `AdjustConfig2dx` to indicate if device info should be read only once.
- Added ability to process shortened deep links and provide the unshortened link back as a response. You can achieve this by invoking `processDeeplink` method of the `Adjust2dx` instance.
- Added support for setting a new China URL strategy (with fallback to other endpoints) and China only URL strategy (without fallbacks). You can choose this setting by calling `setUrlStrategy` method of `AdjustConfig2dx` instance with `AdjustUrlStrategyCn` / `AdjustUrlStrategyCnOnly` parameter.

#### Native SDKs
- [iOS@v4.37.0][ios_sdk_v4.37.0]
- [Android@v4.38.0][android_sdk_v4.38.0]

---

### Version 4.32.0 (20th October 2022)
#### Added
- Added ability to mark your app as COPPA compliant. You can enable this setting by calling `setCoppaCompliantEnabled` method of `AdjustConfig2dx` instance with boolean parameter `true`.
- Added ability to mark your Android app as app for the kids in accordance to Google Play Families policies. You can enable this setting by calling `setPlayStoreKidsAppEnabled` method of `AdjustConfig2dx` instance with boolean parameter `true` (Android only).
- Added `checkForNewAttStatus` method to `Adjust2dx` API to allow iOS apps to instruct to SDK to check if `att_status` might have changed in the meantime (iOS only).
- Added updated `trackAdRevenueNew` method to `Adjust2dx` API to allow unified way of tracking ad revenue with currently supported partners (AppLovin MAX, AdMob, IronSource, AdMost, Unity, Helium Chartboost). Make sure to include newly added `AdjustAdRevenue2dx.h` and `AdjustAdRevenue2dx.cpp` files to your `Android.mk` or `CMakeLists.txt` files.
- Added partner sharing settings to the third party sharing feature.
- Added `getLastDeeplink` getter to `Adjust2dx` API to be able to get last tracked deep link by the SDK (iOS only).
- Added support for `LinkMe` feature (iOS only).
- Added support to get Facebook install referrer information in attribution callback (Android only).

#### Changed
- Switched to adding permission `com.google.android.gms.permission.AD_ID` in the Android app's manifest by default.

#### Native SDKs
- [iOS@v4.32.1][ios_sdk_v4.32.1]
- [Android@v4.33.0][android_sdk_v4.33.0]

---

### Version 4.29.0 (14th September 2021)
#### Added
- Added possibility to get cost data information in attribution callback.
- Added `setNeedsCost` method to `AdjustConfig2dx` to indicate if cost data is needed in attribution callback (by default cost data will not be part of attribution callback if not enabled with this setter method).
- Added `setPreinstallTrackingEnabled` method to `AdjustConfig2dx` to allow enabling of preinstall tracking (this feature is OFF by default).
- Added support for Apple Search Ads attribution with usage of `AdServices.framework`.
- Added `setAllowAdServicesInfoReading` method to `AdjustConfig2dx` to allow option for users to prevent SDK from performing any tasks related to Apple Search Ads attribution with usage of `AdServices.framework`.
- Added `setAllowiAdInfoReading` method to `AdjustConfig2dx` to allow option for users to prevent SDK from performing any tasks related to Apple Search Ads attribution with usage of `iAd.framework`.
- Added wrapper method `updateConversionValue` method to `Adjust2dx` to allow updating SKAdNetwork conversion value via SDK API.
- Added `getAppTrackingAuthorizationStatus` getter to `Adjust2dx` instance to be able to get current iOS app tracking status.
- Added improved measurement consent management and third party sharing mechanism.
- Added data residency feature. You can choose this setting by calling `setUrlStrategy` method of `AdjustConfig2dx` instance with `AdjustDataResidencyEU` (for EU data residency region), `AdjustDataResidencyTR` (for TR data residency region) or `AdjustDataResidencyUS` value (for US data residency region).
- Added `setConversionValueUpdatedCallback` method to `AdjustConfig2dx` which can be used to set a callback which will get information when Adjust SDK updates conversion value for the user.
- Added preinstall tracking with usage of system installer receiver on Android platform (`setPreinstallFilePath` method of the `AdjustConfig2dx`).

#### Native SDKs
- [iOS@v4.29.6][ios_sdk_v4.29.6]
- [Android@v4.28.4][android_sdk_v4.28.4]

---

### Version 4.28.0 (3rd April 2021)
#### Changed
- Removed native iOS legacy code.

#### Native SDKs
- [iOS@v4.28.0][ios_sdk_v4.28.0]
- [Android@v4.27.0][android_sdk_v4.27.0]

---

### Version 4.23.1 (29th September 2020)
#### Fixed
- Fixed duplicate `ADJUrlStrategy` symbol error.

#### Native SDKs
- [iOS@v4.23.2][ios_sdk_v4.23.2]
- [Android@v4.24.1][android_sdk_v4.24.1]

---

### Version 4.23.0 (26th August 2020)
#### Added
- Added communication with SKAdNetwork framework by default on iOS 14.
- Added method `deactivateSKAdNetworkHandling` method to `AdjustConfig2dx` to switch off default communication with SKAdNetwork framework in iOS 14.
- Added wrapper method `requestTrackingAuthorizationWithCompletionHandler` to `Adjust2dx` to allow asking for user's consent to be tracked in iOS 14 and immediate propagation of user's choice to backend.
- Added handling of new iAd framework error codes introduced in iOS 14.
- Added sending of value of user's consent to be tracked with each package.
- Added `setUrlStrategy` method to `AdjustConfig2dx` class to allow selection of URL strategy for specific market.

#### Native SDKs
- [iOS@v4.23.0][ios_sdk_v4.23.0]
- [Android@v4.24.0][android_sdk_v4.24.0]

---

### Version 4.22.0 (17th June 2020)
#### Added
- Added subscription tracking feature.
- Added support for Huawei App Gallery install referrer.
- Added `disableThirdPartySharing` method to `Adjust2dx` interface to allow disabling of data sharing with third parties outside of Adjust ecosystem.
- Added support for signature library as a plugin.
- Added more aggressive sending retry logic for install session package.
- Added additional parameters to `ad_revenue` package payload.
- Added external device ID support.

#### Changed
- Updated communication flow with `iAd.framework`.

#### Native SDKs
- [iOS@v4.22.1][ios_sdk_v4.22.1]
- [Android@v4.22.0][android_sdk_v4.22.0]

---

### Version 4.18.0 (4th July 2019)
#### Added
- Added `trackAdRevenue` method to `Adjust2dx` interface to allow tracking of ad revenue. With this release added support for `MoPub` ad revenue tracking.
- Added reading of Facebook anonymous ID if available on iOS platform.

#### Native SDKs
- [iOS@v4.18.0][ios_sdk_v4.18.0]
- [Android@v4.18.0][android_sdk_v4.18.0]

---

### Version 4.17.1 (22nd March 2019)
#### Added
- Added support for `Cocos2d-x v2.2.6`.

#### Native SDKs
- [iOS@v4.17.2][ios_sdk_v4.17.2]
- [Android@v4.17.0][android_sdk_v4.17.0]

---

### Version 4.17.0 (18th January 2019)
#### Added
- Added `getSdkVersion` method to `Adjust2dx` interface to obtain current SDK version string.
- Added `setCallbackId` method on `AdjustEvent2dx` object for users to set custom ID on event object which will later be reported in event success/failure callbacks.
- Added `callbackId` field to event tracking success callback object.
- Added `callbackId` field to event tracking failure callback object.

#### Changed
- Marked `setReadMobileEquipmentIdentity` method of `AdjustConfig2dx` object as deprecated.
- SDK will now fire attribution request each time upon session tracking finished in case it lacks attribution info.

#### Native SDKs
- [iOS@v4.17.1][ios_sdk_v4.17.1]
- [Android@v4.17.0][android_sdk_v4.17.0]

---

### Version 4.14.0 (9th July 2018)
#### Added
- Added deep link caching in case `appWillOpenUrl` method is called before SDK is initialised.

#### Changed
- Removed support for Windows platform.
- Updated the way how iOS native bridge handles push tokens from Cocos2d-x interface - they are now being passed directly as strings to native iOS SDK.
- Merged different platform `README` files into one.

#### Native SDKs
- [iOS@v4.14.1][ios_sdk_v4.14.1]
- [Android@v4.14.0][android_sdk_v4.14.0]

---

### Version 4.13.0 (22nd May 2018)
#### Added
- Added `gdprForgetMe` method to `Adjust2dx` interface to enable possibility for user to be forgotten in accordance with GDPR law.

#### Native SDKs
- [iOS@v4.13.0][ios_sdk_v4.13.0]
- [Android@v4.13.0][android_sdk_v4.13.0]
- [Windows SDK 4.0.3][windows_sdk_v4.0.3]

---

### Version 4.12.1 (12th March 2018)
#### Native changes
- Updated Android SDK to `v4.12.4`.

#### Native SDKs
- [iOS@v4.12.3][ios_sdk_v4.12.3]
- [Android@v4.12.4][android_sdk_v4.12.4]
- [Windows SDK 4.0.3][windows_sdk_v4.0.3]

---

### Version 4.12.0 (5th March 2017)
#### Native changes:
- https://github.com/adjust/ios_sdk/blob/master/CHANGELOG.md#version-4120-13th-december-2017
- https://github.com/adjust/ios_sdk/blob/master/CHANGELOG.md#version-4121-13th-december-2017
- https://github.com/adjust/ios_sdk/blob/master/CHANGELOG.md#version-4122-13th-february-2018
- https://github.com/adjust/android_sdk/blob/master/CHANGELOG.md#version-4120-13th-december-2017
- https://github.com/adjust/android_sdk/blob/master/CHANGELOG.md#version-4121-31st-january-2018
- https://github.com/adjust/android_sdk/blob/master/CHANGELOG.md#version-4122-28th-february-2018

#### Added
- Added `getAmazonAdId` method to `Adjust2dx` interface.
- Added `setReadMobileEquipmentIdentity` method to `AdjustConfig2dx` interface.
- Added `setAppSecret` method to `AdjustConfig2dx` interface (**iOS and Android only**).

#### Native SDKs
- [iOS@v4.12.3][ios_sdk_v4.12.3]
- [Android@v4.12.2][android_sdk_v4.12.2]
- [Windows SDK 4.0.3][windows_sdk_v4.0.3]

---

### Version 4.11.3 (28th September 2017)
#### Added
- **[iOS]** Improved iOS 11 support.

#### Changed
- **[iOS]** Removed iOS connection validity checks.
- **[iOS]** Updated native iOS SDK to version **4.11.5**.

#### Native SDKs
- **[iOS]** [iOS SDK 4.11.5][ios_sdk_v4.11.5]
- **[AND]** [Android SDK 4.11.4][android_sdk_v4.11.4]
- **[WIN]** [Windows SDK 4.0.3][windows_sdk_v4.0.3]
 
---

### Version 4.11.2 (19th May 2017)
#### Added
- **[iOS][AND]** Added check if `sdk_click` package response contains attribution information.
- **[iOS][AND]** Added sending of attributable parameters with every `sdk_click` package.

#### Changed
- **[iOS][AND]** Replaced `assert` level logs with `warn` level.

#### Native SDKs
- **[iOS]** [iOS SDK 4.11.4][ios_sdk_v4.11.4]
- **[AND]** [Android SDK 4.11.4][android_sdk_v4.11.4]
- **[WIN]** [Windows SDK 4.0.3][windows_sdk_v4.0.3]

---

### Version 4.11.1 (27th April 2017)
#### Added
- **[iOS]** Added nullability annotations to public headers for Swift 3.0 compatibility.
- **[iOS]** Added `BITCODE_GENERATION_MODE` to iOS framework for `Carthage` support.
- **[iOS]** Added support for iOS 10.3.
- **[iOS][AND]** Added sending of the app's install time.
- **[iOS][AND]** Added sending of the app's update time.

#### Fixed
- **[iOS]** Fixed not processing of `sdk_info` package type causing logs not to print proper package name once tracked.
- **[AND]** Fixed query string parsing.
- **[AND]** Fixed issue of creating and destroying lots of threads on certain Android API levels (https://github.com/adjust/android_sdk/issues/265).
- **[AND]** Protected `Package Manager` from throwing unexpected exceptions (https://github.com/adjust/android_sdk/issues/266).

#### Changed
- **[iOS]** If `adid` and `idfa` values are not available, return empty string.
- **[AND]** Refactored native networking code.
- **[iOS]** Updated native iOS SDK to version **4.11.3**.
- **[AND]** Updated native Android SDK to version **4.11.3**.
- **[REPO]** Introduced `[iOS]`, `[AND]`, `[WIN]` and `[REPO]` tags to `CHANGELOG` to highlight the platform the change is referring to.

#### Native SDKs
- **[iOS]** [iOS SDK 4.11.3][ios_sdk_v4.11.3]
- **[AND]** [Android SDK 4.11.3][android_sdk_v4.11.3]
- **[WIN]** [Windows SDK 4.0.3][windows_sdk_v4.0.3]

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
- **[WIN]** [Windows SDK 4.0.3][windows_sdk_v4.0.3]

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
[ios_sdk_v4.11.4]: https://github.com/adjust/ios_sdk/tree/v4.11.4
[ios_sdk_v4.11.5]: https://github.com/adjust/ios_sdk/tree/v4.11.5
[ios_sdk_v4.12.1]: https://github.com/adjust/ios_sdk/tree/v4.12.1
[ios_sdk_v4.12.3]: https://github.com/adjust/ios_sdk/tree/v4.12.3
[ios_sdk_v4.13.0]: https://github.com/adjust/ios_sdk/tree/v4.13.0
[ios_sdk_v4.14.1]: https://github.com/adjust/ios_sdk/tree/v4.14.1
[ios_sdk_v4.17.1]: https://github.com/adjust/ios_sdk/tree/v4.17.1
[ios_sdk_v4.17.2]: https://github.com/adjust/ios_sdk/tree/v4.17.2
[ios_sdk_v4.18.0]: https://github.com/adjust/ios_sdk/tree/v4.18.0
[ios_sdk_v4.22.1]: https://github.com/adjust/ios_sdk/tree/v4.22.1
[ios_sdk_v4.23.0]: https://github.com/adjust/ios_sdk/tree/v4.23.0
[ios_sdk_v4.23.2]: https://github.com/adjust/ios_sdk/tree/v4.23.2
[ios_sdk_v4.28.0]: https://github.com/adjust/ios_sdk/tree/v4.28.0
[ios_sdk_v4.29.6]: https://github.com/adjust/ios_sdk/tree/v4.29.6
[ios_sdk_v4.32.1]: https://github.com/adjust/ios_sdk/tree/v4.32.1
[ios_sdk_v4.37.0]: https://github.com/adjust/ios_sdk/tree/v4.37.0
[ios_sdk_v5.0.1]: https://github.com/adjust/ios_sdk/tree/v5.0.1
[ios_sdk_v5.0.2]: https://github.com/adjust/ios_sdk/tree/v5.0.2
[ios_sdk_v5.4.0]: https://github.com/adjust/ios_sdk/tree/v5.4.0

[android_sdk_v4.0.8]: https://github.com/adjust/android_sdk/tree/v4.0.8
[android_sdk_v4.1.0]: https://github.com/adjust/android_sdk/tree/v4.1.0
[android_sdk_v4.1.2]: https://github.com/adjust/android_sdk/tree/v4.1.2
[android_sdk_v4.2.3]: https://github.com/adjust/android_sdk/tree/v4.2.3
[android_sdk_v4.10.2]: https://github.com/adjust/android_sdk/tree/v4.10.2
[android_sdk_v4.11.0]: https://github.com/adjust/android_sdk/tree/v4.11.0
[android_sdk_v4.11.1]: https://github.com/adjust/android_sdk/tree/v4.11.1
[android_sdk_v4.11.3]: https://github.com/adjust/android_sdk/tree/v4.11.3
[android_sdk_v4.11.4]: https://github.com/adjust/android_sdk/tree/v4.11.4
[android_sdk_v4.12.0]: https://github.com/adjust/android_sdk/tree/v4.12.0
[android_sdk_v4.12.2]: https://github.com/adjust/android_sdk/tree/v4.12.2
[android_sdk_v4.12.4]: https://github.com/adjust/android_sdk/tree/v4.12.4
[android_sdk_v4.13.0]: https://github.com/adjust/android_sdk/tree/v4.13.0
[android_sdk_v4.14.0]: https://github.com/adjust/android_sdk/tree/v4.14.0
[android_sdk_v4.17.0]: https://github.com/adjust/android_sdk/tree/v4.17.0
[android_sdk_v4.18.0]: https://github.com/adjust/android_sdk/tree/v4.18.0
[android_sdk_v4.22.0]: https://github.com/adjust/android_sdk/tree/v4.22.0
[android_sdk_v4.24.0]: https://github.com/adjust/android_sdk/tree/v4.24.0
[android_sdk_v4.24.1]: https://github.com/adjust/android_sdk/tree/v4.24.1
[android_sdk_v4.27.0]: https://github.com/adjust/android_sdk/tree/v4.27.0
[android_sdk_v4.28.4]: https://github.com/adjust/android_sdk/tree/v4.28.4
[android_sdk_v4.33.0]: https://github.com/adjust/android_sdk/tree/v4.33.0
[android_sdk_v4.38.0]: https://github.com/adjust/android_sdk/tree/v4.38.0
[android_sdk_v5.0.1]: https://github.com/adjust/android_sdk/tree/v5.0.1
[android_sdk_v5.0.2]: https://github.com/adjust/android_sdk/tree/v5.0.2
[android_sdk_v5.4.0]: https://github.com/adjust/android_sdk/tree/v5.4.0

[windows_sdk_v4.0.3]: https://github.com/adjust/windows_sdk/tree/v4.0.3
