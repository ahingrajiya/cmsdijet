#!/bin/bash

OUTPUT_PATH=/eos/user/a/ahingraj/outputs

#Execution directory
cd ${OUTPUT_PATH}

Dataset=$1

if [ "$Dataset" -eq 1 ]; then
    echo "Removing output UnembeddedPYTHIA files"
    rm -f Unembedded/*.root
    exit 0
fi

if [ "$Dataset" -eq 2 ]; then
    echo "Removing output EmbeddedPYTHIA files"
    rm -f Embedded/*.root
    exit 0
fi

if [ "$Dataset" -eq 3 ]; then
    echo "Removing output MinimumBias files"
    rm -f MB/*.root
    exit 0
fi

if [ "$Dataset" -eq 4 ]; then
    echo "Removing output HM185 files"
    rm -f HM185/*.root
    exit 0
fi

if [ "$Dataset" -eq 5 ]; then
    echo "Removing output HM250 files"
    rm -f HM250/*.root
    exit 0
fi

if [ "$Dataset" -gt 6 ]; then
    echo "Oops! Wrong Number"
    exit 1
fi