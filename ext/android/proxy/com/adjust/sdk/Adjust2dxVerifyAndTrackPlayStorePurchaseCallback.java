package com.adjust.sdk;

public class Adjust2dxVerifyAndTrackPlayStorePurchaseCallback implements OnPurchaseVerificationFinishedListener {
	public native void verificationResult(String verificationResult, int code, String message);

	public Adjust2dxVerifyAndTrackPlayStorePurchaseCallback() {}

	@Override
	public void onVerificationFinished(AdjustPurchaseVerificationResult result) {
		verificationResult(result.getVerificationStatus(), result.getCode(), result.getMessage());
	}
}
