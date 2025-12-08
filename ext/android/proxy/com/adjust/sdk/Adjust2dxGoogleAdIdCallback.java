package com.adjust.sdk;

public class Adjust2dxGoogleAdIdCallback implements OnGoogleAdIdReadListener {
	public native void googleAdIdRead(String googleAdId);
	public native void googleAdIdReadWithId(String googleAdId, long callbackId);

	private long callbackId = 0;

	public Adjust2dxGoogleAdIdCallback() {}

	public Adjust2dxGoogleAdIdCallback(long callbackId) {
		this.callbackId = callbackId;
	}

	@Override
	public void onGoogleAdIdRead(String googleAdId) {
		if (callbackId != 0) {
			googleAdIdReadWithId(googleAdId, callbackId);
		} else {
			googleAdIdRead(googleAdId);
		}
	}
}
