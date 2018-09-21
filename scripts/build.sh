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
if [ $# -ne 5 ] ; then
    echo -e "${CYAN}[ADJUST][BUILD]:${GREEN} Usage: ./build.sh [ios || android] [example || test] [debug || release] [private || public] [path] ${NC}"
    exit 1
fi

PLATFORM=$1
APP_TYPE=$2
BUILD_TYPE=$3
REPO_TYPE=$4
APP_PATH=$5

# ======================================== #

# Directories and paths of interest for the script.
SCRIPTS_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
ROOT_DIR="$(dirname "$SCRIPTS_DIR")"
AND_DIR_LIBS=libs/android/
AND_DIR_LIBS_TEST=test/libs/android
if [ "$REPO_TYPE" == "public" ]; then
    REPO_TYPE_UC="PUBLIC"
elif [ "$REPO_TYPE" == "private" ]; then
    REPO_TYPE_UC="PRIVATE"
fi
if [ "$BUILD_TYPE" == "debug" ]; then
    BUILD_TYPE_UC="DEBUG"
elif [ "$BUILD_TYPE" == "release" ]; then
    REPO_TYPE_UC="RELEASE"
fi

# ======================================== #

if [ "$PLATFORM" == "android" ]; then
	if [ "$APP_TYPE" == "example" ]; then
		echo -e "${CYAN}[ADJUST][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Removing example app from test device/emulator ... ${NC}"
		adb uninstall com.adjust.examples || true
		echo -e "${CYAN}[ADJUST][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Done! ${NC}"
	elif [ "$APP_TYPE" == "test" ]; then
		echo -e "${CYAN}[ADJUST][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Removing test app from test device/emulator ... ${NC}"
		adb uninstall com.adjust.testapp || true
		echo -e "${CYAN}[ADJUST][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Done! ${NC}"
	fi
fi

# ======================================== #

if [ "$PLATFORM" == "android" ]; then
	if [ "$APP_TYPE" == "example" ]; then
		echo -e "${CYAN}[ADJUST][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Building Adjust SDK JAR file ... ${NC}"
		if [ "$BUILD_TYPE" == "debug" ]; then
			if [ "$REPO_TYPE" == "private" ]; then
				${ROOT_DIR}/ext/android/build.sh debug private
			elif [ "$REPO_TYPE" == "public" ]; then
				${ROOT_DIR}/ext/android/build.sh debug public
			fi
		elif [ "$BUILD_TYPE" == "release" ]; then
			if [ "$REPO_TYPE" == "private" ]; then
				${ROOT_DIR}/ext/android/build.sh release private
			elif [ "$REPO_TYPE" == "public" ]; then
				${ROOT_DIR}/ext/android/build.sh release public
			fi
		fi
		echo -e "${CYAN}[ADJUST][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Done! ${NC}"
	elif [ "$APP_TYPE" == "test" ]; then
		echo -e "${CYAN}[ADJUST][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Building Adjust SDK and test library JAR file ... ${NC}"
		if [ "$BUILD_TYPE" == "debug" ]; then
			if [ "$REPO_TYPE" == "private" ]; then
				${ROOT_DIR}/ext/android/build.sh debug private --with-test-lib
			elif [ "$REPO_TYPE" == "public" ]; then
				${ROOT_DIR}/ext/android/build.sh debug public --with-test-lib
			fi
		elif [ "$BUILD_TYPE" == "release" ]; then
			if [ "$REPO_TYPE" == "private" ]; then
				${ROOT_DIR}/ext/android/build.sh release private --with-test-lib
			elif [ "$REPO_TYPE" == "public" ]; then
				${ROOT_DIR}/ext/android/build.sh release public --with-test-lib
			fi
		fi
		echo -e "${CYAN}[ADJUST][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Done! ${NC}"
	fi



elif [ "$PLATFORM" == "ios" ]; then
	if [ "$APP_TYPE" == "example" ]; then
		echo -e "${CYAN}[ADJUST][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Building AdjustSdk.framework file ... ${NC}"
		if [ "$BUILD_TYPE" == "debug" ]; then
			if [ "$REPO_TYPE" == "private" ]; then
				${ROOT_DIR}/ext/ios/build.sh debug private
			elif [ "$REPO_TYPE" == "public" ]; then
				${ROOT_DIR}/ext/ios/build.sh debug public
			fi
		elif [ "$BUILD_TYPE" == "release" ]; then
			if [ "$REPO_TYPE" == "private" ]; then
				${ROOT_DIR}/ext/ios/build.sh release private
			elif [ "$REPO_TYPE" == "public" ]; then
				${ROOT_DIR}/ext/ios/build.sh release public
			fi
		fi
		echo -e "${CYAN}[ADJUST][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Done! ${NC}"
	elif [ "$APP_TYPE" == "test" ]; then
		echo -e "${CYAN}[ADJUST][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Building AdjustSdk.framework and AdjustTestLibrary.framework files ... ${NC}"
		if [ "$BUILD_TYPE" == "debug" ]; then
			if [ "$REPO_TYPE" == "private" ]; then
				${ROOT_DIR}/ext/ios/build.sh debug private --with-test-lib
			elif [ "$REPO_TYPE" == "public" ]; then
				${ROOT_DIR}/ext/ios/build.sh debug public --with-test-lib
			fi
		elif [ "$BUILD_TYPE" == "release" ]; then
			if [ "$REPO_TYPE" == "private" ]; then
				${ROOT_DIR}/ext/ios/build.sh release private --with-test-lib
			elif [ "$REPO_TYPE" == "public" ]; then
				${ROOT_DIR}/ext/ios/build.sh release public --with-test-lib
			fi
		fi
		echo -e "${CYAN}[ADJUST][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Done! ${NC}"
	fi
fi

# ======================================== #

if [ "$PLATFORM" == "android" ]; then
	if [ "$APP_TYPE" == "example" ]; then
		echo -e "${CYAN}[ADJUST][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Copying Adjust SDK JAR to Cocos2d-x example app at ${APP_PATH} ... ${NC}"
		cd ${ROOT_DIR}/${AND_DIR_LIBS}
		mkdir -p ${APP_PATH}/proj.android/app/libs || true
		cp -v adjust-android.jar ${APP_PATH}/proj.android/app/libs/
		echo -e "${CYAN}[ADJUST][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Done! ${NC}"
	elif [ "$APP_TYPE" == "test" ]; then
		echo -e "${CYAN}[ADJUST][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Copying Adjust SDK and test JAR files to Cocos2d-x test app at ${APP_PATH} ... ${NC}"
		cd ${ROOT_DIR}/${AND_DIR_LIBS}
		mkdir -p ${APP_PATH}/proj.android/app/libs || true
		cp -v adjust-android.jar ${APP_PATH}/proj.android/app/libs/
		cd ${ROOT_DIR}/${AND_DIR_LIBS_TEST}
		cp -v adjust-testing.jar ${APP_PATH}/proj.android/app/libs/
		cp -v gson-2.8.1.jar ${APP_PATH}/proj.android/app/libs/
		echo -e "${CYAN}[ADJUST][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Done! ${NC}"
	fi
elif [ "$PLATFORM" == "ios" ]; then
	if [ "$APP_TYPE" == "example" ]; then
		echo -e "${CYAN}[ADJUST][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Copying new AdjustSdk.framework to example app ... ${NC}"
		rm -rfv ${APP_PATH}/proj.ios_mac/ios/AdjustSdk.framework
		cp -Rv ${ROOT_DIR}/libs/ios/AdjustSdk.framework ${APP_PATH}/proj.ios_mac/ios
		echo -e "${CYAN}[ADJUST][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Done! ${NC}"
	elif [ "$APP_TYPE" == "test" ]; then
		echo -e "${CYAN}[ADJUST][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Copying new AdjustSdk.framework & AdjustTestLibrary.framework to test app ... ${NC}"
		rm -rfv ${APP_PATH}/proj.ios_mac/ios/AdjustSdk.framework
		rm -rfv ${APP_PATH}/proj.ios_mac/ios/AdjustTestLibrary.framework
		cp -Rv ${ROOT_DIR}/libs/ios/AdjustSdk.framework ${APP_PATH}/proj.ios_mac/ios
		cp -Rv ${ROOT_DIR}/libs/ios/AdjustTestLibrary.framework ${APP_PATH}/proj.ios_mac/ios
		echo -e "$${CYAN}[ADJUST][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Done! ${NC}"
	fi
fi

# ======================================== #

if [ "$APP_TYPE" == "example" ]; then
	echo -e "${CYAN}[ADJUST][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Updating Adjust SDK C++ source files in ${APP_PATH}/Classes/Adjust fodler ... ${NC}"
	cd $APP_PATH
	rm -rfv Classes/Adjust/
	mkdir -p Classes/Adjust/
	cd ${ROOT_DIR}
	cp -Rfv src/* ${APP_PATH}/Classes/Adjust/
	cd ${APP_PATH}/Classes/Adjust
	rm -rf test
	cd ${ROOT_DIR}
	echo -e "${CYAN}[ADJUST][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Success. Make sure AdjustSdk.framework is linked in 'Build Phases'. Run it with Xcode from \`proj.ios_mac\` directory. ${NC}"
	echo -e "${CYAN}[ADJUST][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Done! ${NC}"
elif [ "$APP_TYPE" == "test" ]; then
	echo -e "${CYAN}[ADJUST][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Updating Adjust SDK C++ source files in ${APP_PATH}/Classes/Adjust folder ... ${NC}"
	cd $APP_PATH
	rm -rfv Classes/Adjust/
	mkdir -p Classes/Adjust/
	cd ${ROOT_DIR}
	cp -Rfv src/* ${APP_PATH}/Classes/Adjust/
	cd ${ROOT_DIR}
	cp -Rfv test/app/Classes/* ${APP_PATH}/Classes/
	echo -e "${CYAN}[ADJUST][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Success. Build & run with Android Studio from \`proj.android\` directory. Make sure Android.mk file is modified in accordance with README instructions. ${NC}"
	echo -e "${CYAN}[ADJUST][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Done! ${NC}"
fi

# ======================================== #

echo -e "${CYAN}[ADJUST][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Populate dist folder with files needed for clients ... ${NC}"
cd ${ROOT_DIR}
rm -rfv dist/*
cp -Rfv src/* dist
cd dist
rm -rf test
echo -e "${CYAN}[ADJUST][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Done! ${NC}"

# ======================================== #

echo -e "${CYAN}[ADJUST][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Script completed! ${NC}"
