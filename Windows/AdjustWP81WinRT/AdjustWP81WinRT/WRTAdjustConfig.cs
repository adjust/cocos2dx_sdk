using System;

using AdjustSdk;
using System.Runtime.InteropServices;
using System.IO;

namespace AdjustWinRT
{
    public sealed class WRTAdjustConfig
    {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate void LogCallback([MarshalAs(UnmanagedType.LPStr)] string logLine);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate void AttributionCallback(
            [MarshalAs(UnmanagedType.LPStr)] string trackerToken,
            [MarshalAs(UnmanagedType.LPStr)] string trackerName, 
            [MarshalAs(UnmanagedType.LPStr)] string network, 
            [MarshalAs(UnmanagedType.LPStr)] string campaign, 
            [MarshalAs(UnmanagedType.LPStr)] string adgroup, 
            [MarshalAs(UnmanagedType.LPStr)] string creative, 
            [MarshalAs(UnmanagedType.LPStr)] string clickLabel);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate void FileWriteCallback(
            [MarshalAs(UnmanagedType.LPStr)] string fileName,
            [MarshalAs(UnmanagedType.LPArray)] byte[] newContent);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate Int32 FileReadCallback(
            [MarshalAs(UnmanagedType.LPStr)] string fileName, ref int size);

        private string appToken;
        private string sdkPrefix;
        private string environment;
        private string defaultTracker;

        private LogLevel logLevel;

        private bool? isEventBufferingEnabled;

        private AdjustConfig nativeConfig;

        private LogCallback nativeLogCallback;
        private FileReadCallback nativeFileReadCallback;
        private FileWriteCallback nativeFileWriteCallback;
        private AttributionCallback nativeAttributionCallback;

        private Action<string> rtLogCallback;
        private Func<string, byte[]> rtFileReadCallback;
        private Action<string, byte[]> rtFileWriteCallback;
        private Action<AdjustAttribution> rtAttributionCallback;

        public WRTAdjustConfig(string appToken, string environment)
        {
            this.appToken = appToken;
            this.environment = environment;
            this.sdkPrefix = "cocos2d-x4.11.1";
            
            this.logLevel = LogLevel.Info;

            this.rtLogCallback = null;
            this.defaultTracker = null;
            this.rtFileReadCallback = null;
            this.rtFileWriteCallback = null;
            this.rtAttributionCallback = null;
            this.isEventBufferingEnabled = null;
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

            if (this.rtFileReadCallback != null)
            {
                this.nativeConfig.FileReader = this.rtFileReadCallback;
            }

            if (this.rtFileWriteCallback != null)
            {
                this.nativeConfig.FileWriter = this.rtFileWriteCallback;
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
            this.logLevel = (LogLevel)logLevel;

            IntPtr ptrLogDelegate = new IntPtr(logDelegate);
            this.nativeLogCallback = (LogCallback)Marshal.GetDelegateForFunctionPointer<LogCallback>(ptrLogDelegate);
            this.rtLogCallback = RTLogCallback;
        }

        public void SetDefaultTracker(string defaultTracker)
        {
            nativeConfig.DefaultTracker = defaultTracker;
        }

        public void SetFileWritingCallback(Int64 fileWriteCallback)
        {
            IntPtr ptrFileWriteDelegate = new IntPtr(fileWriteCallback);
            this.nativeFileWriteCallback = (FileWriteCallback)Marshal.GetDelegateForFunctionPointer<FileWriteCallback>(ptrFileWriteDelegate);
            this.rtFileWriteCallback = RTFileWriteCallback;
        }

        public void SetFileReadingCallback(Int64 fileReadCallback)
        {
            IntPtr ptrFileReadDelegate = new IntPtr(fileReadCallback);
            this.nativeFileReadCallback = (FileReadCallback)Marshal.GetDelegateForFunctionPointer<FileReadCallback>(ptrFileReadDelegate);
            this.rtFileReadCallback = RTFileReadCallback;
        }

        public void SetAttributionCallback(Int64 attributionDelegate)
        {
            IntPtr ptrAttributionDelegate = new IntPtr(attributionDelegate);
            this.nativeAttributionCallback = (AttributionCallback)Marshal.GetDelegateForFunctionPointer<AttributionCallback>(ptrAttributionDelegate);
            this.rtAttributionCallback = RTAttributionCallback;
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

        private void RTLogCallback(string logLine)
        {
            nativeLogCallback(logLine);
        }

        private byte[] RTFileReadCallback(string fileName)
        {
            try {
                int size = 0;
                IntPtr ptrReadContent = new IntPtr(nativeFileReadCallback(fileName, ref size));
                byte[] managedArray = new byte[size];
                Marshal.Copy(ptrReadContent, managedArray, 0, size);

                return managedArray;
            }
            catch (Exception e)
            {
                return null;
            }
        }

        private void RTFileWriteCallback(string fileName, byte[] newContent)
        {
            nativeFileWriteCallback(fileName, newContent);
        }

        private void RTAttributionCallback(AdjustAttribution attribution)
        {
            nativeAttributionCallback(attribution.TrackerToken, attribution.TrackerName, attribution.Network, attribution.Campaign, attribution.Adgroup, attribution.Creative, attribution.ClickLabel);
        }
    }
}
