### Version 4.10.0 (7th November 2016)
**Note: All changes in this release are for iOS and Android platform only.**
#### Added
- Added support for iOS 10.
- Added revenue deduplication for Android platform.
- Added an option for enabling/disabling tracking while app is in background.
- Added a callback to be triggered if event is successfully tracked.
- Added a callback callback to be triggered if event tracking failed.
- Added a callback to be triggered if session is successfully tracked.
- Added a callback to be triggered if session tracking failed.
- Added possibility to set session callback and partner parameters with `addSessionCallbackParameter` and `addSessionPartnerParameter` methods.
- Added possibility to remove session callback and partner parameters by key with `removeSessionCallbackParameter` and `removeSessionPartnerParameter` methods.
- Added possibility to remove all session callback and partner parameters with `resetSessionCallbackParameters and `resetSessionPartnerParameters` methods.
- Added new Suppress log level.
- Added possibility to delay initialisation of the SDK while maybe waiting to obtain some session callback or partner parameters with delayed start feature on adjust config instance.
- Added callback method to get deferred deep link content into the app.
- Added possibility to decide whether the SDK should launch the deferred deep link or not.
- Added possibility to set user agent manually on adjust config instance.

#### Fixed
- Fixed `setEventBufferingEnabled` JNI signature.

#### Changed
- Deferred deep link info will now arrive as part of the attribution response and not as part of the answer to first session.
- Updated docs.
- Native SDKs stability updates and improvements.
- Updated native iOS SDK to version 4.10.2.
- Updated native Android SDK to version 4.10.2.

#### Native SDKs
- [iOS@v4.10.2][ios_sdk_v4.10.2]
- [Android@v4.10.2][android_sdk_v4.10.2]
- [Windows@4.0.3][windows_sdk_v4.0.3]

---

### Version 4.2.0 (12th February 2016)
#### Added
- Added support for Windows platform.
- Added `CHANGELOG.md`.
- Added instructions for Android Studio in Android README.
- Added `getIdfa` method for getting `IDFA` on iOS device.
- Added `getGoogleAdId` method for getting `Google Play Services Ad Id` on Android device.
- Added `getWindowsAdId` method for getting `Windows Advertisement Id` on Windows device.

#### Changed
- Renamed `Adjust.framework` to `AdjustSdk.framework`.
- Removed `MAC MD5` tracking feature for `iOS platform` completely.
- Updated documentation.
- Updated Native iOS SDK to version **4.5.4**.
- Updated Native Android SDK to version **4.2.3**.

#### Native SDKs
- [iOS@v4.5.4][ios_sdk_v4.5.4]
- [Android@v4.2.3][android_sdk_v4.2.3]
- [Windows@4.0.3][windows_sdk_v4.0.3]

---

### Version 4.1.0 (17th September 2015)
#### Added
- Added additional methods to C++ interface.

#### Changed
- Moved calls from Java code to C++.
- Updated Native iOS SDK to version **4.3.0**.
- Updated Native Android SDK to version **4.1.2**.

#### Native SDKs
- [iOS@v4.3.0][ios_sdk_v4.3.0]
- [Android@v4.1.2][android_sdk_v4.1.2]

---

### Version 4.0.1 (17th July 2015)
#### Changed
- Updated Native iOS SDK to version **4.2.7**.
- Updated Native Android SDK to version **4.1.0**.
- Updated documentation

#### Native SDKs
- [iOS@v4.2.7][ios_sdk_v4.2.7]
- [Android@v4.1.0][android_sdk_v4.1.0]

---

### Version 4.0.0 (25th June 2015)
#### Added
- Initial release of the adjust SDK for Cocos2d-x.
- Supported platforms: `iOS` and `Android`.

#### Native SDKs
- [iOS@v4.2.6][ios_sdk_v4.2.6]
- [Android@v4.0.8][android_sdk_v4.0.8]

[ios_sdk_v4.2.6]: https://github.com/adjust/ios_sdk/tree/v4.2.6
[ios_sdk_v4.2.7]: https://github.com/adjust/ios_sdk/tree/v4.2.7
[ios_sdk_v4.3.0]: https://github.com/adjust/ios_sdk/tree/v4.3.0
[ios_sdk_v4.5.4]: https://github.com/adjust/ios_sdk/tree/v4.5.4
[ios_sdk_v4.10.2]: https://github.com/adjust/ios_sdk/tree/v4.10.2

[android_sdk_v4.0.8]: https://github.com/adjust/android_sdk/tree/v4.0.8
[android_sdk_v4.1.0]: https://github.com/adjust/android_sdk/tree/v4.1.0
[android_sdk_v4.1.2]: https://github.com/adjust/android_sdk/tree/v4.1.2
[android_sdk_v4.2.3]: https://github.com/adjust/android_sdk/tree/v4.2.3
[android_sdk_v4.10.2]: https://github.com/adjust/android_sdk/tree/v4.10.2

[windows_sdk_v4.0.3]: https://github.com/adjust/windows_sdk/tree/v4.0.3
