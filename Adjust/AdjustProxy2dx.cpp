//
//  AdjustProxy2dx.cpp
//  Adjust SDK
//
//  Created by Uglješa Erceg on 03/09/15.
//

#include "AdjustProxy2dx.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
JNIEXPORT void JNICALL Java_com_adjust_sdk_Adjust2dxAttributionCallback_attributionChanged
(JNIEnv *env, jobject obj, jobject attributionObject) {
	if (callbackToTrigger != NULL) {
		std::string trackerToken;
		std::string trackerName;
		std::string network;
		std::string campaign;
		std::string adgroup;
		std::string creative;
		std::string clickLabel;

		jclass clsAdjustAttribution = env->FindClass("com/adjust/sdk/AdjustAttribution");

		jfieldID fTrackerTokenID = env->GetFieldID(clsAdjustAttribution, "trackerToken", "Ljava/lang/String;");
		jfieldID fTrackerNameID = env->GetFieldID(clsAdjustAttribution, "trackerName", "Ljava/lang/String;");
		jfieldID fNetworkID = env->GetFieldID(clsAdjustAttribution, "network", "Ljava/lang/String;");
		jfieldID fCampaignID = env->GetFieldID(clsAdjustAttribution, "campaign", "Ljava/lang/String;");
		jfieldID fAdgroupID = env->GetFieldID(clsAdjustAttribution, "adgroup", "Ljava/lang/String;");
		jfieldID fCreativeID = env->GetFieldID(clsAdjustAttribution, "creative", "Ljava/lang/String;");
		jfieldID fClickLabelID = env->GetFieldID(clsAdjustAttribution, "clickLabel", "Ljava/lang/String;");

		jstring jTrackerToken = (jstring)env->GetObjectField(attributionObject, fTrackerTokenID);
		jstring jTrackerName = (jstring)env->GetObjectField(attributionObject, fTrackerNameID);
		jstring jNetwork = (jstring)env->GetObjectField(attributionObject, fNetworkID);
		jstring jCampaign = (jstring)env->GetObjectField(attributionObject, fCampaignID);
		jstring jAdgroup = (jstring)env->GetObjectField(attributionObject, fAdgroupID);
		jstring jCreative = (jstring)env->GetObjectField(attributionObject, fCreativeID);
		jstring jClickLabel = (jstring)env->GetObjectField(attributionObject, fClickLabelID);

		if (jTrackerToken != NULL) {
			const char *trackerTokenCStr = env->GetStringUTFChars(jTrackerToken, NULL);
			trackerToken = std::string(trackerTokenCStr);
			env->ReleaseStringUTFChars(jTrackerToken, trackerTokenCStr);
			env->DeleteLocalRef(jTrackerToken);
		}

		if (jTrackerName != NULL) {
			const char *trackerNameCStr = env->GetStringUTFChars(jTrackerName, NULL);
			trackerName = std::string(trackerNameCStr);
			env->ReleaseStringUTFChars(jTrackerName, trackerNameCStr);
			env->DeleteLocalRef(jTrackerName);
		}

		if (jNetwork != NULL) {
			const char *networkCStr = env->GetStringUTFChars(jNetwork, NULL);
			network = std::string(networkCStr);
			env->ReleaseStringUTFChars(jNetwork, networkCStr);
			env->DeleteLocalRef(jNetwork);
		}

		if (jCampaign != NULL) {
			const char *campaignCStr = env->GetStringUTFChars(jCampaign, NULL);
			campaign = std::string(campaignCStr);
			env->ReleaseStringUTFChars(jCampaign, campaignCStr);
			env->DeleteLocalRef(jCampaign);
		}

		if (jAdgroup != NULL) {
			const char *adgroupCStr = env->GetStringUTFChars(jAdgroup, NULL);
			adgroup = std::string(adgroupCStr);
			env->ReleaseStringUTFChars(jAdgroup, adgroupCStr);
			env->DeleteLocalRef(jAdgroup);
		}

		if (jCreative != NULL) {
			const char *creativeCStr = env->GetStringUTFChars(jCreative, NULL);
			creative = std::string(creativeCStr);
			env->ReleaseStringUTFChars(jCreative, creativeCStr);
			env->DeleteLocalRef(jCreative);
		}

		if (jClickLabel != NULL) {
			const char *clickLabelCStr = env->GetStringUTFChars(jClickLabel, NULL);
			clickLabel = std::string(clickLabelCStr);
			env->ReleaseStringUTFChars(jClickLabel, clickLabelCStr);
			env->DeleteLocalRef(jClickLabel);
		}

		AdjustAttribution2dx attribution = AdjustAttribution2dx(trackerToken, trackerName, network,
				campaign, adgroup, creative, clickLabel);
		callbackToTrigger(attribution);
	}
}

void setAttributionCallbackMethod(void (*callbackMethod)(AdjustAttribution2dx attribution)) {
	if (callbackToTrigger == NULL) {
		callbackToTrigger = callbackMethod;
	}
}

#endif
