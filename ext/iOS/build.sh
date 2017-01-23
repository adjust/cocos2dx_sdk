#!/usr/bin/env bash

set -e

SRCDIR=./sdk
LIBOUTDIR=../../iOS

(cd $SRCDIR; xcodebuild -target AdjustStatic -configuration Release clean build)

rm -rfv $LIBOUTDIR/AdjustSdk.framework
cp -Rv $SRCDIR/Frameworks/Static/AdjustSdk.framework $LIBOUTDIR
rm -rfv $SRCDIR/AdjustSdk.framework
