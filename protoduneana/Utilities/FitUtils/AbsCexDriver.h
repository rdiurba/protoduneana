#ifndef ABSCEXDRIVER_hh
#define ABSCEXDRIVER_hh

#include "ThinSliceDriver.h"
#include "TH2D.h"
#include "TFile.h"
#include <map>

namespace protoana {
class AbsCexDriver : public ThinSliceDriver {
 public:
  AbsCexDriver(const fhicl::ParameterSet & extra_options);
  virtual ~AbsCexDriver();

  void BuildDataHists(
    TTree * tree, ThinSliceDataSet & data_set, double & flux) override;
  void BuildFakeData(
    TTree * tree,
    std::map<int, std::vector<std::vector<ThinSliceSample>>> & samples,
    const std::map<int, bool> & signal_sample_checks,
    ThinSliceDataSet & data_set, double & flux,
    std::map<int, std::vector<double>> & sample_scales) override;
  void FakeDataSampleScales(
    TTree * tree,
    std::map<int, std::vector<std::vector<ThinSliceSample>>> & samples,
    const std::map<int, bool> & signal_sample_checks,
    ThinSliceDataSet & data_set, double & flux,
    std::map<int, std::vector<double>> & sample_scales);
  void FakeDataBinnedScales(
    TTree * tree,
    std::map<int, std::vector<std::vector<ThinSliceSample>>> & samples,
    const std::map<int, bool> & signal_sample_checks,
    ThinSliceDataSet & data_set, double & flux,
    std::map<int, std::vector<double>> & sample_scales);
  void FakeDataG4RW(
    TTree * tree,
    std::map<int, std::vector<std::vector<ThinSliceSample>>> & samples,
    const std::map<int, bool> & signal_sample_checks,
    ThinSliceDataSet & data_set, double & flux,
    std::map<int, std::vector<double>> & sample_scales);

  void BuildMCSamples(
      //TTree * tree,
      const std::vector<ThinSliceEvent> & events,
      std::map<int, std::vector<std::vector<ThinSliceSample>>> & samples,
      const std::map<int, bool> & signal_sample_checks,
      std::map<int, double> & nominal_fluxes,
      std::map<int, std::vector<std::vector<double>>> & fluxes_by_sample,
      std::vector<double> & beam_energy_bins) override;

  void RefillMCSamples(
      //TTree * tree,
      const std::vector<ThinSliceEvent> & events,
      std::map<int, std::vector<std::vector<ThinSliceSample>>> & samples,
      const std::map<int, bool> & signal_sample_checks,
      std::vector<double> & beam_energy_bins,
      const std::map<int, std::vector<double>> & signal_pars,
      const std::map<int, double> & flux_pars,
      const std::map<std::string, ThinSliceSystematic> & syst_pars,
      bool fill_incident = false) override;

  void BuildSystSamples(
      TTree * tree,
      std::map<int, std::vector<std::vector<ThinSliceSample>>> & samples,
      const std::map<int, bool> & signal_sample_checks,
      std::vector<double> & beam_energy_bins) override;
  
  void SystRoutine_G4RW(
      TTree * tree,
      std::map<int, std::vector<std::vector<ThinSliceSample>>> & samples,
      const std::map<int, bool> & signal_sample_checks,
      const fhicl::ParameterSet & routine);

  void SystRoutine_dEdX_Cal(
      TTree * tree,
      std::map<int, std::vector<std::vector<ThinSliceSample>>> & samples,
      const std::map<int, bool> & signal_sample_checks,
      const fhicl::ParameterSet & routine,
      std::vector<double> & beam_energy_bins);

  std::pair<double, size_t> CalculateChi2(
      std::map<int, std::vector<std::vector<ThinSliceSample>>> & samples,
      ThinSliceDataSet & data_set) override;
  void CompareSelections(
      std::map<int, std::vector<std::vector<ThinSliceSample>>> & samples,
      ThinSliceDataSet & data_set,
      TFile & output_file,
      std::vector<std::pair<int, int>> plot_style,
      bool plot_rebinned,
      bool post_fit, int nPars) override;

  void GetCurrentHists(
      std::map<int, std::vector<std::vector<ThinSliceSample>>> & samples,
      ThinSliceDataSet & data_set,
      std::map<int, std::vector<TH1*>> & throw_hists,
      bool plot_rebinned) override;

  virtual void GetCurrentTruthHists(
      std::map<int, std::vector<std::vector<ThinSliceSample>>> & samples,
      std::map<int, std::vector<TH1*>> & hists,
      std::map<int, std::vector<TH1*>> & inc_hists,
      std::map<int, std::vector<TH1*>> & xsec_hists,
      const std::vector<int> & incident_samples,
      const std::map<int, std::vector<double>> & signal_bins) override;

  void PlotThrows(
    ThinSliceDataSet & data_set, std::map<int, std::vector<TH1*>> & throw_hists,
    std::map<int, std::vector<std::vector<ThinSliceSample>>> & samples,
    size_t nThrows,
    std::map<int, std::vector<TH1*>> & truth_throw_hists,
    std::map<int, std::vector<TH1*>> & truth_inc_hists,
    std::map<int, std::vector<TH1*>> & truth_xsec_hists,
    std::map<int, TH1*> & best_fit_incs,
    std::map<int, TH1*> & best_fit_xsecs,
    std::map<int, TH1*> & nominal_incs,
    std::map<int, TH1*> & nominal_xsecs,
    TFile & output_file, bool plot_rebinned,
    std::map<int, std::vector<double>> * sample_scales = 0x0) override;

 private:
   TH2D * fEndSlices;
   TFile * fIn;
   std::map<int, double> fMeans;

   double fEnergyFix;
   bool fDoEnergyFix;

   double fPitch;
   double fZ0;
   double fEndZCut;
   std::string fSliceMethod;
   int fSliceCut;
};
}
#endif
