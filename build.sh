#!/bin/sh

set -x  
 
SOURCE_DIR=`pwd`
BUILD_DIR=${BUILD_DIR:-../MiniProgram_http-build}
BUILD_TYPE=${BUILD_TYPE:-Release}
INSTALL_DIR=${INSTALL_DIR:-../${BUILD_TYPE}-install}

BUILD_NO_EXAMPLES=${BUILD_NO_EXAMPLES:-1}

STUB_FORMATTER="echo"

# mkdir -p ../MiniProgram_http-build/Release
# DCMAKE_INSTALL_PREFIX=../Release-install

mkdir -p $BUILD_DIR/$BUILD_TYPE \
    && cd $BUILD_DIR/$BUILD_TYPE \
    && cmake \
        -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
        -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR \
        -DCMAKE_BUILD_NO_EXAMPLES=$BUILD_NO_EXAMPLES \
		-DCMAKE_BUILD_NO_EXAMPLES_EXCEPT_MAIN_PROJECT=0 \
        -DCMAKE_STUB_FORMATTER=$STUB_FORMATTER \
        $SOURCE_DIR \
    && make $*