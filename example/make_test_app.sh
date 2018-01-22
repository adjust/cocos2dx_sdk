#!/usr/bin/env bash

# Exit if any errors occur
set -e

if [ $# -ne 1 ]; then
    echo $0: "usage: ./make_test_app.sh [location-to-create-new-project]"
    exit 1
fi

NEW_APP_PATH=$1

# Get the current directory (/example/ directory)
EXAMPLE_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
# Traverse up to get to the root directory
ROOT_DIR="$(dirname "$EXAMPLE_DIR")"

RED='\033[0;31m' # Red color
GREEN='\033[0;32m' # Green color
NC='\033[0m' # No Color

echo -e "${GREEN}>>> Create directory if not existant ${NC}"
mkdir -p ${NEW_APP_PATH}
echo "Success"

echo -e "${GREEN}>>> run cocos new ${NC}"
cocos new -l cpp -p com.adjust.examples -d ${NEW_APP_PATH} examples
echo "Success"

echo -e "${GREEN}>>> Removing generated Classes directory ${NC}"
cd ${NEW_APP_PATH}
rm -rfv Classes/*
echo "Success"

echo -e "${GREEN}>>> Replacing Classes directory ${NC}"
cd ${ROOT_DIR}
cp -Rv ${EXAMPLE_DIR}/Classes/* ${NEW_APP_PATH}/Classes/
echo "Success"

echo
echo -e "${GREEN}>>> Add the following environmental variable to your .zshrc file or .bashrc: ${NC}"
echo 'export COCOS_EXAMPLES_APP=/Users/ab/Dev/company/cocos2dx-projects/examples'
echo 'export PATH=$COCOS_EXAMPLES_APP:$PATH'
echo

echo -e "${GREEN}>>> After that, go to https://github.com/adjust/cocos2dx_sdk/ ${NC}"
echo -e "${GREEN}>>> For Android: ${NC}"
echo -e "${GREEN}>>> - Run \'ext/android/build.sh\') ${NC}"
echo -e "${GREEN}>>> - Follow the README instructions for modifying the Android.mk file. ${NC}"
echo -e "${GREEN}>>> - Run \`scripts/testing_android.sh\`. That should copy the necessary files to the examples app. ${NC}"
echo -e "${GREEN}>>> - Run Android Studio and open the project located in \`proj.android-studio\` to interact with the project. ${NC}"
echo
echo -e "${GREEN}>>> For iOS: ${NC}"
echo -e "${GREEN}>>> - Run \'ext/ios/build.sh\') ${NC}"
echo -e "${GREEN}>>> - Follow README instructions to add the generated framework in \`./iOS\` directory to \'Build Phases\'. Make sure to tick the box that says \"Copy files if necessary\" ${NC}"
echo -e "${GREEN}>>> - Run \`scripts/testing_android.sh\`. That should copy the necessary files to the examples app. ${NC}"
echo -e "${GREEN}>>> - Run Xcode and open the project located in \`proj.ios-mac\` to interact with the project. ${NC}"
