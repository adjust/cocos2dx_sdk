package com.adjust.sdk;

import android.net.Uri;

public class Adjust2dxLastDeeplinkCallback implements OnLastDeeplinkReadListener {
	public native void lastDeeplinkRead(String deeplink);
	public native void lastDeeplinkReadWithId(String deeplink, long callbackId);

	private long callbackId = 0;

	public Adjust2dxLastDeeplinkCallback() {}

	public Adjust2dxLastDeeplinkCallback(long callbackId) {
		this.callbackId = callbackId;
	}

	@Override
	public void onLastDeeplinkRead(Uri deeplink) {
		String deeplinkStr = deeplink != null ? deeplink.toString() : null;
		if (callbackId != 0) {
			lastDeeplinkReadWithId(deeplinkStr, callbackId);
		} else {
			lastDeeplinkRead(deeplinkStr);
		}
	}
}
