from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'DijetAnaOO_Data'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = False    # <-- changed
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.scriptExe = 'run_dijetana.sh'
config.JobType.inputFiles = [
    'OODijetAna',
    'input_files.txt',
    'setup_env.sh'
]

config.JobType.scriptArgs = [
    'input_files.txt', 'output.root', '0', '1'
]

config.Data.inputDataset = 'trial.txt'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1

# You can leave these for bookkeeping; they won’t affect xrdcp
config.Data.outLFNDirBase = '/store/user/ahingraj/DijetAna/'
config.Data.publication = False
config.Site.storageSite = 'T2_CH_CERN'
