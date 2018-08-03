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
if [ $# -ne 2 ] && [ $# -ne 3 ]; then
    echo -e "${CYAN}[ADJUST][IOS][BUILD]:${GREEN} Usage: ./build.sh [debug || release] [private || public] [optional: --with-test-lib] ${NC}"
    exit 1
fi

BUILD_TYPE=$1
REPO_TYPE=$2

# ======================================== #

# Directories and paths of interest for the script.
ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
ROOT_DIR="$(dirname "$ROOT_DIR")"
ROOT_DIR="$(dirname "$ROOT_DIR")"
if [ "$REPO_TYPE" == "public" ]; then
    BUILD_DIR=ext/ios/sdk/
    TEST_LIB_BUILD_DIR=ext/ios/sdk/AdjustTests/AdjustTestLibrary
    REPO_TYPE_UC="PUBLIC"
elif [ "$REPO_TYPE" == "private" ]; then
    BUILD_DIR=ext/ios/sdk-dev/
    TEST_LIB_BUILD_DIR=ext/ios/sdk-dev/AdjustTests/AdjustTestLibrary
    REPO_TYPE_UC="PRIVATE"
fi
if [ "$BUILD_TYPE" == "debug" ]; then
    BUILD_TYPE_UC="DEBUG"
elif [ "$BUILD_TYPE" == "release" ]; then
    REPO_TYPE_UC="RELEASE"
fi
LIB_OUT_DIR=libs/ios/

# ======================================== #

echo -e "${CYAN}[ADJUST][IOS][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Deleting old AdjustSdk.framework file ... ${NC}"
cd ${ROOT_DIR}
rm -rfv ${LIB_OUT_DIR}/AdjustSdk.framework
echo -e "${CYAN}[ADJUST][IOS][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Done! ${NC}"

# ======================================== #

if [ $# -eq 3 ] && [ $3 == --with-test-lib ]; then
	echo -e "${CYAN}[ADJUST][IOS][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Deleting old AdjustTestLibrary.framework file ... ${NC}"
	rm -rfv ${LIB_OUT_DIR}/AdjustTestLibrary.framework
	echo -e "${CYAN}[ADJUST][IOS][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Done! ${NC}"
fi

# ======================================== #

echo -e "${CYAN}[ADJUST][IOS][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Rebuilding AdjustSdk.framework file ... ${NC}"
cd ${ROOT_DIR}/${BUILD_DIR}
if [ "$BUILD_TYPE" == "debug" ]; then
    xcodebuild -target AdjustStatic -configuration Debug clean build
elif [ "$BUILD_TYPE" == "release" ]; then
    xcodebuild -target AdjustStatic -configuration Release clean build
fi
echo -e "${CYAN}[ADJUST][IOS][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Done! ${NC}"

# ======================================== #

if [ $# -eq 3 ] && [ $3 == --with-test-lib ]; then
	echo -e "${CYAN}[ADJUST][IOS][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Rebuilding AdjustTestLibrary.framework file ... ${NC}"
    cd ${ROOT_DIR}/${TEST_LIB_BUILD_DIR}
    if [ "$BUILD_TYPE" == "debug" ]; then
	    xcodebuild -target AdjustTestLibraryStatic -configuration Debug clean build
	elif [ "$BUILD_TYPE" == "release" ]; then
	    xcodebuild -target AdjustTestLibraryStatic -configuration Release clean build
	fi
	echo -e "${CYAN}[ADJUST][IOS][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Done! ${NC}"
fi

# ======================================== #

echo -e "${CYAN}[ADJUST][IOS][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Copying AdjustSdk.framework to ${ROOT_DIR}/${LIB_OUT_DIR} ... ${NC}"
cd ${ROOT_DIR}/${BUILD_DIR}
cp -Rv Frameworks/Static/AdjustSdk.framework ${ROOT_DIR}/${LIB_OUT_DIR}
echo -e "${CYAN}[ADJUST][IOS][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Done! ${NC}"

# ======================================== #

if [ $# -eq 3 ] && [ $3 == --with-test-lib ]; then
	echo -e "${CYAN}[ADJUST][IOS][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Copying AdjustTestLibrary.framework to ${ROOT_DIR}/${LIB_OUT_DIR} ... ${NC}"
	cp -Rv Frameworks/Static/AdjustTestLibrary.framework ${ROOT_DIR}/${LIB_OUT_DIR}
	echo -e "${CYAN}[ADJUST][IOS][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Done! ${NC}"
fi

# ======================================== #

echo -e "${CYAN}[ADJUST][IOS][BUILD][$REPO_TYPE_UC][$BUILD_TYPE_UC]:${GREEN} Script completed! ${NC}"
