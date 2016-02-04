using AdjustSdk;
using System;

namespace AdjustWinRT
{
    public sealed class WRTAdjustEvent
    {
        private AdjustEvent nativeEvent;

        public WRTAdjustEvent(string eventToken)
        {
            nativeEvent = new AdjustEvent(eventToken);
        }

        public void SetRevenue(double revenue, string currency)
        {
            nativeEvent.SetRevenue(revenue, currency);
        }

        public void AddCallbackParameter(string key, string value)
        {
            nativeEvent.AddCallbackParameter(key, value);
        }

        public void AddPartnerParameter(string key, string value)
        {
            nativeEvent.AddPartnerParameter(key, value);
        }

        public bool IsValid()
        {
            return nativeEvent.IsValid();
        }

        public Object GetNativeEvent()
        {
            return nativeEvent;
        }
    }
}
