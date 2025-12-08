package com.adjust.sdk;

public class Adjust2dxIsEnabledCallback implements OnIsEnabledListener {
	public native void isEnabledRead(boolean isEnabled);
	public native void isEnabledReadWithId(boolean isEnabled, long callbackId);

	private long callbackId = 0;

	public Adjust2dxIsEnabledCallback() {}

	public Adjust2dxIsEnabledCallback(long callbackId) {
		this.callbackId = callbackId;
	}

	@Override
	public void onIsEnabledRead(boolean isEnabled) {
		if (callbackId != 0) {
			isEnabledReadWithId(isEnabled, callbackId);
		} else {
			isEnabledRead(isEnabled);
		}
	}
}
