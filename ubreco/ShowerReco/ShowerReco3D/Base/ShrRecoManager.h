/**
 * \file ShrRecoManager.h
 *
 * \ingroup ShowerReco3D
 *
 * \brief Class def header for a class ShrRecoManager
 *
 * @author kazuhiro
 */

/** \addtogroup ShowerReco3D

    @{*/
#ifndef SHOWERRECO_SHRRECOMANAGER_H
#define SHOWERRECO_SHRRECOMANAGER_H

#include <iostream>
#include <TFile.h>
#include "ShowerRecoException.h"
#include "ShowerRecoModuleBase.h"
#include "ShowerAnaBase.h"
#include "TStopwatch.h"
namespace util {
  class GeometryUtilities;
}

namespace showerreco {

typedef std::vector<std::vector<unsigned int> > ClusterAss_t;

//typedef std::vector< larutil::Hit2D> PxHitSet_t;

/**
   \class ShrRecoManager
   User defined class ShrRecoManager ... these comments are used to generate
   doxygen documentation!
*/
class ShrRecoManager {

public:

  /// Default constructor
  ShrRecoManager();

  /// Default destructor
  ~ShrRecoManager() {}

  /// Add shower reconstruction algorithm
  void AddAlgo(std::unique_ptr<showerreco::ShowerRecoModuleBase> alg) { _alg_v.push_back(std::move(alg)); }

  /// Add shower analysis class
  void AddAna(ShowerAnaBase* ana) { _ana_v.push_back(ana); }

  void Reset();

  /**
   * @brief Reconstruct showers
   */
  void Reconstruct (util::GeometryUtilities const& gser,
                    std::vector< ::showerreco::Shower_t>& showers);
  
  /**
     Reconstruct one shower
   */
  ::showerreco::Shower_t RecoOneShower(util::GeometryUtilities const& gser,
                                       const ::protoshower::ProtoShower& proto_shower);

  /**
     Finalize: provide TFile access so that anything that needs to be stored can be stored
  */
  void Finalize(TFile* fout = nullptr);

  // initalize function
  void Initialize();

  /**
     @brief set clusters for the current event
   */
  void SetProtoShowers(const std::vector< ::protoshower::ProtoShower >& proto_showers)
  { _proto_showers = proto_showers; }

  /**
   * @brief Prints the module list
   * @details Prints out the module list in the order in which they will run, nicely formatted.
   */
    void PrintModuleList();

    /**
     * @brief Set the debug option
     * @details Debug mode prints the changes in the shower_t object after each module is called.
     * Modules are expected to have their own debug mode that is activated separately.
     *
     * @param b true or false to turn on or off debug mode.  Default for the whole class is off, default for this function is on
     */
    void SetDebug(bool b = true) {_debug = b;}

    /**
     * @brief set verbosity mode
     */
    void SetVerbose(bool b = true) { _verbose = b; }

    
    /**
     */
    void Clear() { _alg_v.clear(); }

 private:
    
    bool _debug;
    bool _verbose;

    /// Shower reconstruction algorithm
    std::vector< std::unique_ptr<::showerreco::ShowerRecoModuleBase> > _alg_v;
    
    /// Shower analysis code
    std::vector< ::showerreco::ShowerAnaBase* > _ana_v;
    
    void Process(const ClusterAss_t& ass,
		 std::vector< ::showerreco::Shower_t >& showers);
    
    // vector of input clusters to be used for reconstruction
    std::vector< ::protoshower::ProtoShower > _proto_showers;
    
    void Reset(Shower_t& result);
    
    void printChanges(const Shower_t & localCopy,
		      const Shower_t result,
		      std::string moduleName);
    
    // Time profilers
    TStopwatch _watch; ///< For profiling
    std::vector<double> _alg_time_v; ///< Overall time for processing
    std::vector<size_t> _alg_ctr_v;  ///< Overall number of clusters processed by algo;
    
};
}

#endif
/** @} */ // end of doxygen group
