#!/usr/bin/python
import argparse
from scripting_utils import *
import build_sdk_android as android
import build_sdk_ios     as ios

set_log_tag('BUILD-SDK')

if __name__ != "__main__":
    error('Error. Do not import this script, but run it explicitly.')
    exit()

# ------------------------------------------------------------------
# set arguments
parser = argparse.ArgumentParser(description="Script used to build SDK or Cocos2dx")
parser.add_argument('platform', help='platform to which the scripts will be ran for', choices=['android', 'ios'])
parser.add_argument('-t', '--apptype', help='type of the application to be updated', choices=['example', 'test'], default='example')
parser.add_argument('-c', '--configuration', help='build configuration', choices=['release', 'debug'], default='release')
parser.add_argument('app_path', help='Example/Test Project App path')

args = parser.parse_args()

# ------------------------------------------------------------------
# common paths
script_dir              = os.path.dirname(os.path.realpath(__file__))
root_dir                = os.path.dirname(os.path.normpath(script_dir))
android_submodule_dir   = '{0}/ext/android'.format(root_dir)
ios_submodule_dir       = '{0}/ext/ios'.format(root_dir)

# ------------------------------------------------------------------
# Call platform specific build method.
try:
    if args.platform == 'ios':
        set_log_tag('IOS-SDK-BUILD')
        check_submodule_dir('iOS', ios_submodule_dir + '/sdk')
        ios.build(root_dir, ios_submodule_dir, args.apptype, args.configuration, args.app_path)
    else:
        set_log_tag('ANROID-SDK-BUILD')
        check_submodule_dir('Android', android_submodule_dir + '/sdk')
        android.build(root_dir, android_submodule_dir, args.apptype, args.configuration, args.app_path)
finally:
    # Remove autocreated python compiled files.
    remove_files('*.pyc', script_dir, log=False)

# ------------------------------------------------------------------
# Script completed.
debug_green('Script completed!')
