#! /bin/bash

#Change the path to the CMSSW_13_0_5 directory
EXEC_PATH=${HOME}/private/analysis/CMSSW_13_0_5/src/cmsdijet
cd ${EXEC_PATH}

mkdir -p "executions_dir"
cp -r "$EXEC_PATH/build/pPbDijetAna" "executions_dir"

