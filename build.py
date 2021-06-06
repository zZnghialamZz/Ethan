# ==============================================================================
# @File   : build.py
# @Brief  : All in one build file of every platforms for Ethan.
# @Author : Nghia Lam <nghialam12795@gmail.com>
# ---
#
# TODO(Nghia Lam):
#   - Build options (shared library, executable).
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

import logging

from optparse import OptionParser


__version__ = "0.0.1"
__doc__ = "All in one build file of every platforms for Ethan."


# ------------------------------------------------------------------------------
# Build configurations
# ------------------------------------------------------------------------------
BUILD_TYPE = ['Debug', 'Release']
BUILD_CONFIG = ['ETHAN_SHARED', 'ETHAN_EXECUTABLE']


def build():
    global BUILD_TYPE, BUILD_CONFIG

    # Build here


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
        help='Build configs as %s. Default: %s' % (BUILD_CONFIG, BUILD_CONFIG[0]),
    )

    # Parse input
    options, _   = parser.parse_args()
    BUILD_TYPE   = options.build_type
    BUILD_CONFIG = options.build_config

    build()

if __name__ == '__main__':
    main()
