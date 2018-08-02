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
if [ $# -ne 2 ] ; then
    echo -e "${CYAN}[ADJUST][ANDROID][APP]:${GREEN} Usage: ./app-android.sh [example || test] [path-to-app] ${NC}"
    exit 1
fi

BUILD_TYPE=$1
APP_PATH=$2

# ======================================== #

# Directories and paths of interest for the script.
SCRIPTS_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
ROOT_DIR="$(dirname "$SCRIPTS_DIR")"
LIBS_DIR=libs/android/
TEST_LIBS_DIR=test/android/libs

# ======================================== #

if [ "$BUILD_TYPE" == "example" ]; then
	echo -e "${CYAN}[ADJUST][ANDROID][APP]:${GREEN} Removing example app from test device/emulator ... ${NC}"
	adb uninstall com.adjust.examples || true
	echo -e "${CYAN}[ADJUST][ANDROID][APP]:${GREEN} Done! ${NC}"
elif [ "$BUILD_TYPE" == "test" ]; then
	echo -e "${CYAN}[ADJUST][ANDROID][APP]:${GREEN} Removing test app from test device/emulator ... ${NC}"
	adb uninstall com.adjust.testapp || true
	echo -e "${CYAN}[ADJUST][ANDROID][APP]:${GREEN} Done! ${NC}"
fi

# ======================================== #

if [ "$BUILD_TYPE" == "example" ]; then
	echo -e "${CYAN}[ADJUST][ANDROID][APP]:${GREEN} Building Adjust SDK JAR file ... ${NC}"
	${ROOT_DIR}/ext/android/build.sh release
	echo -e "${CYAN}[ADJUST][ANDROID][APP]:${GREEN} Done! ${NC}"
elif [ "$BUILD_TYPE" == "test" ]; then
	echo -e "${CYAN}[ADJUST][ANDROID][APP]:${GREEN} Building Adjust SDK and test library JAR file ... ${NC}"
	${ROOT_DIR}/ext/android/build.sh release --with-test-lib
	echo -e "${CYAN}[ADJUST][ANDROID][APP]:${GREEN} Done! ${NC}"
fi

# ======================================== #

if [ "$BUILD_TYPE" == "example" ]; then
	echo -e "${CYAN}[ADJUST][ANDROID][APP]:${GREEN} Copying Adjust SDK JAR to Cocos2d-x example app at ${APP_PATH} ... ${NC}"
	cd ${ROOT_DIR}/${LIBS_DIR}
	mkdir -p ${APP_PATH}/proj.android/app/libs || true
	cp -v adjust-android.jar ${APP_PATH}/proj.android/app/libs/
	echo -e "${CYAN}[ADJUST][ANDROID][APP]:${GREEN} Done! ${NC}"
elif [ "$BUILD_TYPE" == "test" ]; then
	echo -e "${CYAN}[ADJUST][ANDROID][APP]:${GREEN} Copying Adjust SDK and test JAR files to Cocos2d-x test app at ${APP_PATH} ... ${NC}"
	cd ${ROOT_DIR}/${LIBS_DIR}
	mkdir -p ${APP_PATH}/proj.android/app/libs || true
	cp -v adjust-android.jar ${APP_PATH}/proj.android/app/libs/
	cd ${ROOT_DIR}/${TEST_LIBS_DIR}
	cp -v adjust-testing.jar ${APP_PATH}/proj.android/app/libs/
	cp -v gson-2.8.1.jar ${APP_PATH}/proj.android/app/libs/
	echo -e "${CYAN}[ADJUST][ANDROID][APP]:${GREEN} Done! ${NC}"
fi

# ======================================== #

if [ "$BUILD_TYPE" == "example" ]; then
	echo -e "${CYAN}[ADJUST][ANDROID][APP]:${GREEN} Updating Adjust SDK C++ source files in ${APP_PATH}/Classes/Adjust folder ... ${NC}"
	cd $APP_PATH
	rm -rfv Classes/Adjust/
	mkdir -p Classes/Adjust/
	cd ${ROOT_DIR}
	cp -Rfv src/* dist/
	cd dist
	rm -rf test
	cd ${ROOT_DIR}
	cp -Rfv dist/* ${APP_PATH}/Classes/Adjust/
	echo -e "${CYAN}[ADJUST][ANDROID][APP]:${GREEN} Success. Build & run with Android Studio from \`proj.android\` directory. Make sure Android.mk file is modified in accordance with README instructions. ${NC}"
	echo -e "${CYAN}[ADJUST][ANDROID][APP]:${GREEN} Done! ${NC}"
elif [ "$BUILD_TYPE" == "test" ]; then
	echo -e "${CYAN}[ADJUST][ANDROID][APP]:${GREEN} Updating Adjust SDK C++ source files in ${APP_PATH}/Classes/Adjust folder ... ${NC}"
	cd $APP_PATH
	rm -rfv Classes/Adjust/
	mkdir -p Classes/Adjust/
	cd ${ROOT_DIR}
	cp -Rfv src/* dist/
	cd dist
	rm -rf test
	cd ${ROOT_DIR}
	cp -Rfv src/* ${APP_PATH}/Classes/Adjust/ # this is the diff
	echo -e "${CYAN}[ADJUST][ANDROID][APP]:${GREEN} Success. Build & run with Android Studio from \`proj.android\` directory. Make sure Android.mk file is modified in accordance with README instructions. ${NC}"
	echo -e "${CYAN}[ADJUST][ANDROID][APP]:${GREEN} Done! ${NC}"
fi

# ======================================== #

echo -e "${CYAN}[ADJUST][ANDROID][APP]:${GREEN} Script completed! ${NC}"
