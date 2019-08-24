from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'RelValZpTT_13UP18_PUpmx25ns_106X_CMSSW_10_6_1'
config.General.workArea = 'RelValZpTT_1500_13UP18_MINI_CMSSW_10_6_1'

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'test_2018.py'

config.section_("Data")
config.Data.inputDataset = '/RelValZpTT_1500_13UP18/CMSSW_10_6_1-PUpmx25ns_106X_upgrade2018_realistic_v6_ul18hlt_premix_hs-v1/MINIAODSIM'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
#config.Data.totalUnits = -1
config.Data.outLFNDirBase = '/store/user/vmuralee/TagAndProbe/genlevel/'
config.Data.publication = False
#config.Data.publishDataName = 'CRAB3_tutorial_MC_analysis_test1'
config.Data.allowNonValidInputDataset = True
config.section_("Site")
config.Site.storageSite = 'T2_IN_TIFR'
