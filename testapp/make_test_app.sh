#!/usr/bin/env bash

# Exit if any errors occur
set -e

if [ $# -ne 2 ]; then
    echo $0: "error. missing arguments. usage: ./make_test_app.sh [platfor: -ios | -android] [location-to-create-new-project]"
    exit 1
fi

if [ $1 != "-ios" ] && [ $1 != "-android" ]; then
    echo $0: "error. wrong platform selected. usage: ./make_test_app.sh [platfor: -ios | -android] [location-to-create-new-project]"
    exit 1
fi

NEW_APP_PATH=$2

# ======================================== ##

# Get the current directory (/testapp/ directory)
TESTAPP_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
# Traverse up to get to the root directory
ROOT_DIR="$(dirname "$TESTAPP_DIR")"

RED='\033[0;31m' # Red color
GREEN='\033[0;32m' # Green color
YELLOW='\033[0;33m' # Green color
NC='\033[0m' # No Color

# ======================================== ##

echo -e "${GREEN}>>> Create directory if not existant ${NC}"
mkdir -p ${NEW_APP_PATH}
echo "Success"

# ======================================== ##

echo -e "${GREEN}>>> Run cocos new ${NC}"
cocos new -l cpp -p com.adjust.testapp -d ${NEW_APP_PATH} testapp
echo "Success"

# ======================================== ##

echo -e "${GREEN}>>> Removing generated Classes directory ${NC}"
cd ${NEW_APP_PATH}/testapp
rm -rfv Classes
echo "Success"

# ======================================== ##

echo -e "${GREEN}>>> Replacing Classes directory ${NC}"
cd ${ROOT_DIR}
cp -Rv ${TESTAPP_DIR}/Classes ${NEW_APP_PATH}/testapp
echo "Success"

# ======================================== ##

echo -e "${GREEN}>>> Copy necessary Adjust files ${NC}"
if [ $1 == -ios ]; then
	${ROOT_DIR}/scripts/testapp-ios.sh ${NEW_APP_PATH}/testapp
else
	${ROOT_DIR}/scripts/testapp-android.sh ${NEW_APP_PATH}/testapp
fi
