package com.adjust.sdk;

public class Adjust2dxSdkVersionCallback implements OnSdkVersionReadListener {
	public native void sdkVersionRead(String sdkVersion);
	public native void sdkVersionReadWithId(String sdkVersion, long callbackId);
	private String sdkPrefix;
	private long callbackId = 0;

	public Adjust2dxSdkVersionCallback(String sdkPrefix) {
		this.sdkPrefix = sdkPrefix;
	}

	public Adjust2dxSdkVersionCallback(String sdkPrefix, long callbackId) {
		this.sdkPrefix = sdkPrefix;
		this.callbackId = callbackId;
	}

	@Override
	public void onSdkVersionRead(String sdkVersion) {
		String version = sdkPrefix != null ? sdkPrefix + "@" + sdkVersion : sdkVersion;
		if (callbackId != 0) {
			sdkVersionReadWithId(version, callbackId);
		} else {
			sdkVersionRead(version);
		}
	}
}
