package com.adjust.sdk;

public class Adjust2dxPurchaseVerificationResultCallback implements OnPurchaseVerificationFinishedListener {
	public native void verificationResult(String verificationResult, int code, String message);
	
	public Adjust2dxPurchaseVerificationResultCallback() {}
	
	@Override
	public void onVerificationFinished(AdjustPurchaseVerificationResult result) {
		verificationResult(result.getVerificationStatus(), result.getCode(), result.getMessage());
	}
}
