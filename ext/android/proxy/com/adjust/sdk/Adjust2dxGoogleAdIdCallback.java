package com.adjust.sdk;

public class Adjust2dxGoogleAdIdCallback implements OnGoogleAdIdReadListener {
	public native void googleAdIdRead(String googleAdId);

	public Adjust2dxGoogleAdIdCallback() {}

	@Override
	public void onGoogleAdIdRead(String googleAdId) {
		googleAdIdRead(googleAdId);
	}
}
