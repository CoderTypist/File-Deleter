#!/bin/bash
# author Christian Bargraser

i=0
echo "" > hexArray.txt
echo "Created by Christian Bargraser 7/6/2019"
echo ""

echo "unsigned char hexPair[16][16] = {"
echo "unsigned char hexPair[16][16] = {" > hexArray.txt

for c1 in 0 1 2 3 4 5 6 7 8 9 A B C D E F; do
    for c2 in 0 1 2 3 4 5 6 7 8 9 A B C D E F; do

        # creates hex pair
        pair="0x$c1$c2"

        # prints hex pair

        # first hex pair in row
        if [ "$i" -eq 0 ]; then
            line="{$pair, "
            i=$((i+1))

        # last hex pair in row
        elif [ "$i" -eq 15 ]; then

            # last hex pair in the last row
            if [ "0xFF" == "$pair" ]; then
                line=" ${line}${pair}}};"
            else
                line=" ${line}${pair}},"
            fi

            line=$(echo "$line" | sed "s/^ *//g")
            echo "$line" >> hexArray.txt
            echo "$line"

            # clears variables
            line=""
            i=0

        # neither the first or last hex pair in the row
        else
            line=" ${line}${pair}, "
            i=$((i+1))
        fi
    done
done

echo ""
