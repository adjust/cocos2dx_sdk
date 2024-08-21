package com.adjust.sdk;

public class Adjust2dxAmazonAdIdCallback implements OnAmazonAdIdReadListener {
	public native void adIdRead(String adId);
	
	public Adjust2dxAmazonAdIdCallback() {}
	
	@Override
	public void onAmazonAdIdRead(String amazonAdId) {
		adIdRead(amazonAdId);
	}
}
