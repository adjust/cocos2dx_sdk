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
    echo -e "${CYAN}[ADJUST][BUILD-SDK-ANDROID]:${GREEN} Usage: ./build.sh [debug || release] [optional: --with-test-lib] ${NC}"
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
ANDROID_JAR=$ANDROID_HOME/platforms/android-23/android.jar
JAR=$JAVA_HOME_7/bin/jar
JAVAC=$JAVA_HOME_7/bin/javac

# ======================================== #

# Move to Adjust directory.
cd ${ROOT_DIR}/${BUILD_DIR}

# ======================================== #

# first run gradle clean
./gradlew clean

if [ "$BUILD_TYPE" == "debug" ]; then
	echo -e "${CYAN}[ADJUST][ANDROID][BUILD-SDK]:${GREEN} Running makeDebugJar Gradle task ... ${NC}"
    JAR_IN_DIR=adjust/build/intermediates/bundles/debug
    ./gradlew makeDebugJar
    echo -e "${CYAN}[ADJUST][ANDROID][BUILD-SDK]:${GREEN} Done! ${NC}"
elif [ "$BUILD_TYPE" == "release" ]; then
	echo -e "${CYAN}[ADJUST][ANDROID][BUILD-SDK]:${GREEN} Running makeReleaseJar Gradle task ... ${NC}"
    JAR_IN_DIR=adjust/build/intermediates/bundles/release
    ./gradlew makeReleaseJar
    echo -e "${CYAN}[ADJUST][ANDROID][BUILD-SDK]:${GREEN} Done! ${NC}"
fi

if [ $# -eq 2 ] && [ $2 == --with-test-lib ]; then
    echo -e "${CYAN}[ADJUST-TEST-LIB][ANDROID][BUILD-SDK]:${GREEN} Running makeJar Gradle task ... ${NC}"
    ./gradlew makeJar
    if [ "$BUILD_TYPE" == "debug" ]; then
        TESTLIB_JAR_IN_DIR=testlibrary/build/intermediates/bundles/debug
    else
        TESTLIB_JAR_IN_DIR=testlibrary/build/intermediates/bundles/release
    fi
    echo -e "${CYAN}[ADJUST-TEST-LIB][ANDROID][BUILD-SDK]:${GREEN} Done! ${NC}"
fi

# ======================================== #

echo -e "${CYAN}[ADJUST][ANDROID][BUILD-SDK]:${GREEN} Moving Android SDK JAR from ${JAR_IN_DIR} to ${PROXY_DIR} ... ${NC}"
mv -v ${JAR_IN_DIR}/*.jar ${ROOT_DIR}/${PROXY_DIR}/adjust-android.jar
if [ $# -eq 2 ] && [ $2 == --with-test-lib ]; then
    echo -e "${CYAN}[ADJUST][ANDROID-TEST-LIB][BUILD-SDK]:${GREEN} Moving Testing JAR from ${TESTLIB_JAR_IN_DIR} to ${PROXY_DIR} ... ${NC}"
    mv -v ${TESTLIB_JAR_IN_DIR}/*.jar ${ROOT_DIR}/${PROXY_DIR}/adjust-testing.jar
fi
echo -e "${CYAN}[ADJUST][ANDROID][BUILD-SDK]:${GREEN} Done! ${NC}"

# ======================================== #

echo -e "${CYAN}[ADJUST][ANDROID][BUILD-SDK]:${GREEN} Unpacking adjust-android.jar file ... ${NC}"
cd ${ROOT_DIR}/${PROXY_DIR}
$JAVAC -cp "adjust-android.jar:$ANDROID_JAR" com/adjust/sdk/*.java
if [ $# -eq 2 ] && [ $2 == --with-test-lib ]; then
    echo -e "${CYAN}[ADJUST][ANDROID-TEST-LIB][BUILD-SDK]:${GREEN} Unpacking adjust-testing.jar file ... ${NC}"
    $JAVAC -cp "adjust-testing.jar:$ANDROID_JAR" com/adjust/testlibrary/*.java
fi
echo -e "${CYAN}[ADJUST][ANDROID][BUILD-SDK]:${GREEN} Done! ${NC}"

# ======================================== #

echo -e "${CYAN}[ADJUST][ANDROID][BUILD-SDK]:${GREEN} Injecting C++ bridge Java classes to adjust-android.jar ... ${NC}"
cd ${ROOT_DIR}/${PROXY_DIR}
$JAR uf adjust-android.jar com/adjust/sdk/*.class
if [ $# -eq 2 ] && [ $2 == --with-test-lib ]; then
    echo -e "${CYAN}[ADJUST-TEST-LIB][ANDROID][BUILD-SDK]:${GREEN} Injecting C++ bridge Java classes to adjust-testing.jar ... ${NC}"
    $JAR uf adjust-testing.jar com/adjust/testlibrary/*.class
fi
echo -e "${CYAN}[ADJUST][ANDROID][BUILD-SDK]:${GREEN} Done! ${NC}"

# ======================================== #

echo -e "${CYAN}[ADJUST][ANDROID][BUILD-SDK]:${GREEN} Deleting .class files ... ${NC}"
cd ${ROOT_DIR}/${PROXY_DIR}
rm -rfv com/adjust/sdk/*.class
if [ $# -eq 2 ] && [ $2 == --with-test-lib ]; then
    rm -rfv com/adjust/testlibrary/*.class
fi
echo -e "${CYAN}[ADJUST][ANDROID][BUILD-SDK]:${GREEN} Done! ${NC}"

# ======================================== #

echo -e "${CYAN}[ADJUST][ANDROID][BUILD-SDK]:${GREEN} Copying resulting adjust-android.jar into ${ROOT_DIR}/${LIBS_OUT_DIR} ${NC}"
cd ${ROOT_DIR}/${PROXY_DIR}
cp -v adjust-android.jar ${ROOT_DIR}/${LIBS_OUT_DIR}
if [ $# -eq 2 ] && [ $2 == --with-test-lib ]; then
    echo -e "${CYAN}[ADJUST-TEST-LIB][ANDROID][BUILD-SDK]:${GREEN} Copying resulting adjust-testing.jar into ${ROOT_DIR}/${LIBS_OUT_DIR} ${NC}"
    cp -v adjust-testing.jar ${ROOT_DIR}/${LIBS_OUT_DIR}
fi
echo -e "${CYAN}[ADJUST][ANDROID][BUILD-SDK]:${GREEN} Done! ${NC}"

# ======================================== #

echo -e "${CYAN}[ADJUST][ANDROID][BUILD-SDK]:${GREEN} Script completed! ${NC}"