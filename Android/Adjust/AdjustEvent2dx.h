/*
 * AdjustEvent2dx.h
 *
 *  Created on: Jun 16, 2015
 *      Author: uerceg
 */

#ifndef ADJUST_ADJUSTEVENT2DX_H_
#define ADJUST_ADJUSTEVENT2DX_H_

#include <jni.h>
#include <iostream>

class AdjustEvent2dx {
private:
	jobject event;
	void initEvent(std::string eventToken);

public:
	AdjustEvent2dx(std::string eventToken) {
		initEvent(eventToken);
	}

	void addCallbackParameter(std::string key, std::string value);
	void addPartnerParameter(std::string key, std::string value);
	void setRevenue(double amount, std::string currency);
	void setTransactionId(std::string transactionId);
	bool isValid();
	void setReceipt(std::string receipt, std::string transactionId);
	jobject getEvent();
};

#endif /* ADJUST_ADJUSTEVENT2DX_H_ */
