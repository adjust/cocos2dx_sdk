#!/usr/bin/python
import argparse
from scripting_utils import *

set_log_tag('BUILD-APP')

if __name__ != "__main__":
    error('Error. Do not import this script, but run it explicitly.')
    exit()

# ------------------------------------------------------------------
# Arguments.
parser = argparse.ArgumentParser(description="Script used to build an example/test app or Cocos2dx")
parser.add_argument('app_path', help='Example/Test Project App path')
parser.add_argument('-t', '--apptype', help='type of the project to be created (default - example)', choices=['example', 'test'], default='example')
args = parser.parse_args()

# ------------------------------------------------------------------
# Paths.
script_dir  = os.path.dirname(os.path.realpath(__file__))
root_dir    = os.path.dirname(os.path.normpath(script_dir))
app_path    = args.app_path

recreate_dir(app_path)

try:
    if args.apptype == 'example':
        # ------------------------------------------------------------------
        # Paths.
        example_dir = '{0}/example'.format(root_dir)

        # ------------------------------------------------------------------
        # Create new Cocos2d-x app.
        debug_green('Create new Cocos2d-x app ...')
        cocos_new_project('com.adjust.examples', app_path, 'AdjustExample')

        # ------------------------------------------------------------------
        # Remove autogenerated classes.
        debug_green('Remove autogenerated classes ...')
        remove_files('*', '{0}/AdjustExample/Classes/'.format(app_path))

        # ------------------------------------------------------------------
        # Use Adjust example app classes instead.
        debug_green('Use Adjust example app classes instead ...')
        copy_dir_contents('{0}/Classes/'.format(example_dir), '{0}/AdjustExample/Classes'.format(app_path))
    else:
        # ------------------------------------------------------------------
        # Paths.
        test_app_dir = '{0}/test/app'.format(root_dir)

        # ------------------------------------------------------------------
        # Create new Cocos2d-x app.
        debug_green('Create new Cocos2d-x app ...')
        cocos_new_project('com.adjust.testapp', app_path, 'AdjustTest')

        # ------------------------------------------------------------------
        # Remove autogenerated classes.
        debug_green('Remove autogenerated classes ...')
        remove_files('*', '{0}/AdjustTest/Classes/'.format(app_path))

        # ------------------------------------------------------------------
        # Use Adjust test app classes instead.
        debug_green('Use Adjust example app classes instead ...')
        copy_dir_contents('{0}/Classes/'.format(test_app_dir), '{0}/AdjustTest/Classes'.format(app_path))
finally:
    remove_files('*.pyc', script_dir, log=False)

debug_blue(' For Android:')
debug_blue(' - Follow the README instructions for modifying the Android.mk file.')
debug_blue(' - Follow the README instructions for adding the necessary permissions to AndroidManifest.xml file.')
debug_blue(' - Run "scripts/build_sdk.py" script with providing your newly generated example app path. That should copy the necessary files to the examples app.')
debug_blue(' - Build your app [cocos build -p android].')
debug_blue(' - Run Android Studio and open the project located in "proj.android" to interact with the project.')
debug_blue(' For iOS:')
debug_blue(' - Follow README instructions to add the generated framework in "./iOS" directory to "Build Phases". Make sure to tick the box that says "Copy files if necessary"')
debug_blue(' - Run "scripts/build_sdk.py" script with providing your newly generated example app path. That should copy the necessary files to the examples app.')
debug_blue(' - Run Xcode and open the project located in "proj.ios-mac" to interact with the project.')
