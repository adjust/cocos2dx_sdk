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
SCRIPTS_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
ROOT_DIR="$(dirname "$SCRIPTS_DIR")"
PROXY_DIR=ext/android/proxy

# ======================================== #

echo -e "${CYAN}[ADJUST][ANDROID][EXAMPLE]:${GREEN} Removing example app from test device ... ${NC}"
adb uninstall com.adjust.examples || true
echo -e "${CYAN}[ADJUST][ANDROID][EXAMPLE]:${GREEN} Done! ${NC}"

# ======================================== #

echo -e "${CYAN}[ADJUST][ANDROID][EXAMPLE]:${GREEN} Building Adjust SDK JAR file ... ${NC}"
${ROOT_DIR}/ext/android/build-sdk.sh release
echo -e "${CYAN}[ADJUST][ANDROID][EXAMPLE]:${GREEN} Done! ${NC}"

# ======================================== #

echo -e "${CYAN}[ADJUST][ANDROID][EXAMPLE]:${GREEN} Copying Adjust SDK JAR to Cocos2d-x example app at ${COCOS_EXAMPLES_APP} ... ${NC}"
cd ${ROOT_DIR}/${PROXY_DIR}
mkdir ${COCOS_EXAMPLES_APP}/proj.android/app/libs || true
cp -v adjust-android.jar ${COCOS_EXAMPLES_APP}/proj.android/app/libs/
echo -e "${CYAN}[ADJUST][ANDROID][EXAMPLE]:${GREEN} Done! ${NC}"

# ======================================== #

echo -e "${CYAN}[ADJUST][ANDROID][EXAMPLE]:${GREEN} Updating Adjust SDK C++ source files in ${COCOS_EXAMPLES_APP}/Classes/Adjust fodler ... ${NC}"
cd $COCOS_EXAMPLES_APP
rm -rfv Classes/Adjust/
mkdir -p Classes/Adjust/
cd ${ROOT_DIR}
cp -Rfv src/* ${COCOS_EXAMPLES_APP}/Classes/Adjust/
echo -e "${CYAN}[ADJUST][ANDROID][EXAMPLE]:${GREEN} Done! ${NC}"
echo -e "${CYAN}[ADJUST][ANDROID][EXAMPLE]:${GREEN} Success. Build & run with Android Studio from \`proj.android\` directory. Make sure Android.mk file is modified in accordance with README instructions. ${NC}"

# ======================================== #

echo -e "${CYAN}[ADJUST][ANDROID][EXAMPLE]:${GREEN} Script completed! ${NC}"
