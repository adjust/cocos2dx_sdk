package com.adjust.sdk;

public class Adjust2dxAmazonAdIdCallback implements OnAmazonAdIdReadListener {
	public native void amazonAdIdRead(String amazonAdId);
	public native void amazonAdIdReadWithId(String amazonAdId, long callbackId);

	private long callbackId = 0;

	public Adjust2dxAmazonAdIdCallback() {}

	public Adjust2dxAmazonAdIdCallback(long callbackId) {
		this.callbackId = callbackId;
	}

	@Override
	public void onAmazonAdIdRead(String amazonAdId) {
		if (callbackId != 0) {
			amazonAdIdReadWithId(amazonAdId, callbackId);
		} else {
			amazonAdIdRead(amazonAdId);
		}
	}
}
