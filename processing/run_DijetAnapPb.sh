#!/bin/bash

#Change the path to the CMSSW_13_0_5 directory
CMS_PATH=${HOME}/private/analysis/CMSSW_13_0_5/src
cd ${CMS_PATH}

#Export the CMSSW environment
eval 'scramv1 runtime -sh'

EXEC_PATH=${HOME}/private/analysis/CMSSW_13_0_5/src/cmsdijet/executions_dir
cd ${EXEC_PATH}

input_file_list=$1
output_file=$2
ismc=$3
isembedded=$4
isPbgoing=$5
pthatmin=$6
pthatmax=$7


./pPbDijetAna ${input_file_list} ${output_file} ${ismc} ${isembedded} ${isPbgoing} ${pthatmin} ${pthatmax}


