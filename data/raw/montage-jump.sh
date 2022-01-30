#!/bin/bash

DIR=$1
PATTERN=$2
TILESET=$3

rm -f "jump.png"
montage \
$DIR/${PATTERN}00.png \
$DIR/${PATTERN}01.png \
$DIR/${PATTERN}02.png \
$DIR/${PATTERN}03.png \
$DIR/${PATTERN}04.png \
$DIR/${PATTERN}05.png \
$DIR/${PATTERN}06.png \
-background none -tile 3x3 -geometry 512x512 png32:${DIR}/jump.png

rm -f "fall.png"
montage \
$DIR/${PATTERN}07.png \
$DIR/${PATTERN}08.png \
$DIR/${PATTERN}09.png \
$DIR/${PATTERN}10.png \
$DIR/${PATTERN}11.png \
$DIR/${PATTERN}12.png \
-background none -tile 3x3 -geometry 512x512 png32:${DIR}/fall.png

rm -f "land.png"
montage \
$DIR/${PATTERN}13.png \
$DIR/${PATTERN}14.png \
$DIR/${PATTERN}15.png \
$DIR/${PATTERN}16.png \
-background none -tile 3x3 -geometry 512x512 png32:${DIR}/land.png
