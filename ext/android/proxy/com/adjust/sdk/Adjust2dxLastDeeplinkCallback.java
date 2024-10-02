package com.adjust.sdk;

import android.net.Uri;

public class Adjust2dxLastDeeplinkCallback implements OnLastDeeplinkReadListener {
	public native void lastDeeplinkRead(String deeplink);

	public Adjust2dxLastDeeplinkCallback() {}

	@Override
	public void onLastDeeplinkRead(Uri deeplink) {
		lastDeeplinkRead(deeplink != null ? deeplink.toString() : null);
	}
}
