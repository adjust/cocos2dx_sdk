package com.adjust.sdk;

public class Adjust2dxAdidCallback implements OnAdidReadListener {
	public native void adidRead(String adid);

	public Adjust2dxAdidCallback() {}

	@Override
	public void onAdidRead(String adid) {
		adidRead(adid);
	}
}
