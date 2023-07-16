import ROOT ,sys

inFile = ROOT.TFile.Open(sys.argv[1])
outputFile = ROOT.TFile.Open("%s_skim_smallpt.root"%inFile.GetName().split(".")[0],"RECREATE")# inFile = 450661.root: inFile.GetName().split(".") = ['450661','root']

thisTree = inFile.ntuple #inFile.Get('dilep') are same
newTree  = thisTree.CloneTree(0)
for ev in thisTree:
#    if ((ev.AntiKt10LCTopoLeadJets_pt > 200000) and (ev.AntiKt10LCTopoLeadJets_pt < 250000) and (ev.AntiKt10LCTopoLeadJets_partonTruthLabel >=1) and (ev.AntiKt10LCTopoLeadJets_partonTruthLabel <=5)):
#    if ((ev.AntiKt10LCTopoLeadJets_pt > 200000) and (ev.AntiKt10LCTopoLeadJets_pt < 250000) and (ev.AntiKt10LCTopoLeadJets_partonTruthLabel == 21)):
    #if ((ev.emtopo_partonTruthLabel_matched >=1) and (ev.emtopo_partonTruthLabel_matched <=5)):
    if ((ev.emtopo_partonTruthLabel_matched == 21)):
        newTree.Fill()

newTree.AutoSave()
