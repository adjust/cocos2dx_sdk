package com.adjust.sdk;

public class Adjust2dxSdkVersionCallback implements OnSdkVersionReadListener {
	public native void sdkVersionRead(String sdkVersion);

	private String sdkPrefix;

	public Adjust2dxSdkVersionCallback(String sdkPrefix) {
		this.sdkPrefix = sdkPrefix;
	}

	@Override
	public void onSdkVersionRead(String sdkVersion) {
		if (sdkPrefix != null) {
			sdkVersionRead(sdkPrefix + "@" + sdkVersion);
		} else {
			sdkVersionRead("");
		}
	}
}
