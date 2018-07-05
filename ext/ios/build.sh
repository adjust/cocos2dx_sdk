#!/usr/bin/env bash

# End script if one of the lines fails
set -e

# Get the current directory (ext/ios/)
ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Traverse up to get to the root directory
ROOT_DIR="$(dirname "$ROOT_DIR")"
ROOT_DIR="$(dirname "$ROOT_DIR")"
BUILD_DIR=ext/iOS/sdk/
LIB_OUT_DIR=iOS/

RED='\033[0;31m' # Red color
GREEN='\033[0;32m' # Green color
NC='\033[0m' # No Color

echo -e "${GREEN}>>> Delete old .framework file ${NC}"
cd ${ROOT_DIR}
rm -rfv ${LIB_OUT_DIR}/AdjustSdk.framework

echo -e "${GREEN}>>> Build framework from source ${NC}"
cd ${ROOT_DIR}/${BUILD_DIR}
xcodebuild -target AdjustStatic -configuration Release clean build

echo -e "${GREEN}>>> Build successful. Move to root/ios directory ${NC}"
cd ${ROOT_DIR}/${BUILD_DIR}
cp -Rv Frameworks/Static/AdjustSdk.framework ${ROOT_DIR}/${LIB_OUT_DIR}
