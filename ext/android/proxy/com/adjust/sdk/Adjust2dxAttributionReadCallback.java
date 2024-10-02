package com.adjust.sdk;

public class Adjust2dxAttributionReadCallback implements OnAttributionReadListener {
	public native void attributionRead(Object attribution);

	public Adjust2dxAttributionReadCallback() {}

	@Override
	public void onAttributionRead(AdjustAttribution attribution) {
		attributionRead(attribution);
	}
}
