#!/usr/bin/env bash

set -e

# ======================================== #

# Colors for output
NC='\033[0m'
RED='\033[0;31m'
CYAN='\033[1;36m'
GREEN='\033[0;32m'

# ======================================== #

# Usage hint in case of wrong invocation.
if [ $# -ne 1 ] && [ $# -ne 2 ]; then
    echo -e "${CYAN}[ADJUST][ANDROID][BUILD]:${GREEN} Usage: ./build.sh [debug || release] [optional: --with-test-lib] ${NC}"
    exit 1
fi

BUILD_TYPE=$1

# ======================================== #

# Directories and paths of interest for the script.
ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
ROOT_DIR="$(dirname "$ROOT_DIR")"
ROOT_DIR="$(dirname "$ROOT_DIR")"
BUILD_DIR=ext/android/sdk/Adjust
PROXY_DIR=ext/android/proxy
LIBS_OUT_DIR=libs/android
TEST_LIBS_OUT_DIR=test/libs/android/
ANDROID_JAR=$ANDROID_HOME/platforms/android-23/android.jar
JAR=$JAVA_HOME_7/bin/jar
JAVAC=$JAVA_HOME_7/bin/javac

# ======================================== #

# Move to Adjust directory.
cd ${ROOT_DIR}/${BUILD_DIR}

# ======================================== #

echo -e "${CYAN}[ADJUST][ANDROID][BUILD]:${GREEN} Running clean and makeDebugJar Gradle tasks for Adjust SDK project ... ${NC}"
if [ "$BUILD_TYPE" == "debug" ]; then
    JAR_IN_DIR=adjust/build/intermediates/bundles/debug
    ./gradlew clean makeDebugJar
    echo -e "${CYAN}[ADJUST][ANDROID][BUILD]:${GREEN} Done! ${NC}"
elif [ "$BUILD_TYPE" == "release" ]; then
    JAR_IN_DIR=adjust/build/intermediates/bundles/release
    ./gradlew clean makeReleaseJar
    echo -e "${CYAN}[ADJUST][ANDROID][BUILD]:${GREEN} Done! ${NC}"
fi

# ======================================== #

echo -e "${CYAN}[ADJUST][ANDROID][BUILD]:${GREEN} Copying Android SDK JAR from ${JAR_IN_DIR} to ${PROXY_DIR} ... ${NC}"
cp -v ${JAR_IN_DIR}/*.jar ${ROOT_DIR}/${PROXY_DIR}/adjust-android.jar
echo -e "${CYAN}[ADJUST][ANDROID][BUILD]:${GREEN} Done! ${NC}"

# ======================================== #

if [ $# -eq 2 ] && [ $2 == --with-test-lib ]; then
    echo -e "${CYAN}[ADJUST][ANDROID][BUILD]:${GREEN} Running clean and makeJar Gradle tasks for Adjust test library project ... ${NC}"
    ./gradlew clean makeJar
    if [ "$BUILD_TYPE" == "debug" ]; then
        TESTLIB_JAR_IN_DIR=testlibrary/build/intermediates/bundles/debug
    else
        TESTLIB_JAR_IN_DIR=testlibrary/build/intermediates/bundles/release
    fi
    echo -e "${CYAN}[ADJUST][ANDROID][BUILD]:${GREEN} Done! ${NC}"

    # ======================================== #

    echo -e "${CYAN}[ADJUST][ANDROID][BUILD]:${GREEN} Copying Testing JAR from ${TESTLIB_JAR_IN_DIR} to ${PROXY_DIR} ... ${NC}"
    cp -v ${TESTLIB_JAR_IN_DIR}/*.jar ${ROOT_DIR}/${PROXY_DIR}/adjust-testing.jar
    echo -e "${CYAN}[ADJUST][ANDROID][BUILD]:${GREEN} Done! ${NC}"
fi

# ======================================== #

echo -e "${CYAN}[ADJUST][ANDROID][BUILD]:${GREEN} Unpacking adjust-android.jar file ... ${NC}"
cd ${ROOT_DIR}/${PROXY_DIR}
$JAVAC -cp "adjust-android.jar:$ANDROID_JAR" com/adjust/sdk/*.java
echo -e "${CYAN}[ADJUST][ANDROID][BUILD]:${GREEN} Done! ${NC}"

# ======================================== #

if [ $# -eq 2 ] && [ $2 == --with-test-lib ]; then
    echo -e "${CYAN}[ADJUST][ANDROID][BUILD]:${GREEN} Unpacking adjust-testing.jar file ... ${NC}"
    $JAVAC -cp "adjust-testing.jar:$ANDROID_JAR" com/adjust/testlibrary/*.java
    echo -e "${CYAN}[ADJUST][ANDROID][BUILD]:${GREEN} Done! ${NC}"
fi

# ======================================== #

echo -e "${CYAN}[ADJUST][ANDROID][BUILD]:${GREEN} Injecting C++ bridge Java classes to adjust-android.jar ... ${NC}"
cd ${ROOT_DIR}/${PROXY_DIR}
$JAR uf adjust-android.jar com/adjust/sdk/*.class
echo -e "${CYAN}[ADJUST][ANDROID][BUILD]:${GREEN} Done! ${NC}"

# ======================================== #

if [ $# -eq 2 ] && [ $2 == --with-test-lib ]; then
    echo -e "${CYAN}[ADJUST][ANDROID][BUILD]:${GREEN} Injecting C++ bridge Java classes to adjust-testing.jar ... ${NC}"
    $JAR uf adjust-testing.jar com/adjust/testlibrary/*.class
    echo -e "${CYAN}[ADJUST][ANDROID][BUILD]:${GREEN} Done! ${NC}"
fi

# ======================================== #

echo -e "${CYAN}[ADJUST][ANDROID][BUILD]:${GREEN} Deleting .class files ... ${NC}"
cd ${ROOT_DIR}/${PROXY_DIR}
rm -rfv com/adjust/sdk/*.class
if [ $# -eq 2 ] && [ $2 == --with-test-lib ]; then
    rm -rfv com/adjust/testlibrary/*.class
fi
echo -e "${CYAN}[ADJUST][ANDROID][BUILD]:${GREEN} Done! ${NC}"

# ======================================== #

echo -e "${CYAN}[ADJUST][ANDROID][BUILD]:${GREEN} Copying resulting adjust-android.jar into ${ROOT_DIR}/${LIBS_OUT_DIR} ${NC}"
cd ${ROOT_DIR}/${PROXY_DIR}
cp -v adjust-android.jar ${ROOT_DIR}/${LIBS_OUT_DIR}
echo -e "${CYAN}[ADJUST][ANDROID][BUILD]:${GREEN} Done! ${NC}"

# ======================================== #

if [ $# -eq 2 ] && [ $2 == --with-test-lib ]; then
    echo -e "${CYAN}[ADJUST][ANDROID][BUILD]:${GREEN} Copying resulting adjust-testing.jar into ${ROOT_DIR}/${TEST_LIBS_OUT_DIR} ${NC}"
    cp -v adjust-testing.jar ${ROOT_DIR}/${TEST_LIBS_OUT_DIR}
    echo -e "${CYAN}[ADJUST][ANDROID][BUILD]:${GREEN} Done! ${NC}"
fi

# ======================================== #

echo -e "${CYAN}[ADJUST][ANDROID][BUILD]:${GREEN} Script completed! ${NC}"