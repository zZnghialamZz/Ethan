#!/bin/bash

# Author : Nghia Lam
# Copyright (c) Nghia Lam

rm -rf bin
rm -rf build
rm -rf compile_command.json

# NOTE(Nghia Lam):
#   - compile_command.json file is for using with emacs + clangd server
#     (require compiler support help generate this file <- consider to
#     use MinGW64 on Windows).
#   - "-Wno-dev" flag will disable the warnings of freetype library.
/usr/local/bin/cmake -Wno-dev -H. -B build
ln -s build/compile_commands.json .
