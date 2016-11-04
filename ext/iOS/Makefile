SRCDIR = ./sdk
LIBOUTDIR = ../../iOS

default: copy

build:	
	cd $(SRCDIR); \
	xcodebuild -target AdjustStatic -configuration Release clean build

copy: build
	rm -rf $(LIBOUTDIR)/AdjustSdk.framework; \
	cp -R $(SRCDIR)/Frameworks/Static/AdjustSdk.framework $(LIBOUTDIR); \
	rm -rf $(SRCDIR)/AdjustSdk.framework
