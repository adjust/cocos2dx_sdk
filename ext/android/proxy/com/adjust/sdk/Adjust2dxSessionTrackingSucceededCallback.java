package com.adjust.sdk;

public class Adjust2dxSessionTrackingSucceededCallback implements OnSessionTrackingSucceededListener {
	public native void sessionTrackingSucceeded(Object sessionSuccess);
	
	public Adjust2dxSessionTrackingSucceededCallback() {}
	
	@Override
	public void onSessionTrackingSucceeded(AdjustSessionSuccess sessionSuccessResponseData) {
		sessionTrackingSucceeded(sessionSuccessResponseData);
	}
}
