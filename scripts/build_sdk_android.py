from scripting_utils import *

def build(root_dir, android_submodule_dir, apptype, configuration, app_path):
    if (apptype == 'example'):
        build_example(root_dir, android_submodule_dir, configuration, app_path)
    else:
        build_test(root_dir, android_submodule_dir, configuration, app_path)

def build_example(root_dir, android_submodule_dir, configuration, app_path):
    # ------------------------------------------------------------------
    # paths]
    android_libs_dir = '{0}/libs/android/'.format(root_dir)

    # ------------------------------------------------------------------
    # Removing example app from test device/emulator
    debug_green('Removing example app from test device/emulator ...')
    adb_uninstall('com.adjust.examples')

    # ------------------------------------------------------------------
    # Building Adjust SDK JAR file
    debug_green('Building Adjust SDK JAR file ...')
    _build_sdk(root_dir, android_submodule_dir, configuration, with_test_lib=False)

    # ------------------------------------------------------------------
    # Copying Adjust SDK JAR to Cocos2d-x example app at APP_PATH
    debug_green('Copying Adjust SDK JAR to Cocos2d-x example app at {0} ...'.format(app_path))
    create_dir_if_not_exist('{0}/proj.android/app/libs'.format(app_path))
    copy_file('{0}/adjust-android.jar'.format(android_libs_dir), '{0}/proj.android/app/libs/adjust-android.jar'.format(app_path))

    # ------------------------------------------------------------------
    # Updating Adjust SDK C++ source files in ${APP_PATH}/Classes/Adjust fodler
    debug_green('Updating Adjust SDK C++ source files in {0}/Classes/Adjust fodler ...'.format(app_path))
    recreate_dir('{0}/Classes/Adjust'.format(app_path))
    copy_dir_contents('{0}/src'.format(root_dir), '{0}/Classes/Adjust'.format(app_path))
    remove_dir_if_exists('{0}/Classes/Adjust/test'.format(app_path))

    # ------------------------------------------------------------------
    # Populate dist folder with files needed for clients
    update_dist(root_dir)

    debug_green('Success. Build & run with Android Studio from "proj.android" directory. Make sure Android.mk file is modified in accordance with README instructions.')

def build_test(root_dir, android_submodule_dir, configuration, app_path):
    # ------------------------------------------------------------------
    # paths]
    android_libs_dir      = '{0}/libs/android/'.format(root_dir)
    android_test_libs_dir = '{0}/test/libs/android'.format(root_dir)

    # ------------------------------------------------------------------
    # Removing test app from test device/emulator
    debug_green('Removing test app from test device/emulator ...')
    adb_uninstall('com.adjust.testapp')

    # ------------------------------------------------------------------
    # Building Adjust SDK JAR file
    debug_green('Building Adjust SDK JAR file ...')
    _build_sdk(root_dir, android_submodule_dir, configuration, with_test_lib=True)

    # ------------------------------------------------------------------
    # Copying Adjust SDK and test JAR files to Cocos2d-x test app at APP_PATH
    debug_green('Copying Adjust SDK and test JAR files to Cocos2d-x test app at {0} ...'.format(app_path))
    create_dir_if_not_exist('{0}/proj.android/app/libs'.format(app_path))
    copy_file('{0}/adjust-android.jar'.format(android_libs_dir), '{0}/proj.android/app/libs/adjust-android.jar'.format(app_path))
    copy_file('{0}/adjust-testing.jar'.format(android_test_libs_dir), '{0}/proj.android/app/libs/adjust-testing.jar'.format(app_path))
    copy_file('{0}/gson-2.8.1.jar'.format(android_test_libs_dir), '{0}/proj.android/app/libs/gson-2.8.1.jar'.format(app_path))

    # ------------------------------------------------------------------
    # Updating Adjust SDK C++ source files in ${APP_PATH}/Classes/Adjust folder
    debug_green('Updating Adjust SDK C++ source files in {0}/Classes/Adjust fodler ...'.format(app_path))
    recreate_dir('{0}/Classes/Adjust'.format(app_path))
    copy_dir_contents('{0}/src'.format(root_dir), '{0}/Classes/Adjust/'.format(app_path))
    copy_dir_contents('{0}/test/app/Classes'.format(root_dir), '{0}/Classes'.format(app_path))

    # ------------------------------------------------------------------
    # Populate dist folder with files needed for clients
    update_dist(root_dir)

    debug_green('Success. Build & run with Android Studio from "proj.android" directory. Make sure Android.mk file is modified in accordance with README instructions.')
    
def _build_sdk(root_dir, android_submodule_dir, configuration, with_test_lib=False):
    # ------------------------------------------------------------------
    # paths]
    proxy_dir         = '{0}/proxy'.format(android_submodule_dir)
    libs_out_dir      = '{0}/libs/android'.format(root_dir)
    test_libs_out_dir = '{0}/test/libs/android/'.format(root_dir)
    test_libs_in_dir  = ''
    build_dir         = '{0}/sdk/Adjust'.format(android_submodule_dir)
    jar_in_dir        = ''

    change_dir(build_dir)

    # ------------------------------------------------------------------
    # Running clean and make JAR Gradle tasks for Adjust SDK project
    debug_green('Running clean and make JAR Gradle tasks for Adjust SDK project ...')
    if (configuration == 'release'):
        gradle_make_release_jar(do_clean=True)
        jar_in_dir = '{0}/adjust/build/intermediates/bundles/debug'.format(build_dir)
    else:
        gradle_make_debug_jar(do_clean=True)
        jar_in_dir = '{0}/adjust/build/intermediates/bundles/release'.format(build_dir)

    # ------------------------------------------------------------------
    # Copying Android SDK JAR from ${JAR_IN_DIR} to ${PROXY_DIR}
    debug_green('Copying Android SDK JAR from {0} to {1} ...'.format(jar_in_dir, proxy_dir))
    copy_file('{0}/classes.jar'.format(jar_in_dir), '{0}/adjust-android.jar'.format(proxy_dir))

    if with_test_lib:
        # ------------------------------------------------------------------
        # Running clean and makeJar Gradle tasks for Adjust test library project
        debug_green('Running clean and makeJar Gradle tasks for Adjust test library project ...')
        gradle_run(['clean', 'makeJar'])
        if (configuration == 'release'):
            test_libs_in_dir = '{0}/testlibrary/build/intermediates/bundles/release'.format(build_dir)
        else:
            test_libs_in_dir = '{0}/testlibrary/build/intermediates/bundles/debug'.format(build_dir)

        # ------------------------------------------------------------------
        # Copying Testing JAR from ${TESTLIB_JAR_IN_DIR} to ${PROXY_DIR}
        debug_green('Copying Testing JAR from {0} to {1} ...'.format(test_libs_in_dir, proxy_dir))
        copy_file('{0}/classes.jar'.format(test_libs_in_dir), '{0}/adjust-testing.jar'.format(proxy_dir))

    # ------------------------------------------------------------------
    # Injecting C++ bridge changes
    change_dir(proxy_dir)
    inject_cpp_bridge(proxy_dir, with_test_lib)

    # ------------------------------------------------------------------
    # Deleting .class files
    debug_green('Deleting .class files ...')
    remove_files('*.class', '{0}/com/adjust/sdk/'.format(proxy_dir))
    if with_test_lib:
        remove_files('*.class', '{0}/com/adjust/testlibrary/'.format(proxy_dir))

    # ------------------------------------------------------------------
    # Copying resulting adjust-android.jar into libs_out_dir
    debug_green('Copying resulting adjust-android.jar into {0} ...'.format(libs_out_dir))
    copy_file('{0}/adjust-android.jar'.format(proxy_dir), '{0}/adjust-android.jar'.format(libs_out_dir))

    # ------------------------------------------------------------------
    # Copying resulting adjust-testing.jar into test libs out dir
    if with_test_lib:
        debug_green('Copying resulting adjust-testing.jar into {0} ...'.format(test_libs_out_dir))
        copy_file('{0}/adjust-testing.jar'.format(proxy_dir), '{0}/adjust-testing.jar'.format(test_libs_out_dir))    
