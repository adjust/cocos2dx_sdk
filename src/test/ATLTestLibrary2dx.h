//
//  ATLTestLibrary2dx.h
//  Adjust SDK
//
//  Created by Srdjan Tubin (@2beens) on 30th July 2018.
//  Copyright © 2018-2019 Adjust GmbH. All rights reserved.
//

#ifndef ADJUST_ATLTESTLIBRARY2DX_H_
#define ADJUST_ATLTESTLIBRARY2DX_H_

class ATLTestLibrary2dx {
private:
    void* testLibrary;

public:
    ATLTestLibrary2dx() {}
    ATLTestLibrary2dx(std::string baseUrl, std::string controlUrl, void(*executeCommandCallback)(std::string className, std::string methodName, std::string jsonParameters));

    void addTest(std::string testName);
    void addTestDirectory(std::string testDirectory);
    void startTestSession(std::string clientSdk);
    void addInfoToSend(std::string key, std::string value);
    void sendInfoToServer(std::string basePath);
};

#endif /* ADJUST_ATLTESTLIBRARY2DX_H_ */
