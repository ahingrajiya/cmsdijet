#!/bin/bash
# run_dijetana.sh

# Arguments passed from CRAB
input_file_list=$1
output_file=$2
ismc=$3
isembedded=$4

echo "==> Starting job with arguments:"
echo "Input file list: $input_file_list"
echo "Output file: $output_file"
echo "IsMC: $ismc"
echo "IsEmbedded: $isembedded"

# Setup CMSSW / ROOT environment
source ./setup_env.sh

# Copy input file list
cp $input_file_list .

# Run your executable
chmod +x ./OODijetAna
./OODijetAna $input_file_list $output_file $ismc $isembedded

# Check job success
if [ $? -ne 0 ]; then
    echo "ERROR: OODijetAna failed."
    exit 1
fi

# Define EOS output directory
EOSDIR="/eos/user/a/ahingraj/output/OO_Data"

echo "==> Copying output to EOS: ${EOSDIR}/${output_file}"

# Use xrdcp to copy to EOS
xrdcp -f $output_file root://eosuser.cern.ch/${EOSDIR}/${output_file}
if [ $? -ne 0 ]; then
    echo "ERROR: xrdcp to EOS failed."
    exit 2
fi

echo "==> Output successfully copied to EOS."
