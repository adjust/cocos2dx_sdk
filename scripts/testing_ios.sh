#!/usr/bin/env bash

# Exit if any errors occur
set -e

# Get the current directory (/scripts/ directory)
SCRIPTS_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
# Traverse up to get to the root directory
ROOT_DIR="$(dirname "$SCRIPTS_DIR")"

RED='\033[0;31m' # Red color
GREEN='\033[0;32m' # Green color
NC='\033[0m' # No Color

echo -e "${GREEN}>>> Building Adjust .framework file ${NC}"
${ROOT_DIR}/ext/ios/build.sh

echo -e "${GREEN}>>> Build successful. Removing old .framework ${NC}"
rm -rfv ${COCOS_EXAMPLES_APP}/proj.ios_mac/ios/AdjustSdk.framework

echo -e "${GREEN}>>> Copying new .framework to examples app ${NC}"
cp -Rv ${ROOT_DIR}/iOS/AdjustSdk.framework ${COCOS_EXAMPLES_APP}/proj.ios_mac/ios

echo -e "${GREEN}>>> Removing and recreating ${COCOS_EXAMPLES_APP}/Classes/Adjust ${NC}"
cd $COCOS_EXAMPLES_APP
rm -rfv Classes/Adjust
mkdir Classes/Adjust

echo -e "${GREEN}>>> Moving classes to ${COCOS_EXAMPLES_APP} ${NC}"
cd ${ROOT_DIR}
cp -Rfv Adjust/* ${COCOS_EXAMPLES_APP}/Classes/Adjust

echo -e "${GREEN}>>> Success. Make sure AdjustSdk.framework is linked in 'Build Phases'. Run it with Xcode from \`proj.ios_mac\` directory ${NC}"
