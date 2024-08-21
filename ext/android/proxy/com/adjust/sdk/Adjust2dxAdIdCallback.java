package com.adjust.sdk;

public class Adjust2dxAdIdCallback implements OnAdidReadListener {
	public native void adIdRead(String adId);

	public Adjust2dxAdIdCallback() {}

	@Override
	public void onAdidRead(String adId) {
		adIdRead(adId);
	}
}
