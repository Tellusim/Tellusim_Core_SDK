#!/bin/bash

# RmlUi - The HTML/CSS User Interface Library Evolved
# Uses Windows Subsystem for Linux on Windows
#
# Usage: clone.sh

TARGET=RmlUi.git

# remove TARGET
rm -rf ./$TARGET

# download TARGET
git clone https://github.com/mikke89/$TARGET $TARGET

# copy headers
rm -rf ./RmlUi
rsync -av ./$TARGET/Include/RmlUi/Core.h ./RmlUi/
rsync -av ./$TARGET/Include/RmlUi/Core/ ./RmlUi/Core
rsync -av ./$TARGET/Include/RmlUi/Config/ ./RmlUi/Config
rm -rf ./RmlUi/Core/Containers

# copy libraries
#rsync -av $CLAYROOT/extern/lib/ ./lib
#find ./lib -not -name "*freetype*" -and -not -name "*rmlui*" -delete
