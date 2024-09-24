package com.adjust.sdk;

import android.net.Uri;

public class Adjust2dxDeferredDeeplinkCallback implements OnDeferredDeeplinkResponseListener {
	public native boolean deferredDeeplinkReceived(String deeplink);
	
	public Adjust2dxDeferredDeeplinkCallback() {}
	
	@Override
	public boolean launchReceivedDeeplink(Uri deeplink) {
		return deferredDeeplinkReceived(deeplink.toString());
	}
}
