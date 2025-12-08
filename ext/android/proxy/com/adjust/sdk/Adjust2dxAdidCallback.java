package com.adjust.sdk;

public class Adjust2dxAdidCallback implements OnAdidReadListener {
	public native void adidRead(String adid);
	public native void adidReadWithId(String adid, long callbackId);

	private long callbackId = 0;

	public Adjust2dxAdidCallback() {}

	public Adjust2dxAdidCallback(long callbackId) {
		this.callbackId = callbackId;
	}

	@Override
	public void onAdidRead(String adid) {
		if (callbackId != 0) {
			adidReadWithId(adid, callbackId);
		} else {
			adidRead(adid);
		}
	}
}
