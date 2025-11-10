#!/bin/bash
CMS_PATH=${HOME}/private/analysis/CMSSW_13_0_5/src
# CMS_PATH=${HOME}/analysis/jetAnalysis/

cd ${CMS_PATH}
# eval 'cmsenv'

#Change the path to the CMSSW_13_0_5 directory
EXEC_PATH=${HOME}/private/analysis/CMSSW_13_0_5/src/cmsdijet
# EXEC_PATH=${HOME}/analysis/jetAnalysis/

DataSet=$1
files_per_job=$2
doBuild=$3

if [ "$doBuild" -eq 1 ]; then
    echo "Building the code"
    cd ${EXEC_PATH}/build
    make
    cd ${EXEC_PATH}
    mkdir -p "executions_dir"
    cp -r "$EXEC_PATH/build/OODijetAna" "executions_dir"
fi

if [ "$DataSet" -eq 1 ]; then
    echo "PYTHIA Datasset is selected"  
    cd ${EXEC_PATH}   
    sample_prefix="PYTHIA8_5p36TeV"
    input_files_list="${EXEC_PATH}/files_input/OO5360/MC/Unembedded/"
    output_path="/eos/user/a/ahingraj/outputs/OO_MC_Unembedded/"
    isMC=1
    isEmbedded=0

fi

if [ "$DataSet" -eq 2 ]; then
    echo "PYTHIA + HIJING Datasset is selected"  
    cd ${EXEC_PATH}   
    sample_prefix="PYTHIA_HIJING_5p36TeV"
    input_files_list="${EXEC_PATH}/files_input/OO5360/MC/Embedded/"
    output_path="/eos/user/a/ahingraj/outputs/OO_MC_Embedded/"
    isMC=1
    isEmbedded=1

fi

if [ "$DataSet" -eq 3 ]; then
    echo "OO Data is Selected"    
    cd ${EXEC_PATH}   
    sample_prefix="OO_Data"
    input_files_list="${EXEC_PATH}/files_input/OO5360/DATA/"
    output_path="/eos/user/a/ahingraj/outputs/OO_Data/"
    isMC=0
    isEmbedded=1
fi

if [ "$DataSet" -gt 3 ]; then
    echo "No Data Set Selected. Use numbers from 1 to 5"
    exit 1
fi

echo "Input File List : ${input_files_list}"

mkdir -p processing/condor/logs

PD_Number=1
for filename in ${input_files_list}/*.txt; do
    echo "Processing file: $(basename "$filename")"
    echo "$PWD"
    processing/split_files.sh ${input_files_list} $(basename "$filename") $files_per_job
    file_list=$(processing/split_files.sh ${input_files_list} $(basename "$filename") $files_per_job)
    subfile=$(basename "$filename")
    echo "Submission file with name OO_${subfile%.*}.sub is Created"
    cat <<EOF > processing/OO_${subfile%.*}.sub
        universe        = vanilla
        executable      = ${EXEC_PATH}/processing/run_DijetAnaOO.sh
        +JobFlavour     = "longlunch"
        getenv          = True
        requirements    =((OpSysAndVer =?= "AlmaLinux9") && (CERNEnvironment =?= "qa"))
        RequestCpus     = 1
        transfer_input_files  = ${EXEC_PATH}/processing/voms_proxy.txt
        environment     = "X509_USER_PROXY=${EXEC_PATH}/processing/voms_proxy.txt"
        


EOF
    jobid=0
    for file in ${file_list}/*.txt; do
        cat <<EOF >> processing/OO_${subfile%.*}.sub

	    arguments   = ${file_list}/$(basename "$file") ${output_path}${sample_prefix}_PD${PD_Number}_${jobid}.root ${isMC} ${isEmbedded}
        output      = processing/condor/logs/${sample_prefix}_PD${PD_Number}_${jobid}.out
        error       = processing/condor/logs/${sample_prefix}_PD${PD_Number}_${jobid}.err
        log         = processing/condor/logs/${sample_prefix}_PD${PD_Number}_${jobid}.log
        queue

EOF
        jobid=$((jobid+1))
    done
    PD_Number=$((PD_Number+1))
    condor_submit processing/OO_${subfile%.*}.sub
done





    



