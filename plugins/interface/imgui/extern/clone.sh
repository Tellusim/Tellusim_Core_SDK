#!/bin/bash

# ImGui
# Uses Windows Subsystem for Linux on Windows
#
# Usage: clone.sh

TARGET=imgui.git

# remove TARGET
rm -rf ./$TARGET

# download TARGET
git clone https://github.com/ocornut/$TARGET $TARGET
