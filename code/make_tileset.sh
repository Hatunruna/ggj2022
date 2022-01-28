#!/bin/sh

FILE=tileset.png

rm -f "${FILE}"
montage *.png -background none -tile 8x8 -geometry 32x32  png32:${FILE}

