using AdjustSdk;
using System;

namespace AdjustUAP10WinRT
{
    public sealed class WRTAdjust
    {
        public static void ApplicationLaunching(WRTAdjustConfig adjustConfig)
        {
            System.Diagnostics.Debug.WriteLine("Initialisation start!");
            if (adjustConfig.GetLogDelegate() != null)
            {
                Adjust.SetupLogging((Action<String>)adjustConfig.GetLogDelegate(), (LogLevel)adjustConfig.GetLogLevel());
            }
            System.Diagnostics.Debug.WriteLine("Logging setup end!");

            System.Diagnostics.Debug.WriteLine("Initialisation start!");
            adjustConfig.BuildNativeConfig();

            if (adjustConfig.GetNativeConfig() == null)
            {
                System.Diagnostics.Debug.WriteLine("Native config is null!");
            }
            else
            {
                System.Diagnostics.Debug.WriteLine("Native config is NOT null!");
            }

            Adjust.ApplicationLaunching((AdjustConfig)adjustConfig.GetNativeConfig());
            System.Diagnostics.Debug.WriteLine("Initialisation end!");
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
    }
}
