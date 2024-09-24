package com.adjust.sdk;

public class Adjust2dxSessionTrackingFailedCallback implements OnSessionTrackingFailedListener {
	public native void sessionTrackingFailed(Object sessionFailure);
	
	public Adjust2dxSessionTrackingFailedCallback() {}
	
	@Override
	public void onSessionTrackingFailed(AdjustSessionFailure failureResponseData) {
		sessionTrackingFailed(failureResponseData);
	}
}
