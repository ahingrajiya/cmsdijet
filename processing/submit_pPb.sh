#!/bin/bash
CMS_PATH=${HOME}/private/analysis/CMSSW_13_0_5/src
# CMS_PATH=${HOME}/analysis/jetAnalysis/

cd ${CMS_PATH}
# eval 'cmsenv'

#Change the path to the CMSSW_13_0_5 directory
EXEC_PATH=${HOME}/private/analysis/CMSSW_13_0_5/src/cmsdijet
# EXEC_PATH=${HOME}/analysis/jetAnalysis/

cd ${EXEC_PATH}

mkdir -p "executions_dir"
cp -r "$EXEC_PATH/build/pPbDijetAna" "executions_dir"

DataSet=$1
isPbgoing=$2
files_per_job=$3

if [ "$DataSet" -eq 1 ]; then
    echo "Unembedded pPb Datasset is selected"
    cd ${EXEC_PATH}/processing
    if [ "$isPbgoing" -eq 1 ]; then
        echo "Pbgoing is selected"
        condor_submit MC_unembedded_Pbgoing_submission_nopthatcut.sub
        exit 0
    elif [ "$isPbgoing" -eq 0 ]; then
        echo "pgoing is selected"
        condor_submit MC_unembedded_pgoing_submission_nopthatcut.sub
        exit 0
    fi
fi

if [ "$DataSet" -eq 2 ]; then
    echo "Embedded pPb Dataset is selected"
    cd ${EXEC_PATH}/processing
    if [ "$isPbgoing" -eq 1 ]; then
        echo "Pbgoing is selected"
        condor_submit MC_embedded_Pbgoing_submission_nopthatcut.sub
        exit 0
    elif [ "$isPbgoing" -eq 0 ]; then
        echo "pgoing is selected"
        condor_submit MC_embedded_pgoing_submission_nopthatcut.sub
        exit 0
    fi
fi

if [ "$DataSet" -eq 3 ]; then
    echo "MB pPb Dataset is selected"
    if [ "$isPbgoing" -eq 1 ]; then
        echo "Pbgoing is selected"
        sample_prefilx="MB_Pbgoing"
        input_files_list="${EXEC_PATH}/files_input/pPb_8160/DATA_MB/Pbgoing/"
        
    elif [ "$isPbgoing" -eq 0 ]; then
        echo "pgoing is selected"
        sample_prefilx="MB_pgoing"
        input_files_list="${EXEC_PATH}/files_input/pPb_8160/DATA_MB/pgoing/"
    fi
fi

if [ "$DataSet" -eq 4 ]; then
    echo "HM185 pPb Dataset is selected"
    if [ "$isPbgoing" -eq 1 ]; then
        echo "Pbgoing is selected"
        sample_prefilx="HM185_Pbgoing"
        input_files_list="/files_input/pPb_8160/DATA_HM185/Pbgoing"
        
    elif [ "$isPbgoing" -eq 0 ]; then
        echo "pgoing is selected"
        sample_prefilx="HM185_pgoing"
        input_files_list="${EXEC_PATH}/files_input/pPb_8160/DATA_HM185/pgoing/"
    fi
fi

if [ "$DataSet" -eq 5 ]; then
    echo "HM185 pPb Dataset is selected"
    if [ "$isPbgoing" -eq 1 ]; then
        echo "Pbgoing is selected"
        sample_prefilx="HM250_Pbgoing"
        input_files_list="${EXEC_PATH}/files_input/pPb_8160/DATA_HM250/Pbgoing/"
        
    elif [ "$isPbgoing" -eq 0 ]; then
        echo "pgoing is selected"
        sample_prefilx="HM185_pgoing"
        input_files_list="${EXEC_PATH}/files_input/pPb_8160/DATA_HM250/pgoing/"
    fi
fi

if [ "$DataSet" -gt 6 ]; then
    echo "No Data Set Selected. Use numbers from 1 to 5"
    exit 1
fi
echo "${PWD}"
echo "Input File List : ${input_files_list}"

for filename in ${PWD}${input_files_list}/*.txt; do
 processing/split_files.sh ${PWD}${input_files_list} $(basename "$filename") $files_per_job
done
# PD_Number=1
# for filename in "${PWD}${input_files_list}/*.txt"; do
#     echo "Processing file: $(basename $filename)"
#     ${PWD}/processing/split_files.sh ${PWD}${input_files_list} $($basename $filename) $files_per_job
#     file_list=$(./split_files.sh ${input_files_list} $($basename $filename) $files_per_job)
#     cat <<EOF > pPb_${$(basename $filename)%.*}.sub
#         universe = vanilla
#         executable = ${EXEC_PATH}/run_dijetAna.sh
#         +JobFlavour           = "longlunch"
#         getenv     = True
#         requirements =((OpSysAndVer =?= "AlmaLinux9") && (CERNEnvironment =?= "qa"))
#         RequestCpus = 1
#         transfer_input_files  = voms_proxy.txt
#         environment = "X509_USER_PROXY=voms_proxy.txt"
# EOF

#     jobid = 0
#     for file in ${file_list}; do
#         cat <<EOF >> pPb_${($basename $filename)%.*}.sub
#         arguments = ${file_list}/file ${sample_prefix}_PD${PD_Number}_${jobid}.root 0 0 ${isPbgoing} 0 0
#         output = condor/logs/${sample_prefix}_PD${PD_Number}_${jobid}.out
#         error = condor/logs/${sample_prefix}_PD${PD_Number}_${jobid}.err
#         log = condor/logs/${sample_prefix}_PD${PD_Number}_${jobid}.log
#         queue
# EOF
#         jobid=$((jobid+1))
#     done
#     PD_Number=$((PD_Number+1))
#     # condor_submit pPb_${filename%.*}.sub
# done





    



