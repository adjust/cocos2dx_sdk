package com.adjust.sdk;

public class Adjust2dxAmazonAdIdCallback implements OnAmazonAdIdReadListener {
	public native void amazonAdIdRead(String amazonAdId);

	public Adjust2dxAmazonAdIdCallback() {}

	@Override
	public void onAmazonAdIdRead(String amazonAdId) {
		amazonAdIdRead(amazonAdId);
	}
}
