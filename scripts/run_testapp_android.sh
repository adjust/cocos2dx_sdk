#!/usr/bin/env bash

# Exit if any errors occur
set -e

# Get the current directory (/scripts/ directory)
SCRIPTS_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
# Traverse up to get to the root directory
ROOT_DIR="$(dirname "$SCRIPTS_DIR")"
PROXY_DIR=ext/Android/proxy

ANDROIDJAR=$ANDROID_HOME/platforms/android-23/android.jar
JAR=$JAVA_HOME_7/bin/jar
JAVAC=$JAVA_HOME_7/bin/javac

RED='\033[0;31m' # Red color
GREEN='\033[0;32m' # Green color
NC='\033[0m' # No Color

echo -e "${GREEN}>>> Removing test app from test device ${NC}"
adb uninstall com.adjust.testapp || true

echo -e "${GREEN}>>> Building Adjust Android JAR file ${NC}"
${ROOT_DIR}/ext/android/build.sh release

echo -e "${GREEN}>>> Unpacking adjust-android.jar & adjust-testing.jar files ${NC}"
cd ${ROOT_DIR}/${PROXY_DIR}
$JAVAC -cp "adjust-android.jar:$ANDROIDJAR" com/adjust/sdk/*.java
$JAVAC -cp "adjust-testing.jar:$ANDROIDJAR" com/adjust/testlibrary/*.java

echo -e "${GREEN}>>> Injecting c++ bridge to adjust-android.jar & adjust-testing.jar ${NC}"
cd ${ROOT_DIR}/${PROXY_DIR}
$JAR uf adjust-android.jar com/adjust/sdk/*.class
$JAR uf adjust-testing.jar com/adjust/testlibrary/*.class

echo -e "${GREEN}>>> Deleting .classes files ${NC}"
cd ${ROOT_DIR}/${PROXY_DIR}
rm -rfv com/adjust/sdk/*.class
rm -rfv com/adjust/testlibrary/*.class

echo -e "${GREEN}>>> Moving adjust jar to ${COCOS_TEST_APP} ${NC}"
cd ${ROOT_DIR}/${PROXY_DIR}
mkdir ${COCOS_TEST_APP}/proj.android/app/libs || true
cp -v adjust-android.jar ${COCOS_TEST_APP}/proj.android/app/libs/
cp -v adjust-testing.jar ${COCOS_TEST_APP}/proj.android/app/libs/
cp -v ../Android/gson-2.8.1.jar ${COCOS_TEST_APP}/proj.android/app/libs/

echo -e "${GREEN}>>> Removing and recreating ${COCOS_TEST_APP}/Classes/Adjust ${NC}"
cd $COCOS_TEST_APP
rm -rfv Classes/Adjust/
rm -rfv Classes/AdjustTesting/
mkdir -p Classes/Adjust/
mkdir -p Classes/AdjustTesting/

echo -e "${GREEN}>>> Moving classes to ${COCOS_TEST_APP} ${NC}"
cd ${ROOT_DIR}
cp -Rfv Adjust/* ${COCOS_TEST_APP}/Classes/Adjust/
cp -Rfv AdjustTesting/* ${COCOS_TEST_APP}/Classes/AdjustTesting/

echo -e "${GREEN}>>> Success. Build & run with Android Studio from \`proj.android\` directory. Make sure Android.mk file is modified per README instructions ${NC}"
