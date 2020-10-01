#!/bin/bash

# Author : Nghia Lam
# Copyright (c) Nghia Lam

rm -rf bin
rm -rf build
rm -rf compile_command.json

cmake -H. -B build
ln -s build/compile_commands.json .
