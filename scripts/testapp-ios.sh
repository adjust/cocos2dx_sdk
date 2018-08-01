#!/usr/bin/env bash

# Exit if any errors occur
set -e

if [ $# -ne 1 ]; then
    echo $0: "error. missing arguments. usage: ./testapp-ios.sh [location-of-test-app-project]"
    exit 1
fi

TEST_APP_PATH=$1

# Get the current directory (/scripts/ directory)
SCRIPTS_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
# Traverse up to get to the root directory
ROOT_DIR="$(dirname "$SCRIPTS_DIR")"

RED='\033[0;31m' # Red color
GREEN='\033[0;32m' # Green color
NC='\033[0m' # No Color

# ======================================== ##

echo -e "${GREEN} Building AdjustSdk.framework file ... ${NC}"
${ROOT_DIR}/ext/ios/build-sdk.sh --with-test-lib
echo -e "${GREEN} Done! ${NC}"

# ======================================== ##

echo -e "${GREEN} Removing old AdjustSdk.framework & AdjustTestLibrary.framework from test app ... ${NC}"
rm -rfv ${TEST_APP_PATH}/proj.ios_mac/ios/AdjustSdk.framework
rm -rfv ${TEST_APP_PATH}/proj.ios_mac/ios/AdjustTestLibrary.framework
echo -e "${GREEN} Done! ${NC}"

# ======================================== ##

echo -e "${GREEN} Copying new AdjustSdk.framework & AdjustTestLibrary.framework to test app ... ${NC}"
cp -Rv ${ROOT_DIR}/libs/ios/AdjustSdk.framework ${TEST_APP_PATH}/proj.ios_mac/ios
cp -Rv ${ROOT_DIR}/libs/ios/AdjustTestLibrary.framework ${TEST_APP_PATH}/proj.ios_mac/ios
echo -e "${GREEN} Done! ${NC}"

# ======================================== ##

echo -e "${GREEN}>>> Removing and recreating ${TEST_APP_PATH}/Classes/Adjust ${NC}"
cd $TEST_APP_PATH
rm -rfv Classes/Adjust/
mkdir -p Classes/Adjust/

# ======================================== ##

echo -e "${GREEN}>>> Moving classes to ${TEST_APP_PATH} ${NC}"
cd ${ROOT_DIR}
cp -Rfv src/* ${TEST_APP_PATH}/Classes/Adjust/

# ======================================== ##

echo -e "${GREEN}>>> Success. Make sure AdjustSdk.framework & AdjustTestLibrary.framework (and GameController.framework) are linked in 'Build Phases'. ${NC}"
echo -e "${GREEN}>>> Run it with Xcode from \`proj.ios_mac\` directory. ${NC}"
