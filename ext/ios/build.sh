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
    echo -e "${CYAN}[ADJUST][IOS][BUILD]:${GREEN} Usage: ./build.sh [debug || release] [optional: --with-test-lib] ${NC}"
    exit 1
fi

BUILD_TYPE=$1

# ======================================== #

# Directories and paths of interest for the script.
ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
ROOT_DIR="$(dirname "$ROOT_DIR")"
ROOT_DIR="$(dirname "$ROOT_DIR")"
BUILD_DIR=ext/ios/sdk/
TEST_LIB_BUILD_DIR=ext/ios/sdk/AdjustTests/AdjustTestLibrary
LIB_OUT_DIR=libs/ios/

# ======================================== #

echo -e "${CYAN}[ADJUST][IOS][BUILD]:${GREEN} Deleting old AdjustSdk.framework file ... ${NC}"
cd ${ROOT_DIR}
rm -rfv ${LIB_OUT_DIR}/AdjustSdk.framework
echo -e "${CYAN}[ADJUST][IOS][BUILD]:${GREEN} Done! ${NC}"

# ======================================== #

if [ $# -eq 1 ] && [ $1 == --with-test-lib ]; then
	echo -e "${CYAN}[ADJUST][IOS][BUILD]:${GREEN} Deleting old AdjustTestLibrary.framework file ... ${NC}"
	rm -rfv ${LIB_OUT_DIR}/AdjustTestLibrary.framework
	echo -e "${CYAN}[ADJUST][IOS][BUILD]:${GREEN} Done! ${NC}"
fi

# ======================================== #

echo -e "${CYAN}[ADJUST][IOS][BUILD]:${GREEN} Rebuilding AdjustSdk.framework file ... ${NC}"
cd ${ROOT_DIR}/${BUILD_DIR}
if [ "$BUILD_TYPE" == "debug" ]; then
    xcodebuild -target AdjustStatic -configuration Debug clean build
elif [ "$BUILD_TYPE" == "release" ]; then
    xcodebuild -target AdjustStatic -configuration Release clean build
fi
echo -e "${CYAN}[ADJUST][IOS][BUILD]:${GREEN} Done! ${NC}"

# ======================================== #

if [ $# -eq 1 ] && [ $1 == --with-test-lib ]; then
	echo -e "${CYAN}[ADJUST][IOS][BUILD]:${GREEN} Rebuilding AdjustTestLibrary.framework file ... ${NC}"
    cd ${ROOT_DIR}/${TEST_LIB_BUILD_DIR}
    if [ "$BUILD_TYPE" == "debug" ]; then
	    xcodebuild -target AdjustTestLibraryStatic -configuration Debug clean build
	elif [ "$BUILD_TYPE" == "release" ]; then
	    xcodebuild -target AdjustTestLibraryStatic -configuration Release clean build
	fi
	echo -e "${CYAN}[ADJUST][IOS][BUILD]:${GREEN} Done! ${NC}"
fi

# ======================================== #

echo -e "${CYAN}[ADJUST][IOS][BUILD]:${GREEN} Copying AdjustSdk.framework to ${ROOT_DIR}/${LIB_OUT_DIR} ... ${NC}"
cd ${ROOT_DIR}/${BUILD_DIR}
cp -Rv Frameworks/Static/AdjustSdk.framework ${ROOT_DIR}/${LIB_OUT_DIR}
echo -e "${CYAN}[ADJUST][IOS][BUILD]:${GREEN} Done! ${NC}"

# ======================================== #

if [ $# -eq 1 ] && [ $1 == --with-test-lib ]; then
	echo -e "${CYAN}[ADJUST][IOS][BUILD]:${GREEN} Copying AdjustTestLibrary.framework to ${ROOT_DIR}/${LIB_OUT_DIR} ... ${NC}"
	cp -Rv Frameworks/Static/AdjustTestLibrary.framework ${ROOT_DIR}/${LIB_OUT_DIR}
	echo -e "${CYAN}[ADJUST][IOS][BUILD]:${GREEN} Done! ${NC}"
fi

# ======================================== #

echo -e "${CYAN}[ADJUST][IOS][BUILD]:${GREEN} Script completed! ${NC}"
