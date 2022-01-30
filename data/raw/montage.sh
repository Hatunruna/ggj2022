#!/bin/bash

DIR=$1
PATTERN=$2
TILESET=$3

rm -f "${FILE}"
montage $DIR/$PATTERN*.png -background none -tile 4x3 -geometry 256x256  png32:${DIR}/${TILESET}
