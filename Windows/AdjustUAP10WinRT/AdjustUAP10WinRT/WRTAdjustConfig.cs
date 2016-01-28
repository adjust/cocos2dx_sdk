using System;

using AdjustSdk;
using System.Runtime.InteropServices;

namespace AdjustUAP10WinRT
{
    public sealed class WRTAdjustConfig
    {
        private delegate void LogCallback([MarshalAs(UnmanagedType.LPStr)] string logLine);
        private delegate void AttributionCallback(
            [MarshalAs(UnmanagedType.LPStr)] string trackerToken,
            [MarshalAs(UnmanagedType.LPStr)] string trackerName, 
            [MarshalAs(UnmanagedType.LPStr)] string network, 
            [MarshalAs(UnmanagedType.LPStr)] string campaign, 
            [MarshalAs(UnmanagedType.LPStr)] string adgroup, 
            [MarshalAs(UnmanagedType.LPStr)] string creative, 
            [MarshalAs(UnmanagedType.LPStr)] string clickLabel);

        private string appToken;
        private string sdkPrefix;
        private string environment;
        private string defaultTracker;

        private LogLevel logLevel;

        private bool? isEventBufferingEnabled;

        private AdjustConfig nativeConfig;

        private LogCallback nativeLogCallback;
        private AttributionCallback nativeAttributionCallback;

        private Action<String> rtLogCallback;
        private Action<AdjustAttribution> rtAttributionCallback;

        public WRTAdjustConfig(string appToken, string environment)
        {
            System.Diagnostics.Debug.WriteLine("Constructor start!");
            this.appToken = appToken;
            this.environment = environment;
            this.sdkPrefix = "cocos2d-x4.2.0";
            
            this.logLevel = LogLevel.Info;

            this.rtLogCallback = null;
            this.defaultTracker = null;
            this.rtAttributionCallback = null;
            this.isEventBufferingEnabled = null;
            System.Diagnostics.Debug.WriteLine("Constructor end!");
        }

        public void BuildNativeConfig()
        {
            this.nativeConfig = new AdjustConfig(this.appToken, this.environment);
            this.nativeConfig.SdkPrefix = this.sdkPrefix;

            if (this.defaultTracker != null)
            {
                this.nativeConfig.DefaultTracker = this.defaultTracker;
            }

            if (this.isEventBufferingEnabled != null)
            {
                this.nativeConfig.EventBufferingEnabled = (bool)this.isEventBufferingEnabled;
            }

            if (this.rtAttributionCallback != null)
            {
                this.nativeConfig.AttributionChanged = this.rtAttributionCallback;
            }
        }

        public bool IsValid()
        {
            return nativeConfig.IsValid();
        }

        public void SetEventBufferingEnabled(bool isEnabled)
        {
            nativeConfig.EventBufferingEnabled = isEnabled;
        }

        public void SetLogLevel(int logLevel, Int64 logDelegate)
        {
            System.Diagnostics.Debug.WriteLine("Log level and delegate start!");
            this.logLevel = (LogLevel)logLevel;

            IntPtr ptrLogDelegate = new IntPtr(logDelegate);
            this.nativeLogCallback = (LogCallback)Marshal.GetDelegateForFunctionPointer<LogCallback>(ptrLogDelegate);
            this.rtLogCallback = RTLogCallback;
            System.Diagnostics.Debug.WriteLine("Log level and delegate end!");
        }

        public void SetDefaultTracker(string defaultTracker)
        {
            nativeConfig.DefaultTracker = defaultTracker;
        }

        public void SetAttributionCallback(Int64 attributionDelegate)
        {
            System.Diagnostics.Debug.WriteLine("Attribution delegate start!");
            IntPtr ptrAttributionDelegate = new IntPtr(attributionDelegate);
            this.nativeAttributionCallback = (AttributionCallback)Marshal.GetDelegateForFunctionPointer<AttributionCallback>(ptrAttributionDelegate);
            this.rtAttributionCallback = RTAttributionCallback;
            System.Diagnostics.Debug.WriteLine("Attribution delegate end!");
        }

        public int GetLogLevel()
        {
            return (int)this.logLevel;
        }

        public Object GetLogDelegate()
        {
            return this.rtLogCallback;
        }

        public Object GetNativeConfig()
        {
            return this.nativeConfig;
        }

        private void RTLogCallback(String logLine)
        {
            nativeLogCallback(logLine);
        }

        private void RTAttributionCallback(AdjustAttribution attribution)
        {
            nativeAttributionCallback(attribution.TrackerToken, attribution.TrackerName, attribution.Network, attribution.Campaign, attribution.Adgroup, attribution.Creative, attribution.ClickLabel);
        }
    }
}
