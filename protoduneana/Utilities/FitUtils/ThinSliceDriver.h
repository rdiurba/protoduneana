#ifndef THINSLICEDRIVER_hh
#define THINSLICEDRIVER_hh

#include <map>
#include <vector>

#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"

#include "ThinSliceSample.h"
#include "ThinSliceDataSet.h"

#include "fhiclcpp/ParameterSet.h"

namespace protoana {
class ThinSliceDriver {
 public:
  ThinSliceDriver(const fhicl::ParameterSet & extra_options);
  virtual ~ThinSliceDriver();

  virtual void BuildDataHists(
    TTree * tree, ThinSliceDataSet & data_set, double & flux) = 0;

  virtual void BuildFakeData(
    TTree * tree,
    std::map<int, std::vector<std::vector<ThinSliceSample>>> & samples,
    const std::map<int, bool> & signal_sample_checks,
    ThinSliceDataSet & data_set, double & flux,
    std::map<int, std::vector<double>> & sample_scales) = 0;

  virtual void BuildMCSamples(
      TTree * tree,
      std::map<int, std::vector<std::vector<ThinSliceSample>>> & samples,
      const std::map<int, bool> & signal_sample_checks,
      std::map<int, double> & nominal_fluxes,
      std::map<int, std::vector<std::vector<double>>> & fluxes_by_sample,
      std::vector<double> & beam_energy_bins) = 0;

  virtual void BuildSystSamples(
      TTree * tree,
      std::map<int, std::vector<std::vector<ThinSliceSample>>> & samples,
      const std::map<int, bool> & signal_sample_checks) = 0;

  virtual std::pair<double, size_t> CalculateChi2(
      std::map<int, std::vector<std::vector<ThinSliceSample>>> & samples,
      ThinSliceDataSet & data_set) = 0;

  virtual void CompareSelections(
      std::map<int, std::vector<std::vector<ThinSliceSample>>> & samples,
      ThinSliceDataSet & data_set,
      TFile & output_file,
      std::vector<std::pair<int, int>> plot_style,
      bool plot_rebinned,
      bool post_fit) = 0;

  virtual void GetCurrentHists(
      std::map<int, std::vector<std::vector<ThinSliceSample>>> & samples,
      ThinSliceDataSet & data_set,
      std::map<int, std::vector<TH1*>> & hists,
      bool plot_rebinned) = 0;

  virtual void GetCurrentTruthHists(
      std::map<int, std::vector<std::vector<ThinSliceSample>>> & samples,
      std::map<int, std::vector<TH1*>> & hists) = 0;

  virtual void PlotThrows(
    ThinSliceDataSet & data_set, std::map<int, std::vector<TH1*>> & throw_hists,
    std::map<int, std::vector<std::vector<ThinSliceSample>>> & samples,
    std::map<int, std::vector<TH1*>> & truth_throw_hists,
    TFile & output_file, bool plot_rebinned,
    std::map<int, std::vector<double>> * sample_scales = 0x0) = 0;

  /*virtual void PostFitThrows(
      std::map<int, std::vector<std::vector<ThinSliceSample>>> & samples,
      ThinSliceDataSet & data_set,
      TH1D & pars,
      TH2D & cov,
      TFile & output_file,
      std::vector<std::pair<int, int>> plot_style,
      bool plot_rebinned) = 0;*/

  void CompareDataMC(
      std::map<int, std::vector<std::vector<ThinSliceSample>>> & samples,
      ThinSliceDataSet & data_set,
      TFile & output_file,
      std::vector<std::pair<int, int>> plot_style,
      bool plot_rebinned = false,
      bool post_fit = false);

  std::pair<int, int> GetColorAndStyle(
      size_t i, const std::vector<std::pair<int, int>> & plot_style);
 protected:
  fhicl::ParameterSet fExtraOptions;
 private:
};
}
#endif
