#include <iostream>
#include <vector>

#include "TFile.h"
#include "TTree.h"

#include "MyData.h"

int main() {

    // Open input file and get input tree
    TFile *input_file = TFile::Open("myfile_tree.root", "READ");
    TTree *input_tree = (TTree*)input_file->Get("ntuple");

    // Set up input branches

    std::vector<float>* input_jet_pt = nullptr;
    std::vector<float>* input_jet_eta = nullptr;
    std::vector<float>* input_jet_phi = nullptr;
    std::vector<float>* input_jet_m = nullptr;
    std::vector<int>* input_jet_nConstituents = nullptr;
    std::vector<int>* input_jet_partonTruthLabel = nullptr;
    std::vector<std::vector<float>>* input_jet_constituentEt = nullptr;
    std::vector<std::vector<float>>* input_jet_constituentEta = nullptr;
    std::vector<std::vector<float>>* input_jet_constituentPhi = nullptr;


    std::vector<float>* input_jet_truth_pt = nullptr;
    std::vector<float>* input_jet_truth_eta = nullptr;
    std::vector<float>* input_jet_truth_phi = nullptr;
    std::vector<float>* input_jet_truth_m = nullptr;
    std::vector<int>* input_jet_truth_nConstituents = nullptr;
    std::vector<int>* input_jet_truth_partonTruthLabel = nullptr;
    std::vector<std::vector<float>>* input_jet_truth_constituentEt = nullptr;
    std::vector<std::vector<float>>* input_jet_truth_constituentEta = nullptr;
    std::vector<std::vector<float>>* input_jet_truth_constituentPhi = nullptr;


    input_tree->SetBranchAddress("AntiKt4emtopoCalo422Jets_pt", &input_jet_pt);
    input_tree->SetBranchAddress("AntiKt4emtopoCalo422Jets_eta", &input_jet_eta);
    input_tree->SetBranchAddress("AntiKt4emtopoCalo422Jets_phi", &input_jet_phi);
    input_tree->SetBranchAddress("AntiKt4emtopoCalo422Jets_m", &input_jet_m);
    input_tree->SetBranchAddress("AntiKt4emtopoCalo422Jets_nConstituents", &input_jet_nConstituents);
    input_tree->SetBranchAddress("AntiKt4emtopoCalo422Jets_partonTruthLabel", &input_jet_partonTruthLabel);
    input_tree->SetBranchAddress("AntiKt4emtopoCalo422Jets_constituentEt", &input_jet_constituentEt);
    input_tree->SetBranchAddress("AntiKt4emtopoCalo422Jets_constituentEta", &input_jet_constituentEta);
    input_tree->SetBranchAddress("AntiKt4emtopoCalo422Jets_constituentPhi", &input_jet_constituentPhi);


    input_tree->SetBranchAddress("AntiKt4TruthJets_pt", &input_jet_truth_pt);
    input_tree->SetBranchAddress("AntiKt4TruthJets_eta", &input_jet_truth_eta);
    input_tree->SetBranchAddress("AntiKt4TruthJets_phi", &input_jet_truth_phi);
    input_tree->SetBranchAddress("AntiKt4TruthJets_m", &input_jet_truth_m);
    input_tree->SetBranchAddress("AntiKt4TruthJets_nConstituents", &input_jet_truth_nConstituents);
    input_tree->SetBranchAddress("AntiKt4TruthJets_partonTruthLabel", &input_jet_truth_partonTruthLabel);
    input_tree->SetBranchAddress("AntiKt4TruthJets_constituentEt", &input_jet_truth_constituentEt);
    input_tree->SetBranchAddress("AntiKt4TruthJets_constituentEta", &input_jet_truth_constituentEta);
    input_tree->SetBranchAddress("AntiKt4TruthJets_constituentPhi", &input_jet_truth_constituentPhi);



    // Create output file and output tree
    TFile *output_file = TFile::Open("output.root", "RECREATE");
    TTree *output_tree = new TTree("ntuple", "Reduced ntuple");

    // Create output variables


    float output_jet_pt = 0;
    float output_jet_eta = 0;
    float output_jet_phi = 0;
    float output_jet_m = 0;
    int output_jet_nConstituents = 0;
    int output_jet_partonTruthLabel = 0;

    std::vector<float> *output_jet_constituentEt = new std::vector<float>;
    std::vector<float> *output_jet_constituentEta = new std::vector<float>;
    std::vector<float> *output_jet_constituentPhi = new std::vector<float>;

    float output_jet_truth_pt = 0;
    float output_jet_truth_eta = 0;
    float output_jet_truth_phi = 0;
    float output_jet_truth_m = 0;
    int output_jet_truth_nConstituents = 0;
    int output_jet_truth_partonTruthLabel = 0;

    std::vector<float> *output_jet_truth_constituentEt = new std::vector<float>;
    std::vector<float> *output_jet_truth_constituentEta = new std::vector<float>;
    std::vector<float> *output_jet_truth_constituentPhi = new std::vector<float>;




    // Set up output branches

    output_tree->Branch("AntiKt4emtopoCalo422Jets_pt", &output_jet_pt, "AntiKt4emtopoCalo422Jets_pt/F");
    output_tree->Branch("AntiKt4emtopoCalo422Jets_eta", &output_jet_eta, "AntiKt4emtopoCalo422Jets_eta/F");
    output_tree->Branch("AntiKt4emtopoCalo422Jets_phi", &output_jet_phi, "AntiKt4emtopoCalo422Jets_phi/F");
    output_tree->Branch("AntiKt4emtopoCalo422Jets_m", &output_jet_m, "AntiKt4emtopoCalo422Jets_m/F");
    output_tree->Branch("AntiKt4emtopoCalo422Jets_nConstituents", &output_jet_nConstituents, "AntiKt4emtopoCalo422Jets_nConstituents/I");
    output_tree->Branch("AntiKt4emtopoCalo422Jets_partonTruthLabel", &output_jet_partonTruthLabel, "AntiKt4emtopoCalo422Jets_partonTruthLabel/I");
    output_tree->Branch("AntiKt4emtopoCalo422Jets_constituentEt", "std::vector<float>", &output_jet_constituentEt);
    output_tree->Branch("AntiKt4emtopoCalo422Jets_constituentEta", "std::vector<float>", &output_jet_constituentEta);
    output_tree->Branch("AntiKt4emtopoCalo422Jets_constituentPhi", "std::vector<float>", &output_jet_constituentPhi);

    output_tree->Branch("AntiKt4TruthJets_pt", &output_jet_truth_pt, "AntiKt4TruthJets_pt/F");
    output_tree->Branch("AntiKt4TruthJets_eta", &output_jet_truth_eta, "AntiKt4TruthJets_eta/F");
    output_tree->Branch("AntiKt4TruthJets_phi", &output_jet_truth_phi, "AntiKt4TruthJets_phi/F");
    output_tree->Branch("AntiKt4TruthJets_m", &output_jet_truth_m, "AntiKt4TruthJets_m/F");
    output_tree->Branch("AntiKt4TruthJets_nConstituents", &output_jet_truth_nConstituents, "AntiKt4TruthJets_nConstituents/I");
    output_tree->Branch("AntiKt4TruthJets_partonTruthLabel", &output_jet_truth_partonTruthLabel, "AntiKt4TruthJets_partonTruthLabel/I");
    output_tree->Branch("AntiKt4TruthJets_constituentEt", "std::vector<float>", &output_jet_truth_constituentEt);
    output_tree->Branch("AntiKt4TruthJets_constituentEta", "std::vector<float>", &output_jet_truth_constituentEta);
    output_tree->Branch("AntiKt4TruthJets_constituentPhi", "std::vector<float>", &output_jet_truth_constituentPhi);


    // Loop over input events and fill output tree
    const Long64_t num_entries = input_tree->GetEntries();
    for (Long64_t i_entry = 0; i_entry < num_entries; i_entry++) {
        input_tree->GetEntry(i_entry);

   
     // Find leading jet in event
        const std::size_t num_jets = input_jet_pt->size();
        if (num_jets == 0) continue;

        std::size_t leading_jet_index = 0;
        float leading_jet_pt = input_jet_pt->at(0);

        for (std::size_t i_jet = 1; i_jet < num_jets; i_jet++) {
            const float jet_pt = input_jet_pt->at(i_jet);
            if (jet_pt > leading_jet_pt) {
                leading_jet_index = i_jet;
                leading_jet_pt = jet_pt;
            }
        }
        const std::size_t num_truth_jets = input_jet_truth_pt->size();
        if (num_truth_jets == 0) continue;

        std::size_t leading_jet_truth_index = 0;
        float leading_jet_truth_pt = input_jet_truth_pt->at(0);

        for (std::size_t j_jet = 1; j_jet < num_truth_jets; j_jet++) {
            const float jet_truth_pt = input_jet_pt->at(j_jet);
            if (jet_truth_pt > leading_jet_truth_pt) {
                leading_jet_truth_index = j_jet;
                leading_jet_truth_pt = jet_truth_pt;
            }
        }

        // Fill output variables for leading jet

        output_jet_pt = input_jet_pt->at(leading_jet_index);
        output_jet_eta = input_jet_eta->at(leading_jet_index);
        output_jet_phi = input_jet_phi->at(leading_jet_index);
        output_jet_m = input_jet_m->at(leading_jet_index);
        output_jet_nConstituents = input_jet_nConstituents->at(leading_jet_index);
        output_jet_partonTruthLabel = input_jet_partonTruthLabel->at(leading_jet_index);

        output_jet_truth_pt = input_jet_truth_pt->at(leading_jet_truth_index);
        output_jet_truth_eta = input_jet_truth_eta->at(leading_jet_truth_index);
        output_jet_truth_phi = input_jet_truth_phi->at(leading_jet_truth_index);
        output_jet_truth_m = input_jet_truth_m->at(leading_jet_truth_index);
        output_jet_truth_nConstituents = input_jet_truth_nConstituents->at(leading_jet_truth_index);
        output_jet_truth_partonTruthLabel = input_jet_truth_partonTruthLabel->at(leading_jet_truth_index);


        const std::vector<float>& jet_constituentEt = input_jet_constituentEt->at(leading_jet_index);
        const std::vector<float>& jet_constituentEta = input_jet_constituentEta->at(leading_jet_index);
        const std::vector<float>& jet_constituentPhi = input_jet_constituentPhi->at(leading_jet_index);


        const std::vector<float>& jet_truth_constituentEt = input_jet_truth_constituentEt->at(leading_jet_truth_index);
        const std::vector<float>& jet_truth_constituentEta = input_jet_truth_constituentEta->at(leading_jet_truth_index);
        const std::vector<float>& jet_truth_constituentPhi = input_jet_truth_constituentPhi->at(leading_jet_truth_index);


        output_jet_constituentEt->clear();
        output_jet_constituentEta->clear();
        output_jet_constituentPhi->clear();

        output_jet_truth_constituentEt->clear();
        output_jet_truth_constituentEta->clear();
        output_jet_truth_constituentPhi->clear();

        output_jet_constituentEt->insert(output_jet_constituentEt->end(), jet_constituentEt.begin(), jet_constituentEt.end());
        output_jet_constituentEta->insert(output_jet_constituentEta->end(), jet_constituentEta.begin(), jet_constituentEta.end());
        output_jet_constituentPhi->insert(output_jet_constituentPhi->end(), jet_constituentPhi.begin(), jet_constituentPhi.end());

        output_jet_truth_constituentEt->insert(output_jet_truth_constituentEt->end(), jet_truth_constituentEt.begin(), jet_truth_constituentEt.end());
        output_jet_truth_constituentEta->insert(output_jet_truth_constituentEta->end(), jet_truth_constituentEta.begin(), jet_truth_constituentEta.end());
        output_jet_truth_constituentPhi->insert(output_jet_truth_constituentPhi->end(), jet_truth_constituentPhi.begin(), jet_truth_constituentPhi.end());

        // Fill output tree
        output_tree->Fill();
    }

    // Write output file and clean up
    output_file->Write();
    output_file->Close();

    input_file->Close();

    return 0;
}

