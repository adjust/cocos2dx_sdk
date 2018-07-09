#ifndef  _TESTAPP_COMMAND_H_
#define  _TESTAPP_COMMAND_H_

#include <vector>
#include <map>
#include <string>

#include "jsonParser/json.hpp"
using json = nlohmann::json;

class Command {
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