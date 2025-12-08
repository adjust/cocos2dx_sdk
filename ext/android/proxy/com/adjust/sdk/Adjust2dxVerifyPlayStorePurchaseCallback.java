package com.adjust.sdk;

public class Adjust2dxVerifyPlayStorePurchaseCallback implements OnPurchaseVerificationFinishedListener {
	public native void verificationResult(String verificationResult, int code, String message);
	public native void verificationResultWithId(String verificationResult, int code, String message, long callbackId);
	
	private long callbackId = 0;
	
	public Adjust2dxVerifyPlayStorePurchaseCallback() {}
	
	public Adjust2dxVerifyPlayStorePurchaseCallback(long callbackId) {
		this.callbackId = callbackId;
	}
	
	@Override
	public void onVerificationFinished(AdjustPurchaseVerificationResult result) {
		if (callbackId != 0) {
			verificationResultWithId(result.getVerificationStatus(), result.getCode(), result.getMessage(), callbackId);
		} else {
			verificationResult(result.getVerificationStatus(), result.getCode(), result.getMessage());
		}
	}
}
