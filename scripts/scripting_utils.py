##
##  Various util python methods which can be utilized and shared among different scripts
##
import os, shutil, glob, time, sys, platform, subprocess
from distutils.dir_util import copy_tree

def set_log_tag(t):
    global TAG
    TAG = t

############################################################
### colors for terminal (does not work in Windows... of course)

CEND = '\033[0m'

CBOLD     = '\33[1m'
CITALIC   = '\33[3m'
CURL      = '\33[4m'
CBLINK    = '\33[5m'
CBLINK2   = '\33[6m'
CSELECTED = '\33[7m'

CBLACK  = '\33[30m'
CRED    = '\33[31m'
CGREEN  = '\33[32m'
CYELLOW = '\33[33m'
CBLUE   = '\33[34m'
CVIOLET = '\33[35m'
CBEIGE  = '\33[36m'
CWHITE  = '\33[37m'

CBLACKBG  = '\33[40m'
CREDBG    = '\33[41m'
CGREENBG  = '\33[42m'
CYELLOWBG = '\33[43m'
CBLUEBG   = '\33[44m'
CVIOLETBG = '\33[45m'
CBEIGEBG  = '\33[46m'
CWHITEBG  = '\33[47m'

CGREY    = '\33[90m'
CRED2    = '\33[91m'
CGREEN2  = '\33[92m'
CYELLOW2 = '\33[93m'
CBLUE2   = '\33[94m'
CVIOLET2 = '\33[95m'
CBEIGE2  = '\33[96m'
CWHITE2  = '\33[97m'

CGREYBG    = '\33[100m'
CREDBG2    = '\33[101m'
CGREENBG2  = '\33[102m'
CYELLOWBG2 = '\33[103m'
CBLUEBG2   = '\33[104m'
CVIOLETBG2 = '\33[105m'
CBEIGEBG2  = '\33[106m'
CWHITEBG2  = '\33[107m'

############################################################
### file system util methods

def copy_file(sourceFile, destFile):
    debug('copying: {0} -> {1}'.format(sourceFile, destFile))
    shutil.copyfile(sourceFile, destFile)

def copy_files(fileNamePattern, sourceDir, destDir):
    for file in glob.glob(sourceDir + '/' + fileNamePattern):
        debug('copying: {0} -> {1}'.format(file, destDir))
        shutil.copy(file, destDir)

def copy_dir_contents(sourceDir, destDir):
    debug('copying dir contents: {0} -> {1}'.format(sourceDir, destDir))
    copy_tree(sourceDir, destDir)

def remove_files(fileNamePattern, sourceDir, log=True):
    for file in glob.glob(sourceDir + '/' + fileNamePattern):
        if log:
            debug('deleting: ' + file)
        os.remove(file)

def rename_file(fileNamePattern, newFileName, sourceDir):
    for file in glob.glob(sourceDir + '/' + fileNamePattern):
        debug('rename: {0} -> {1}'.format(file, newFileName))
        os.rename(file, sourceDir + '/' + newFileName)

def remove_dir_if_exists(path):
    if os.path.exists(path):
        debug('deleting dir: ' + path)
        shutil.rmtree(path)
    else:
        error('canot delete {0}. dir does not exist'.format(path))

def remove_file_if_exists(path):
    if os.path.exists(path):
        debug('deleting: ' + path)
        os.remove(path)
    else:
        error('canot delete {0}. file does not exist'.format(path))

def clear_dir(dir):
    shutil.rmtree(dir)
    os.mkdir(dir)

def recreate_dir(dir):
    if os.path.exists(dir):
        shutil.rmtree(dir)
    os.mkdir(dir)

def create_dir_if_not_exist(dir):
    if not os.path.exists(dir):
        os.makedirs(dir)

############################################################
### debug messages util methods

def debug(msg):
    if not is_windows():
        print(('{0}* [{1}][INFO]:{2} {3}').format(CBOLD, TAG, CEND, msg))
    else:
        print(('* [{0}][INFO]: {1}').format(TAG, msg))

def debug_green(msg):
    if not is_windows():
        print(('{0}* [{1}][INFO]:{2} {3}{4}{5}').format(CBOLD, TAG, CEND, CGREEN, msg, CEND))
    else:
        print(('* [{0}][INFO]: {1}').format(TAG, msg))

def debug_blue(msg):
    if not is_windows():
        print(('{0}* [{1}][INFO]:{2} {3}{4}{5}').format(CBOLD, TAG, CEND, CBLUE, msg, CEND))
    else:
        print(('* [{0}][INFO]: {1}').format(TAG, msg))

def error(msg, do_exit=False):
    if not is_windows():
        print(('{0}* [{1}][ERROR]:{2} {3}{4}{5}').format(CBOLD, TAG, CEND, CRED, msg, CEND))
    else:
        print(('* [{0}][ERROR]: {1}').format(TAG, msg))

    if do_exit:
        exit()

############################################################
### util

def check_submodule_dir(platform, submodule_dir):
    if not os.path.isdir(submodule_dir) or not os.listdir(submodule_dir):
        error('Submodule [{0}] folder empty. Did you forget to run >> git submodule update --init --recursive << ?'.format(platform))
        exit()

def is_windows():
    return platform.system().lower() == 'windows';

# https://stackoverflow.com/questions/17140886/how-to-search-and-replace-text-in-a-file-using-python
def replace_text_in_file(file_path, substring, replace_with):
    # Read in the file
    with open(file_path, 'r') as file:
        filedata = file.read()

    # Replace the target string
    filedata = filedata.replace(substring, replace_with)

    # Write the file out again
    with open(file_path, 'w') as file:
        file.write(filedata)

def execute_command(cmd_params, log=True):
    if log:
        debug_blue('Executing: [{0}]'.format(' '.join([str(cmd) for cmd in cmd_params])))
    subprocess.call(cmd_params)

def change_dir(dir):
    os.chdir(dir)

def get_env_variable(var_name):
    return os.environ[var_name];

def xcode_build(target, configuration='Release'):
    execute_command(['xcodebuild', '-target', target, '-configuration', configuration, 'clean', 'build'])

def adb_uninstall(package):
    execute_command(['adb', 'uninstall', package])

def adb_install_apk(path):
    execute_command(['adb', 'install', '-r', path])

def adb_shell(app_package):
    execute_command(['adb', 'shell', 'monkey', '-p', app_package, '1'])

def gradle_make_release_jar(do_clean=False):
    if (do_clean):
        execute_command(['./gradlew', 'clean', 'makeReleaseJar'])
    else:
        execute_command(['./gradlew', 'makeReleaseJar'])

def gradle_make_debug_jar(do_clean=False):
    if (do_clean):
        execute_command(['./gradlew', 'clean', 'makeDebugJar'])
    else:
        execute_command(['./gradlew', 'makeDebugJar'])    

def gradle_run(options):
    cmd_params = ['./gradlew']
    for opt in options:
        cmd_params.append(opt)
    execute_command(cmd_params)

def get_javac_path():
    java_home_7_env = get_env_variable('JAVA_HOME_7')
    return '{0}/bin/javac'.format(java_home_7_env)

def get_jar_path():
    java_home_7_env = get_env_variable('JAVA_HOME_7')
    return '{0}/bin/jar'.format(java_home_7_env)

def get_android_jar_path():
    android_home = get_env_variable('ANDROID_HOME')
    return '{0}/platforms/android-23/android.jar'.format(android_home)

def unpack_adjust_android_jar():
    execute_command([get_javac_path(), '-cp', 'adjust-android.jar:{0}'.format(get_android_jar_path()), 'com/adjust/sdk/*.java'])

def unpack_adjust_testing_jar():
    execute_command([get_javac_path(), '-cp', 'adjust-testing.jar:{0}'.format(get_android_jar_path()), 'com/adjust/testlibrary/*.java'])

def inject_cpp_bridge():
    execute_command([get_jar_path(), 'uf', 'adjust-android.jar', 'com/adjust/sdk/*.class'])

def inject_cpp_testing_bridge():
    execute_command([get_jar_path(), 'uf', 'adjust-testing.jar', 'com/adjust/testlibrary/*.class'])

def update_dist(root_dir):
    debug_green('Populate dist folder with files needed for clients ...')
    recreate_dir('{0}/dist'.format(root_dir))
    copy_dir_contents('{0}/src'.format(root_dir), '{0}/dist'.format(root_dir))
    remove_dir_if_exists('{0}/dist/test'.format(root_dir))

### cocos specific

def cocos_new_project(package_name, app_path, name):
    execute_command(['cocos', 'new', '-l', 'cpp', '-p', package_name, '-d', app_path, name])

############################################################
### nonsense, eyecandy and such

def waiting_animation(duration, step):
    if(duration <= step):
        return

    line = '-'
    line_killer = '\b'
    while duration >= 0:
        duration -= step
        sys.stdout.write(line)
        sys.stdout.flush()
        sys.stdout.write(line_killer)
        line += '-'
        line_killer += '\b'
        if len(line) > 65:
            line = '-'
        time.sleep(step)
