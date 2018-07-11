//
//  Command.cpp
//  Adjust SDK
//
//  Created by Srdjan Tubin on 04/06/18.
//

#include "Command.h"

using json = nlohmann::json;

Command::Command(std::string className, std::string methodName, std::string parametersJson) {
    this->className = className;
    this->methodName = methodName;
    std::map<std::string, std::vector<std::string>> parsedParams = json::parse(parametersJson);
    this->parameters = parsedParams;
}

std::vector<std::string> Command::getParameters(std::string parameterKey) {
    std::vector<std::string> parameterValues = this->parameters[parameterKey];
    if (parameterValues.size() == 0) {
        return std::vector<std::string>();
    }
    return parameterValues;
}

std::string Command::getFirstParameterValue(std::string parameterKey) {
    std::vector<std::string> parameterValues = this->parameters[parameterKey];
    if (parameterValues.size() == 0) {
        return NULL;
    }
    return parameterValues[0];
}

bool Command::containsParameter(std::string parameterKey) {
    return this->parameters.count(parameterKey) > 0;
}