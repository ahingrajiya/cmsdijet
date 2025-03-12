#! /bin/bash

input_file_path=$1
input_file=$2
nfiles_per_job=$3


cd ${input_file_path}

if [ ! -f "$input_file" ]; then
    echo "The input file does not exist"
    exit 1
fi

NEW_DIR="${input_file%.*}"

mkdir -p "${NEW_DIR}_Split"

rm -f "${NEW_DIR}_Split/*.txt"




if [ $nfiles_per_job -eq 0 ]; then
    nfiles_per_job=1
fi

split -l $nfiles_per_job "$input_file" "${NEW_DIR}_Split/${input_file%.*}_part_" -d -a 4 --additional-suffix=.txt

echo "${input_file_path}${NEW_DIR}_Split"


