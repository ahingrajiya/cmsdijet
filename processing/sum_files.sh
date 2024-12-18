#!/bin/bash

OUTPUT_PATH=/eos/user/a/ahingraj/outputs

#Execution directory
cd ${OUTPUT_PATH}

fileName=$1
Dataset=$2

if [ "$Dataset" -eq 1 ]; then
    echo "Creating output file $1 wiht UnembeddedPYTHIA output files"
    hadd $1 Unembedded/*.root
    exit 0
fi

if [ "$Dataset" -eq 2 ]; then
    echo "Creating output file $1 wiht EmbeddedPYTHIA output files"
    hadd $1 Embedded/*.root
    exit 0
fi

if [ "$Dataset" -eq 3 ]; then
    echo "Creating output file $1 wiht MinimumBias output files"
    hadd $1 MB/*.root
    exit 0
fi

if [ "$Dataset" -eq 4 ]; then
    echo "Creating output file $1 wiht HM185 output files"
    hadd $1 HM185/*.root
    exit 0
fi

if [ "$Dataset" -eq 5 ]; then
    echo "Creating output file $1 wiht HM250 output files"
    hadd $1 HM250/*.root
    exit 0
fi

if [ "$Dataset" -gt 6 ]; then
    echo "Oops! Wrong Number"
    exit 1
fi

