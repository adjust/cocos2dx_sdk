#include "Command.h"

#include "jsonParser/json.hpp"
using json = nlohmann::json;

Command::Command(std::string className, std::string methodName, std::string parametersJson) {
	this->className = className;
	this->methodName = methodName;
    this->parameters = json::parse(parametersJson);
}

std::vector<std::string> Command::getParameters(std::string parameterKey) {
	std::vector<std::string> parameterValues = this->parameters[parameterKey];
	if (parameterValues == NULL) {
        return NULL;
    }
    return parameterValues;
}

std::string Command::getFirstParameterValue(std::string parameterKey) {
    std::vector<std::string> parameterValues = this->parameters[parameterKey];
    if (parameterValues == NULL || parameterValues.size() == 0) {
        return NULL;
    }
    return parameterValues[0];
}

bool Command::containsParameter(std::string parameterKey) {
    return this->parameters.find(parameterKey) != this->parameters.end();
}