#!/bin/bash
# setup_env.sh

# Set up CMSSW runtime environment
export SCRAM_ARCH=el9_amd64_gcc13
export CMSSW_VERSION=CMSSW_13_0_5

# Source the CMSSW environment from CVMFS
source /cvmfs/cms.cern.ch/cmsset_default.sh
if [ -r $CMSSW_VERSION/src ] ; then
  cd $CMSSW_VERSION/src
  eval `scramv1 runtime -sh`
  cd -
else
  echo "CMSSW area not found in CVMFS! Exiting..."
  exit 1
fi
