#!/usr/bin/env bash

set -e

MVNDIR=./sdk/Adjust
JARINDIR=./sdk/Adjust/target
JAROUTDIR=../../Android
PROXYDIR=./proxy
JAR=$JAVA_JDK_7/bin/jar
JAVAC=$JAVA_JDK_7/bin/javac
ANDROIDJAR=$ANDROID_HOME/platforms/android-9/android.jar
VERSION=$(cat ./sdk/VERSION)

(cd $MVNDIR; mvn clean)
(cd $MVNDIR; mvn package)

cp -v $JARINDIR/adjust-android-$VERSION.jar $PROXYDIR
mv -v $PROXYDIR/adjust-android-$VERSION.jar $PROXYDIR/adjust-android.jar; cd $PROXYDIR
$JAVAC -cp "adjust-android.jar:$ANDROIDJAR" com/adjust/sdk/*.java
$JAR uf adjust-android.jar com/adjust/sdk/*.class; cd ..
mv -v $PROXYDIR/adjust-android.jar $JAROUTDIR/adjust-android.jar
rm -v $PROXYDIR/com/adjust/sdk/*.class;
