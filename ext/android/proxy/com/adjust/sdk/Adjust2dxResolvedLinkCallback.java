package com.adjust.sdk;

public class Adjust2dxResolvedLinkCallback implements OnDeeplinkResolvedListener {
	public native void deeplinkResolved(String resolvedLink);
	public native void deeplinkResolvedWithId(String resolvedLink, long callbackId);

	private long callbackId = 0;

	public Adjust2dxResolvedLinkCallback() {}

	public Adjust2dxResolvedLinkCallback(long callbackId) {
		this.callbackId = callbackId;
	}

	@Override
	public void onDeeplinkResolved(String resolvedLink) {
		if (callbackId != 0) {
			deeplinkResolvedWithId(resolvedLink, callbackId);
		} else {
			deeplinkResolved(resolvedLink);
		}
	}
}
