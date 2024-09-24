package com.adjust.sdk;

public class Adjust2dxIsEnabledCallback implements OnIsEnabledListener {
	public native void isEnabledRead(boolean isEnabled);

	public Adjust2dxIsEnabledCallback() {}

	@Override
	public void onIsEnabledRead(boolean isEnabled) {
		isEnabledRead(isEnabled);
	}
}
