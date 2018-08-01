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
LIBS_DIR=libs/android

RED='\033[0;31m' # Red color
GREEN='\033[0;32m' # Green color
NC='\033[0m' # No Color

# ======================================== ##

echo -e "${GREEN}>>> Removing test app from test device ${NC}"
adb uninstall com.adjust.testapp || true

# ======================================== ##

echo -e "${GREEN}>>> Building Adjust Android & Test Library JAR files ${NC}"
${ROOT_DIR}/ext/android/build-sdk.sh release --with-test-lib

# ======================================== ##

echo -e "${GREEN}>>> Moving adjust jar to ${TEST_APP_PATH} ${NC}"
cd ${ROOT_DIR}/${LIBS_DIR}
mkdir ${TEST_APP_PATH}/proj.android/app/libs || true
cp -v adjust-android.jar ${TEST_APP_PATH}/proj.android/app/libs/
cp -v adjust-testing.jar ${TEST_APP_PATH}/proj.android/app/libs/
cp -v gson-2.8.1.jar ${TEST_APP_PATH}/proj.android/app/libs/

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

echo -e "${GREEN}>>> Success. Build & run with Android Studio from \`proj.android\` directory. Make sure Android.mk file is modified per README instructions ${NC}"
