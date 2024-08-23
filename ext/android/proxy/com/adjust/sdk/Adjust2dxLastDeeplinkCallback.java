package com.adjust.sdk;

public class Adjust2dxLastDeeplinkCallback implements OnLastDeeplinkReadListener {
	public native void lastDeeplinkRead(String deeplink);

	public Adjust2dxLastDeeplinkCallback() {}

	@Override
	public void onLastDeeplinkRead(Uri deeplink) {
		lastDeeplinkRead(deeplink != null ? deeplink.toString() : null);
	}
}
