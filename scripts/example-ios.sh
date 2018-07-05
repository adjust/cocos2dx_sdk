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

# ======================================== #

echo -e "${CYAN}[ADJUST][IOS][EXAMPLE]:${GREEN} Building AdjustSdk.framework file ... ${NC}"
${ROOT_DIR}/ext/ios/build-sdk.sh
echo -e "${CYAN}[ADJUST][IOS][EXAMPLE]:${GREEN} Done! ${NC}"

# ======================================== #

echo -e "${CYAN}[ADJUST][IOS][EXAMPLE]:${GREEN} Removing old AdjustSdk.framework from example app ... ${NC}"
rm -rfv ${COCOS_EXAMPLES_APP}/proj.ios_mac/ios/AdjustSdk.framework
echo -e "${CYAN}[ADJUST][IOS][EXAMPLE]:${GREEN} Done! ${NC}"

# ======================================== #

echo -e "${CYAN}[ADJUST][IOS][EXAMPLE]:${GREEN} Copying new AdjustSdk.framework to example app ... ${NC}"
cp -Rv ${ROOT_DIR}/libs/ios/AdjustSdk.framework ${COCOS_EXAMPLES_APP}/proj.ios_mac/ios
echo -e "${CYAN}[ADJUST][IOS][EXAMPLE]:${GREEN} Done! ${NC}"

# ======================================== #

echo -e "${CYAN}[ADJUST][ANDROID][EXAMPLE]:${GREEN} Updating Adjust SDK C++ source files in ${COCOS_EXAMPLES_APP}/Classes/Adjust fodler ... ${NC}"
cd $COCOS_EXAMPLES_APP
rm -rfv Classes/Adjust/
mkdir -p Classes/Adjust/
cd ${ROOT_DIR}
cp -Rfv src/* ${COCOS_EXAMPLES_APP}/Classes/Adjust/
echo -e "${CYAN}[ADJUST][ANDROID][EXAMPLE]:${GREEN} Done! ${NC}"
echo -e "${CYAN}[ADJUST][ANDROID][EXAMPLE]:${GREEN} Success. Make sure AdjustSdk.framework is linked in 'Build Phases'. Run it with Xcode from \`proj.ios_mac\` directory. ${NC}"

# ======================================== #

echo -e "${CYAN}[ADJUST][ANDROID][EXAMPLE]:${GREEN} Script completed! ${NC}"
