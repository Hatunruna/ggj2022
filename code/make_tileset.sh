#!/bin/sh

FILE=tileset.png

rm -f "${FILE}"
montage *.png -background none -tile 8x8 -geometry 34x34  png32:${FILE}

