#!/bin/bash
# Runs on the batch worker. Needs nothing from AFS: condor copies
# sandbox_pp.tgz (executable + libJetAnalysis + aux_files) and the input list
# into the scratch dir, and ROOT comes from the CMSSW release on CVMFS.

input_file_list=$1
output_file=$2
ismc=$3
collenergy=$4

echo "Host: $(hostname)   Start: $(date)"

# CMSSW_VERSION and SCRAM_ARCH are passed in from the submit file
source /cvmfs/cms.cern.ch/cmsset_default.sh
scram project CMSSW "${CMSSW_VERSION}" > /dev/null || { echo "scram project failed"; exit 1; }
cd "${CMSSW_VERSION}/src" || exit 1
eval "$(scramv1 runtime -sh)"
cd "${_CONDOR_SCRATCH_DIR}" || exit 1

# Unpack keeping the repo layout, so ../aux_files/... resolves from executions_dir
tar -xzf sandbox_pp.tgz || { echo "sandbox unpack failed"; exit 1; }
export LD_LIBRARY_PATH="${_CONDOR_SCRATCH_DIR}/build:${LD_LIBRARY_PATH}"

cd executions_dir || exit 1
./ppDijetAna "${_CONDOR_SCRATCH_DIR}/${input_file_list}" "${output_file}" "${ismc}" "${collenergy}"
