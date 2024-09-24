package com.adjust.sdk;

public class Adjust2dxEventTrackingFailedCallback implements OnEventTrackingFailedListener {
	public native void eventTrackingFailed(Object eventFailure);
	
	public Adjust2dxEventTrackingFailedCallback() {}
	
	@Override
	public void onEventTrackingFailed(AdjustEventFailure eventFailureResponseData) {
		eventTrackingFailed(eventFailureResponseData);
	}
}
