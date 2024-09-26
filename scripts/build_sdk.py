#!/usr/bin/python
import argparse
from scripting_utils import *
import build_sdk_android as android
import build_sdk_ios     as ios

set_log_tag('COCOS2DX-SDK')

if __name__ != "__main__":
    error('Error. Do not import this script, but run it explicitly.')
    exit()

# ------------------------------------------------------------------
# Arguments
parser = argparse.ArgumentParser(description="Script used to build Adjust SDK for Cocos2d-x platform.")
parser.add_argument('-p', '--platform', help='Platform to which the scripts will be ran for', choices=['android', 'ios'])
parser.add_argument('-t', '--apptype', help='Type of the application to be updated.', choices=['example', 'test'], default='example')
parser.add_argument('-c', '--configuration', help='Build configuration.', choices=['release', 'debug'], default='release')
parser.add_argument('-a', '--apppath', help='Example/Test Project App path')
args = parser.parse_args()

# ------------------------------------------------------------------
# Paths.
dir_scripts     = os.path.dirname(os.path.realpath(__file__))
dir_root        = os.path.dirname(os.path.normpath(dir_scripts))
dir_ext_android = '{0}/ext/android'.format(dir_root)
dir_ext_ios     = '{0}/ext/ios'.format(dir_root)

# ------------------------------------------------------------------
# Call platform specific build method.
try:
    if args.platform == 'ios':
        set_log_tag('IOS-SDK-BUILD')
        check_submodule_dir('iOS', dir_ext_ios + '/sdk')
        ios.build(dir_root, dir_ext_ios + '/sdk', args.apptype, args.configuration, args.apppath)
    else:
        set_log_tag('ANROID-SDK-BUILD')
        check_submodule_dir('Android', dir_ext_android + '/sdk')
        android.build(dir_root, dir_ext_android, args.apptype, args.configuration, args.apppath)
finally:
    # Remove autocreated python compiled files.
    remove_files('*.pyc', dir_scripts, log=False)

# ------------------------------------------------------------------
# Script completed.
debug_green('Script completed!')
