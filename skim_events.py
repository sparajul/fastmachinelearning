import ROOT ,sys
import random

inFile = ROOT.TFile.Open(sys.argv[1])
outputFile = ROOT.TFile.Open("%s_skim_events.root"%inFile.GetName().split(".")[0],"RECREATE")# inFile = 450661.root: inFile.GetName().split(".") = ['450661','root']

thisTree = inFile.ntuple #inFile.Get('dilep') are same
num_events = thisTree.GetEntries()
newTree  = thisTree.CloneTree(0)

event_indices = random.sample(range(num_events), 60334)

for event_index in event_indices:
    thisTree.GetEntry(event_index)
    newTree.Fill()

newTree.Write()
outputFile.Close()
inFile.Close()
