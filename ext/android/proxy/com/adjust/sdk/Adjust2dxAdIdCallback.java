package com.adjust.sdk;

public class Adjust2dxAdIdCallback implements OnDeviceIdsRead {
	public native void adIdRead(String adId);
	
	public Adjust2dxAdIdCallback() {}
	
	@Override
	public void onGoogleAdIdRead(String playAdId) {
		adIdRead(playAdId);
	}
}
