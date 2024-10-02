package com.adjust.sdk;

public class Adjust2dxResolvedLinkCallback implements OnDeeplinkResolvedListener {
	public native void deeplinkResolved(String resolvedLink);
	
	public Adjust2dxResolvedLinkCallback() {}
	
	@Override
	public void onDeeplinkResolved(String resolvedLink) {
		deeplinkResolved(resolvedLink);
	}
}
