//
//  Command.h
//  Adjust SDK
//
//  Created by Srdjan Tubin on 04/06/18.
//

#include "Command.h"
#include <iterator>

using json = nlohmann::json;

#define COCOS2D_DEBUG 1
#include <platform/CCStdC.h>
#include <base/CCConsole.h>

Command::Command(std::string className, std::string methodName, std::string parametersJson) {
    this->className = className;
    this->methodName = methodName;

    // reason for changing [null] to []
    // https://github.com/nlohmann/json/issues/1163
    replaceSubString(parametersJson, "[null]", "[\"\"]");
    std::map<std::string, std::vector<std::string>> parsedParams = json::parse(parametersJson);

    this->parameters = parsedParams;
}

bool Command::replaceSubString(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
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