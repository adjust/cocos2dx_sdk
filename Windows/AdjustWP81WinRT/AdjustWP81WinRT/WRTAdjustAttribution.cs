using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdjustWinRT
{
    public sealed class WRTAdjustAttribution
    {
        public string TrackerToken { get; set; }

        public string TrackerName { get; set; }

        public string Network { get; set; }

        public string Campaign { get; set; }

        public string Adgroup { get; set; }

        public string Creative { get; set; }

        public string ClickLabel { get; set; }
    }
}
