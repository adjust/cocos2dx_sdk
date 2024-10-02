package com.adjust.sdk;

public class Adjust2dxEventTrackingSucceededCallback implements OnEventTrackingSucceededListener {
	public native void eventTrackingSucceeded(Object eventSuccess);
	
	public Adjust2dxEventTrackingSucceededCallback() {}
	
	@Override
	public void onEventTrackingSucceeded(AdjustEventSuccess eventSuccessResponseData) {
		eventTrackingSucceeded(eventSuccessResponseData);
	}
}
