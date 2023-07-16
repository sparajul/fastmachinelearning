#ifndef MyData_h
#define MyData_h

#include <vector>

class MyData {
public:
    MyData();
    virtual ~MyData();
    
    std::vector<float> AntiKt4emtopoCalo422Jets_pt;
    std::vector<float> AntiKt4emtopoCalo422Jets_eta;
    std::vector<float> AntiKt4emtopoCalo422Jets_phi;
    std::vector<float> AntiKt4emtopoCalo422Jets_m;
    std::vector<int> AntiKt4emtopoCalo422Jets_nConstituents;
    std::vector<int> AntiKt4emtopoCalo422Jets_partonTruthLabel;
    std::vector<std::vector<float>> AntiKt4emtopoCalo422Jets_constituentEt;
    std::vector<std::vector<float>> AntiKt4emtopoCalo422Jets_constituentEta;
    std::vector<std::vector<float>> AntiKt4emtopoCalo422Jets_constituentPhi;

    std::vector<float> AntiKt4TruthJets_pt;
    std::vector<float> AntiKt4TruthJets_eta;
    std::vector<float> AntiKt4TruthJets_phi;
    std::vector<float> AntiKt4TruthJets_m;
    std::vector<int> AntiKt4TruthJets_nConstituents;
    std::vector<int> AntiKt4TruthJets_partonTruthLabel;
    std::vector<std::vector<float>> AntiKt4TruthJets_constituentEt;
    std::vector<std::vector<float>> AntiKt4TruthJets_constituentEta;
    std::vector<std::vector<float>> AntiKt4TruthJets_constituentPhi;
};

#endif // MyData_h

