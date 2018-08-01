#!/usr/bin/env bash

set -e

# ======================================== #

# Colors for output
NC='\033[0m'
RED='\033[0;31m'
CYAN='\033[1;36m'
GREEN='\033[0;32m'

# ======================================== #

# Directories and paths of interest for the script.
ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
ROOT_DIR="$(dirname "$ROOT_DIR")"
ROOT_DIR="$(dirname "$ROOT_DIR")"
BUILD_DIR=ext/ios/sdk/
TEST_LIB_BUILD_DIR=ext/ios/sdk/AdjustTests/AdjustTestLibrary
LIB_OUT_DIR=libs/ios/

# ======================================== #

echo -e "${CYAN}[ADJUST][IOS][BUILD-SDK]:${GREEN} Deleting old AdjustSdk.framework file ... ${NC}"
cd ${ROOT_DIR}
rm -rfv ${LIB_OUT_DIR}/AdjustSdk.framework

if [ $1 == --with-test-lib ]; then
	echo -e "${CYAN}[ADJUST][IOS][BUILD-SDK]:${GREEN} Deleting old AdjustTestLibrary.framework file ... ${NC}"
	rm -rfv ${LIB_OUT_DIR}/AdjustTestLibrary.framework
fi

echo -e "${CYAN}[ADJUST][IOS][BUILD-SDK]:${GREEN} Done! ${NC}"

# ======================================== #

echo -e "${CYAN}[ADJUST][IOS][BUILD-SDK]:${GREEN} Rebuilding AdjustSdk.framework file ... ${NC}"
cd ${ROOT_DIR}/${BUILD_DIR}
xcodebuild -target AdjustStatic -configuration Release clean build

if [ $1 == --with-test-lib ]; then
	echo -e "${CYAN}[ADJUST][IOS][BUILD-SDK]:${GREEN} Rebuilding AdjustTestLibrary.framework file ... ${NC}"
    cd ${ROOT_DIR}/${TEST_LIB_BUILD_DIR}
	xcodebuild -target AdjustTestLibraryStatic -configuration Release clean build
fi

echo -e "${CYAN}[ADJUST][IOS][BUILD-SDK]:${GREEN} Done! ${NC}"

# ======================================== #

echo -e "${CYAN}[ADJUST][IOS][BUILD-SDK]:${GREEN} Build successful. Copying AdjustSdk.framework to ${ROOT_DIR}/${LIB_OUT_DIR} ... ${NC}"
cd ${ROOT_DIR}/${BUILD_DIR}
cp -Rv Frameworks/Static/AdjustSdk.framework ${ROOT_DIR}/${LIB_OUT_DIR}

if [ $1 == --with-test-lib ]; then
	echo -e "${CYAN}[ADJUST][IOS][BUILD-SDK]:${GREEN} Build successful. Copying AdjustTestLibrary.framework to ${ROOT_DIR}/${LIB_OUT_DIR} ... ${NC}"
	cp -Rv Frameworks/Static/AdjustTestLibrary.framework ${ROOT_DIR}/${LIB_OUT_DIR}
fi

echo -e "${CYAN}[ADJUST][IOS][BUILD-SDK]:${GREEN} Done! ${NC}"

# ======================================== #

echo -e "${CYAN}[ADJUST][IOS][BUILD-SDK]:${GREEN} Script completed! ${NC}"
