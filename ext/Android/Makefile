MVNDIR = ./sdk/Adjust
JARINDIR = ./sdk/Adjust/target
JAROUTDIR = ../../Android
PROXYDIR = ./proxy
JAR = $(JAVA_JDK)/bin/jar
JAVAC = $(JAVA_JDK)/bin/javac
VERSION = $(shell cat ./sdk/VERSION)

default: copy

build: clean
	cd $(MVNDIR); mvn package

clean:
	cd $(MVNDIR); mvn clean

copy: build
	cp $(JARINDIR)/adjust-android-$(VERSION).jar $(PROXYDIR); \
	mv $(PROXYDIR)/adjust-android-$(VERSION).jar $(PROXYDIR)/adjust-android.jar; cd $(PROXYDIR); \
	$(JAVAC) -cp adjust-android.jar com/adjust/sdk/*.java; \
	$(JAR) uf adjust-android.jar com/adjust/sdk/*.class; cd ..; \
	mv $(PROXYDIR)/adjust-android.jar $(JAROUTDIR)/adjust-android.jar; \
	rm $(PROXYDIR)/com/adjust/sdk/*.class;
