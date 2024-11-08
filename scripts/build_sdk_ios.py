from scripting_utils import *

def build(root_dir, ios_submodule_dir, apptype, configuration, app_path):
    if (apptype == 'example'):
        build_example(root_dir, ios_submodule_dir, configuration, app_path)
    else:
        build_test(root_dir, ios_submodule_dir, configuration, app_path)

def build_example(root_dir, ios_submodule_dir, configuration, app_path):
    # ------------------------------------------------------------------
    # Building AdjustSdk.framework file.
    debug_green('Building AdjustSdk.framework file ...')
    _build_sdk(root_dir, ios_submodule_dir, configuration, with_test_lib=False)

    # ------------------------------------------------------------------
    # Copying new AdjustSdk.framework to example app.
    debug_green('Copying new AdjustSdk.framework to example app ...')
    remove_dir_if_exists('{0}/proj.ios_mac/ios/AdjustSdk.framework'.format(app_path))
    copy_dir_contents('{0}/libs/ios/AdjustSdk.framework'.format(root_dir), '{0}/proj.ios_mac/ios/AdjustSdk.framework'.format(app_path), copy_symlinks=True)

    # ------------------------------------------------------------------
    # Updating Adjust SDK C++ source files in ${APP_PATH}/Classes/Adjust fodler.
    debug_green('Updating Adjust SDK C++ source files in {0}/Classes/Adjust fodler ...'.format(app_path))
    recreate_dir('{0}/Classes/Adjust'.format(app_path))
    copy_dir_contents('{0}/src'.format(root_dir), '{0}/Classes/Adjust'.format(app_path))
    remove_dir_if_exists('{0}/Classes/Adjust/test'.format(app_path))

    # ------------------------------------------------------------------
    # Populate dist folder with files needed for clients.
    update_dist(root_dir)

    debug_green('Success. Make sure AdjustSdk.framework is linked in "Build Phases". Run it with Xcode from "proj.ios_mac" directory.')

def build_test(root_dir, ios_submodule_dir, configuration, app_path):
    # ------------------------------------------------------------------
    # Building AdjustSdk.framework and AdjustTestLibrary.framework file.
    debug_green('Building AdjustSdk.framework and AdjustTestLibrary.framework file ...')
    _build_sdk(root_dir, ios_submodule_dir, configuration, with_test_lib=True)

    # ------------------------------------------------------------------
    # Copying new AdjustSdk.framework & AdjustTestLibrary.framework to example app.
    debug_green('Copying new AdjustSdk.framework & AdjustTestLibrary.framework to test app ...')
    remove_dir_if_exists('{0}/proj.ios_mac/ios/AdjustSdk.framework'.format(app_path))
    remove_dir_if_exists('{0}/proj.ios_mac/ios/AdjustTestLibrary.framework'.format(app_path))
    copy_dir_contents('{0}/libs/ios/AdjustSdk.framework'.format(root_dir), '{0}/proj.ios_mac/ios/AdjustSdk.framework'.format(app_path), copy_symlinks=True)
    copy_dir_contents('{0}/test/libs/ios/AdjustTestLibrary.framework'.format(root_dir), '{0}/proj.ios_mac/ios/AdjustTestLibrary.framework'.format(app_path), copy_symlinks=True)

    # ------------------------------------------------------------------
    # Updating Adjust SDK C++ source files in ${APP_PATH}/Classes/Adjust folder.
    debug_green('Updating Adjust SDK C++ source files in {0}/Classes/Adjust fodler ...'.format(app_path))
    recreate_dir('{0}/Classes/Adjust'.format(app_path))
    copy_dir_contents('{0}/src'.format(root_dir), '{0}/Classes/Adjust'.format(app_path))
    copy_dir_contents('{0}/test/app/Classes'.format(root_dir), '{0}/Classes'.format(app_path))

    # ------------------------------------------------------------------
    # Populate dist folder with files needed for clients.
    update_dist(root_dir)

    debug_green('Success. Make sure AdjustSdk.framework & AdjustTestLibrary.framework is linked in "Build Phases". Run it with Xcode from "proj.ios_mac" directory.')

def _build_sdk(root_dir, ios_submodule_dir, configuration, with_test_lib=False):
    # ------------------------------------------------------------------
    # Paths.
    build_dir          = '{0}'.format(ios_submodule_dir)
    test_lib_build_dir = '{0}/AdjustTests/AdjustTestLibrary'.format(build_dir)
    lib_out_dir        = '{0}/libs/ios'.format(root_dir)
    test_lib_out_dir   = '{0}/test/libs/ios'.format(root_dir)

    # ------------------------------------------------------------------
    # Deleting old AdjustSdk.framework file.
    debug_green('Deleting old AdjustSdk.framework file ...')
    remove_dir_if_exists('{0}/AdjustSdk.framework'.format(lib_out_dir))

    # ------------------------------------------------------------------
    # Deleting old AdjustTestLibrary.framework file.
    if with_test_lib:
        debug_green('Deleting old AdjustTestLibrary.framework file ...')
        remove_dir_if_exists('{0}/AdjustTestLibrary.framework'.format(test_lib_out_dir))

    # ------------------------------------------------------------------
    # Rebuilding AdjustSdk.framework file.
    debug_green('Rebuilding AdjustSdk.framework file ...')
    change_dir(build_dir)
    # if configuration == 'debug':
    #     xcode_build('AdjustStatic', 'Debug')
    # else:
    #     xcode_build('AdjustStatic', 'Release')
    execute_command(['./scripts/build_frameworks.sh', '-fs', '-ios'])

    # ------------------------------------------------------------------
    # Copying AdjustSdk.framework to ${ROOT_DIR}/${LIB_OUT_DIR}.
    debug_green('Copying AdjustSdk.framework to {0} ...'.format(lib_out_dir))
    copy_dir_contents('{0}/sdk_distribution/frameworks-static/AdjustSdk-iOS-Static/AdjustSdk.framework'.format(build_dir), '{0}/AdjustSdk.framework'.format(lib_out_dir), copy_symlinks=True)

    # ------------------------------------------------------------------
    # Rebuilding AdjustTestLibrary.framework file.
    if with_test_lib:
        debug_green('Rebuilding AdjustTestLibrary.framework file ...')
        # change_dir(test_lib_build_dir)
        # if configuration == 'debug':
        #     xcode_build('AdjustTestLibraryStatic', 'Debug')
        # else:
        #     xcode_build('AdjustTestLibraryStatic', 'Release')
        execute_command(['./scripts/build_frameworks.sh', '-test', '-ios'])

        # ------------------------------------------------------------------
        # Copying AdjustTestLibrary.framework to ${ROOT_DIR}/${LIB_OUT_DIR}.
        debug_green('Copying AdjustTestLibrary.framework to {0} ...'.format(test_lib_out_dir))
        copy_dir_contents('{0}/sdk_distribution/test-static-framework/AdjustTestLibrary.framework'.format(build_dir), '{0}/AdjustTestLibrary.framework'.format(test_lib_out_dir), copy_symlinks=True)
