package com.adjust.sdk;

public class Adjust2dxAttributionReadCallback implements OnAttributionReadListener {
	public native void attributionRead(Object attribution);
	public native void attributionReadWithId(Object attribution, long callbackId);

	private long callbackId = 0;

	public Adjust2dxAttributionReadCallback() {}

	public Adjust2dxAttributionReadCallback(long callbackId) {
		this.callbackId = callbackId;
	}

	@Override
	public void onAttributionRead(AdjustAttribution attribution) {
		if (callbackId != 0) {
			attributionReadWithId(attribution, callbackId);
		} else {
			attributionRead(attribution);
		}
	}
}
