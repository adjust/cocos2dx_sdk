package com.adjust.sdk;

public class Adjust2dxGoogleAdIdCallback implements OnGoogleAdIdReadListener {
	public native void adIdRead(String adId);

	public Adjust2dxGoogleAdIdCallback() {}

	@Override
	public void onGoogleAdIdRead(String playAdId) {
		adIdRead(playAdId);
	}
}
