#ifndef PROTODUNESELECTIONUTILS_h
#define PROTODUNESELECTIONUTILS_h

#include <iostream>
#include <vector>
#include <string>

#include <TH1.h>
#include <TGraphAsymmErrors.h>

namespace protoana{
  namespace ProtoDUNESelectionUtils{

    // Fill signal and background histograms. The event selection is done at this stage.
    TH1* FillMCBackgroundHistogram_Pions(std::string filename,
        std::string treename, std::vector<double> recoBins, std::string channel,
        std::string topo, int toponum, double endZ_cut, double minval=0.0,
        double maxval=100000.0, bool doNegativeReco=false, int doSyst=0,
        std::string systName="", double weight=1.0);

    TH1* FillMCSignalHistogram_Pions(std::string filename, std::string treename,
        std::vector<double> recoBins, std::string channel, std::string topo,
        int toponum, double minval, double maxval, double endZ_cut,
        bool doNegativeReco=false, int doSyst=0, std::string systName="",
        double weight=1.0);

    // Fill incident pions
    TH1* FillMCIncidentHistogram_Pions(std::string filename, std::string treename,
        std::vector<double> recoBins, std::string channel, std::string topo,
        int toponum, double reco_beam_endZ_cut, int doSyst=0, double weight=1.0);

    // Fill the number of truth beam pions
    TH1* FillMCTruthSignalHistogram_Pions(std::string filename, std::string treename,
        std::vector<double> truthBins, std::string channel, double weight=1.0);

    // Fill data
    TH1* FillDataHistogram_Pions(std::string filename, std::string treename,
        std::vector<double> recoBins, std::string channel,
        bool IsIncidentHisto=false);

    // Pion flux
    TH1* FillMCFlux_Pions(std::string filename, std::string treename,
        std::vector<double> Bins, int mode = 1, double weight=1.0);

    // Get number of triggers
    int GetNTriggers_Pions(std::string filename, std::string treename,
        bool IsMC=true);

    // Old method -- should remove?
    int GetVertexType( const std::vector< std::string > & processes,
        const std::vector<int> & vertex_hits_slices,
        const std::vector<std::vector<double>> & vertex_dRs,
        double cut = 5., int max_slices = 1 );

    // Remove the doSysts from the following?
    std::pair<TH1 *, TH1 *> GetMCIncidentEfficiency(
        std::string fileName, std::string treeName,
        std::vector<double> bins, double reco_beam_endZ_cut,
        bool doNegativeReco=false, int doSyst = 0, double weight = 1.);

    std::pair<TH1 *, TH1 *> GetMCInteractingEfficiency(
        std::string fileName, std::string treeName,
        std::vector<double> bins, std::string channel,
        std::string topo, int toponum, double endZ_cut, int doSyst = 0,
        double weight = 1.);

  }
}

#endif
