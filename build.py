# ==============================================================================
# @File   : build.py
# @Brief  : All in one build file of every platforms for Ethan.
# @Author : Nghia Lam <nghialam12795@gmail.com>
# ---
#
# TODO(Nghia Lam):
#   - [ ] Build options (shared library, executable).
#
# ---
# @License: MIT License.
#
# Copyright (c) 2021 Nghia Lam
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
# ==============================================================================

import os
import sys
import logging
import platform
import subprocess

from optparse import OptionParser


# TODO(Nghia Lam): Detect the version from ethan.h
__version__ = "0.0.1"
__doc__ = "All in one build file of every platforms for Ethan."


# ------------------------------------------------------------------------------
# Global architectures
# ------------------------------------------------------------------------------

# Operating system architecture
ARCH = platform.architecture()[0]
SYSTEM64 = platform.machine().endswith('64')
SYSTEM32 = not SYSTEM64

# Get current platforms
WIN32 = (platform.system() == "Windows")
LINUX = (platform.system() == "Linux")
MACOS = (platform.system() == "Darwin")

# Directories
ROOT_DIR = os.path.abspath(os.path.dirname(os.path.dirname(__file__)))
BUILD_DIR = os.path.join(ROOT_DIR, "build")


# ------------------------------------------------------------------------------
# Build configurations
# ------------------------------------------------------------------------------
BUILD_TYPE = ['Debug', 'Release']
BUILD_CONFIG = ['ETHAN_BUILD_SHARED', 'ETHAN_USE_SHARED', 'ETHAN_EXECUTABLE']

MAIN_FILE = os.path.join(ROOT_DIR, 'ethan.cpp')

# NOTE(Nghia Lam): These Visual Studio constants are used to setup our build
# environment in Windows platform if the user decides to use cl to build the
# project.
# ---
# TODO(Nghia Lam): Find better way for managing this vcvarall location and auto
# detect the version of it.
VS_VERSION = 2019
VS_PLATFORM = 'x86' if SYSTEM32 else 'x64'
VS_VCVARS = ('C:\\Program Files (x86)\\Microsoft Visual Studio\\'
             + str(VS_VERSION)
             + '\\Community\\VC\\Auxiliary\\Build\\vcvarsall.bat')

# ------------------------------------------------------------------------------
# Build script here
# ------------------------------------------------------------------------------
def _assertion(condition, error_message):
    if not condition:
        logging.error('%s Please see --help for more information.',
                      error_message)
        sys.exit(1)


def _check_dependencies():
    global ARCH, BUILD_TYPE, BUILD_CONFIG

    api = ''
    if WIN32:
        api = 'Win32 API'
    elif MACOS:
        api = 'MacOS Native'

    # TODO(Nghia Lam): Renderer information here

    logging.info('''Checking dependencies...
    ----------------------------------------------------------
    Detect current platform information:
      - OS: %s
      - Arch: %s
      - Python: %s

    Current build settings:
      - Build type: %s
      - Build config: %s
      - API: %s
    ----------------------------------------------------------''',
                 platform.system(),
                 ARCH,
                 platform.python_version(),
                 BUILD_TYPE,
                 BUILD_CONFIG,
                 api)


def _check_directories():
    logging.info('Checking directories...')
    if not os.path.exists(BUILD_DIR):
        os.makedirs(BUILD_DIR)


def _get_compiler():
    if WIN32:
        return 'cl'
    elif MACOS:
        return 'clang'

    return None


def _get_compile_flags():
    result = []
    if WIN32:
        # NOTE(Nghia Lam): Compile flags on Windows:
        #   - Zi: debug info (use Z7 older debug format for complex build).
        #   - FC: full path on errors.
        result.append('-FC')
        result.append('-Zi')
    elif MACOS:
        # NOTE(Nghia Lam): Compile flags on MacOS:
        #   - -g: Enable all debugger features.
        result.append('-g')

    return result


def _get_link_libraries():
    result = []
    if WIN32:
        result.append('user32.lib')
        result.append('gdi32.lib')
    elif MACOS:
        # NOTE(Nghia Lam): Libraries on MacOS:
        #   - AppKit: Default NS Library
        result.append('-framework')
        result.append('AppKit')
        # result.append('-o osx_dango-go')

    return result


def _get_output_options():
    global BUILD_CONFIG

    result = []
    if WIN32:
        if (BUILD_CONFIG == 'ETHAN_BUILD_SHARED' or
            BUILD_CONFIG == 'ETHAN_USE_SHARED'):
            result.append('-LD')

    return result


def _get_environment():
    logging.info('Setup environment...')
    result = []

    if WIN32:
        result.append(VS_VCVARS)
        result.append(VS_PLATFORM)

    return result


def build():
    logging.info('Ethan build startup ...')

    # Prerequisites
    _check_dependencies()
    _check_directories()

    # Execute build command
    compiler = _get_compiler()
    compile_flags = _get_compile_flags()
    link_libraries = _get_link_libraries()
    output_option = _get_output_options()

    _assertion(compiler != None, 'Cannot detect compiler !')
    _assertion(compile_flags != None, 'Cannot get default compile flags !')
    _assertion(link_libraries != None, 'Cannot get linked libraries !')

    args = list()
    if _get_environment(): # Not all the OS need to setup the environment.
        args.extend(_get_environment())
        args.append('&&')
    args.append(compiler)
    args.extend(compile_flags)
    args.extend(link_libraries)
    args.extend(output_option)
    args.append(MAIN_FILE)

    build = subprocess.Popen(args, cwd=BUILD_DIR)
    build.wait()
    _assertion(build.returncode == 0, 'Build failed !!')

    logging.info('Ethan finish building !')


def main():
    global BUILD_TYPE, BUILD_CONFIG

    # Logging initialization
    logging.basicConfig(level=logging.INFO,
                        format='[ETHAN] %(levelname)s: %(message)s')

    # CLI
    usage = 'python build.py [options]'
    parser = OptionParser(usage=usage, description=__doc__, version=__version__)
    parser.disable_interspersed_args()

    parser.add_option(
        '-b',
        '--build',
        type = 'choice',
        choices=BUILD_TYPE,
        dest='build_type',
        default=BUILD_TYPE[0],
        help='Build as %s mode. Default: %s' % (BUILD_TYPE, BUILD_TYPE[0]),
    )
    parser.add_option(
        '-c',
        '--config',
        type = 'choice',
        choices=BUILD_CONFIG,
        dest='build_config',
        default=BUILD_CONFIG[0],
        help='Build config as %s. Default: %s' % (BUILD_CONFIG, BUILD_CONFIG[0]),
    )

    # Parse input
    options, _   = parser.parse_args()
    BUILD_TYPE   = options.build_type
    BUILD_CONFIG = options.build_config

    build()

if __name__ == '__main__':
    main()
