#!/usr/bin/env bash

set -e

# Colors for output

NC='\033[0m'
RED='\033[0;31m'
CYAN='\033[1;36m'
GREEN='\033[0;32m'

# ======================================== #

ANDROID_JAR=$ANDROID_HOME/platforms/android-23/android.jar
JAR=$JAVA_HOME_7/bin/jar
JAVAC=$JAVA_HOME_7/bin/javac

# ======================================== #

echo -e "${CYAN}* [ADJUST-SDK-BUILD][CPP-BRIDGE]:${GREEN} Unpacking adjust-android.jar file ... ${NC}"
$JAVAC -cp "adjust-android.jar:$ANDROID_JAR" com/adjust/sdk/*.java
echo -e "${CYAN}* [ADJUST-SDK-BUILD][CPP-BRIDGE]:${GREEN} Done! ${NC}"

# ======================================== #

if [ $# -eq 1 ] && [ $1 == --with-test-lib ]; then
    echo -e "${CYAN}* [ADJUST-SDK-BUILD][CPP-BRIDGE]:${GREEN} Unpacking adjust-testing.jar file ... ${NC}"
    $JAVAC -cp "adjust-testing.jar:$ANDROID_JAR" com/adjust/testlibrary/*.java
    echo -e "${CYAN}* [ADJUST-SDK-BUILD][CPP-BRIDGE]:${GREEN} Done! ${NC}"
fi

# ======================================== #

echo -e "${CYAN}* [ADJUST-SDK-BUILD][CPP-BRIDGE]:${GREEN} Injecting C++ bridge Java classes to adjust-android.jar ... ${NC}"
$JAR uf adjust-android.jar com/adjust/sdk/*.class
echo -e "${CYAN}* [ADJUST-SDK-BUILD][CPP-BRIDGE]:${GREEN} Done! ${NC}"

# ======================================== #

if [ $# -eq 1 ] && [ $1 == --with-test-lib ]; then
    echo -e "${CYAN}* [ADJUST-SDK-BUILD][CPP-BRIDGE]:${GREEN} Injecting C++ bridge Java classes to adjust-testing.jar ... ${NC}"
    $JAR uf adjust-testing.jar com/adjust/testlibrary/*.class
    echo -e "${CYAN}* [ADJUST-SDK-BUILD][CPP-BRIDGE]:${GREEN} Done! ${NC}"
fi