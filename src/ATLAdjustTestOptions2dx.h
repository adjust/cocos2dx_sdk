//
//  ATLAdjustTestOptions2dx.h
//  Adjust SDK
//
//  Created by Srdjan Tubin (@2beens) on 30th July 2018.
//  Copyright © 2018 Adjust GmbH. All rights reserved.
//

#ifndef _ADJUST_ATLADJUSTTESTOPTIONS2X_H_
#define _ADJUST_ATLADJUSTTESTOPTIONS2X_H_

#include <iostream>

class ATLAdjustTestOptions2dx {
private:
    void* testOptions;

public:
	ATLAdjustTestOptions2dx();

	void setBaseUrl(std::string baseUrl);
	void setGdprUrl(std::string gdprUrl);
	void setBasePath(std::string basePath);
	void setGdprPath(std::string gdprPath);
	void setTimerIntervalInMilliseconds(long timerIntervalInMilliseconds);
	void setTimerStartInMilliseconds(long timerStartInMilliseconds);
	void setSessionIntervalInMilliseconds(long sessionIntervalInMilliseconds);
	void setSubsessionIntervalInMilliseconds(long subsessionIntervalInMilliseconds);
	void setTeardown(bool teardown);
	void setDeleteState(bool deleteState);
	void setNoBackoffWait(bool noBackoffWait);
	void setIAdFrameworkEnabled(bool iAdFrameworkEnabled);

    void* getTestOptions();
};

#endif /* _ADJUST_ATLADJUSTTESTOPTIONS2X_H_ */
