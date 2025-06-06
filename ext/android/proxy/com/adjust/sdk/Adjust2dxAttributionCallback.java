package com.adjust.sdk;

public class Adjust2dxAttributionCallback implements OnAttributionChangedListener {
	public native void attributionChanged(Object attribution);
	
	public Adjust2dxAttributionCallback() {}
	
	@Override
	public void onAttributionChanged(AdjustAttribution attribution) {
		attributionChanged(attribution);
	}
}
