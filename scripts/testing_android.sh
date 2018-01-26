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

echo -e "${GREEN}>>> Removing app from test device ${NC}"
adb uninstall com.adjust.examples || true

echo -e "${GREEN}>>> Building Adjust Android JAR file ${NC}"
${ROOT_DIR}/ext/android/build.sh release

echo -e "${GREEN}>>> Unpacking adjust-android.jar file ${NC}"
cd ${ROOT_DIR}/${PROXY_DIR}
$JAVAC -cp "adjust-android.jar:$ANDROIDJAR" com/adjust/sdk/*.java

echo -e "${GREEN}>>> Injecting c++ bridge to adjust-android.jar ${NC}"
cd ${ROOT_DIR}/${PROXY_DIR}
$JAR uf adjust-android.jar com/adjust/sdk/*.class

echo -e "${GREEN}>>> Deleting .classes files ${NC}"
cd ${ROOT_DIR}/${PROXY_DIR}
rm -rfv com/adjust/sdk/*.class

echo -e "${GREEN}>>> Moving jar to ${COCOS_EXAMPLES_APP} ${NC}"
cd ${ROOT_DIR}/${PROXY_DIR}
mkdir ${COCOS_EXAMPLES_APP}/proj.android-studio/app/libs || true
cp -v adjust-android.jar ${COCOS_EXAMPLES_APP}/proj.android-studio/app/libs/

echo -e "${GREEN}>>> Removing and recreating ${COCOS_EXAMPLES_APP}/Classes/Adjust ${NC}"
cd $COCOS_EXAMPLES_APP
rm -rfv Classes/Adjust/
mkdir Classes/Adjust/

echo -e "${GREEN}>>> Moving classes to ${COCOS_EXAMPLES_APP} ${NC}"
cd ${ROOT_DIR}
cp -Rfv Adjust/* ${COCOS_EXAMPLES_APP}/Classes/Adjust/

echo -e "${GREEN}>>> Success. Build & run with Android Studio from \`proj.android-studio\` directory. Make sure Android.mk file is modified per README instructions ${NC}"
