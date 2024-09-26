//
//  Command.h
//  Adjust SDK
//
//  Created by Srdjan Tubin (@2beens) on 4th June 2018.
//  Copyright © 2018-Present Adjust GmbH. All rights reserved.
//

#ifndef  _TESTAPP_COMMAND_H_
#define  _TESTAPP_COMMAND_H_

#include <map>
#include <string>
#include <vector>
#include "json/json.hpp"

class Command {
private:
	void replace(std::string &s, const std::string &search, const std::string &replace);
public:
	std::string className;
	std::string methodName;
	std::map<std::string, std::vector<std::string>> parameters;

	Command(std::string className, std::string methodName, std::string parametersJson);

	std::vector<std::string> getParameters(std::string parameterKey);
	std::string getFirstParameterValue(std::string parameterKey);
	bool containsParameter(std::string parameterKey);
};

#endif // _TESTAPP_COMMAND_H_