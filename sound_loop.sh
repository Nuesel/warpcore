#!/bin/bash
soundfile=$1
if [ -f "$soundfile" ]
then
while : ; do lame --quiet --decode $soundfile - -| aplay -q ; done
fi
