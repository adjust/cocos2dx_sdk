package com.adjust.sdk;

public class Adjust2dxSdkVersionCallback implements OnSdkVersionReadListener {
	public native void sdkVersionRead(String sdkVersion);

	public Adjust2dxSdkVersionCallback() {}

	@Override
	public void onSdkVersionRead(String sdkVersion) {
		sdkVersionRead(sdkVersion);
	}
}
