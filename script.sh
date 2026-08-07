#!/bin/bash

mkdir -p frames

cycles=2

scenes=(
    "scenes/race_1.xml"
    "scenes/race_2.xml"
    "scenes/race_3.xml"
    "scenes/race_4.xml"
    "scenes/race_5.xml"
    "scenes/race_6.xml"
    "scenes/race_7.xml"
    "scenes/race_8.xml"
    "scenes/race_9.xml"
    "scenes/race_10.xml"
    "scenes/race_11.xml"
    "scenes/race_12.xml"
    "scenes/race_13.xml"
    "scenes/race_14.xml"
    "scenes/race_15.xml"
    "scenes/race_16.xml"
    "scenes/race_17.xml"
    "scenes/race_18.xml"
    "scenes/race_19.xml"
    "scenes/race_20.xml"
    "scenes/race_21.xml"
    "scenes/race_22.xml"
    "scenes/race_23.xml"
    "scenes/race_24.xml"
    "scenes/race_25.xml"
    "scenes/race_26.xml"
    "scenes/race_27.xml"
    "scenes/race_28.xml"
    "scenes/race_29.xml"
    "scenes/race_30.xml"
    "scenes/race_31.xml"
    "scenes/race_32.xml"
    "scenes/race_33.xml"
    "scenes/race_34.xml"
    "scenes/race_35.xml"
    "scenes/race_36.xml"
    "scenes/race_37.xml"
)

frame_count=0

for ((i=0; i<cycles; i++)); do
    for ((j=0; j<${#scenes[@]}; j++)); do
        ./build/PEinT "${scenes[$j]}"
        mv race.png "frames/frame_$(printf "%03d" "$frame_count").png"
        ((frame_count++))
    done
done

frame_rate=12

ffmpeg -framerate $frame_rate \
    -i frames/frame_%03d.png \
    -filter_complex "split[s0][s1];[s0]palettegen[p];[s1][p]paletteuse" \
    output.gif
