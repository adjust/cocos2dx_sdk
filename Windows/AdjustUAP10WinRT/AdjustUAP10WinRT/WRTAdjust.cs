using AdjustSdk;
using System;

namespace AdjustWinRT
{
    public sealed class WRTAdjust
    {
        public static void ApplicationLaunching(WRTAdjustConfig adjustConfig)
        {
            if (adjustConfig.GetLogDelegate() != null)
            {
                Adjust.SetupLogging((Action<String>)adjustConfig.GetLogDelegate(), (LogLevel)adjustConfig.GetLogLevel());
            }

            adjustConfig.BuildNativeConfig();

            Adjust.ApplicationLaunching((AdjustConfig)adjustConfig.GetNativeConfig());
        }

        public static void ApplicationActivated()
        {
            Adjust.ApplicationActivated();
        }

        public static void ApplicationDeactivated()
        {
            Adjust.ApplicationDeactivated();
        }

        public static void TrackEvent(WRTAdjustEvent adjustEvent)
        {
            Adjust.TrackEvent((AdjustEvent)adjustEvent.GetNativeEvent());
        }

        public static void SetEnabled(bool isEnabled)
        {
            Adjust.SetEnabled(isEnabled);
        }

        public static bool IsEnabled()
        {
            return Adjust.IsEnabled();
        }

        public static void SetOfflineMode(bool isEnabled)
        {
            Adjust.SetOfflineMode(isEnabled);
        }

        public static void AppWillOpenURL(Uri uri)
        {
            Adjust.AppWillOpenUrl(uri);
        }

        public static string GetWindowsAdId()
        {
            return Adjust.GetWindowsAdId();
        }
    }
}
