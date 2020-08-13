#!/bin/bash

# Author : Nghia Lam
# Copyright (c) Nghia Lam

cmake -H. -B build
ln -s build/compile_commands.json .

cmake --build build

echo "Finish !!"
