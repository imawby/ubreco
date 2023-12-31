/**
 * \file Chi2Match.h
 *
 * \ingroup Algorithms
 * 
 * \brief Class def header for a class Chi2Match
 *
 * @author kazuhiro
 */

/** \addtogroup Algorithms

    @{*/
#ifndef CHI2MATCH_H
#define CHI2MATCH_H

#include <iostream>
#include "ubreco/LLSelectionTool/OpT0Finder/Base/FlashMatchFactory.h"
#include "ubreco/LLSelectionTool/OpT0Finder/Base/BaseFlashMatch.h"
#include "ubreco/LLSelectionTool/OpT0Finder/Base/OpT0FinderException.h"
#include <TMinuit.h>
#include <cmath>
#include <numeric>
#include <TMath.h>

namespace flashana {
  /**
     \class Chi2Match
     User defined class Chi2Match ... these comments are used to generate
     doxygen documentation!
  */
  class Chi2Match : public BaseFlashMatch {

  public:

    /// Default ctor (throws exception, use alternative)
    Chi2Match();

    /// Valid ctor
    Chi2Match(const std::string);
    
    /// Default destructor
    ~Chi2Match(){}

    /// Core function: execute matching
    FlashMatch_t Match(const QCluster_t&, const Flash_t&);

    const Flash_t& ChargeHypothesis(const double);
    const Flash_t& Measurement() const;

    double Chi2(const flashana::Flash_t&,
		const flashana::Flash_t&);

  protected:

    void _Configure_(const Config_t &pset);
    
  private:

    static Chi2Match* _me;
    
    double _normalize; ///< Noramalize hypothesis PE spectrum

    std::vector<double>  _penalty_threshold_v;

    flashana::QCluster_t _raw_trk;
    flashana::Flash_t    _hypothesis;  ///< Hypothesis PE distribution over PMTs
    flashana::Flash_t    _measurement; ///< Flash PE distribution over PMTs

    double _current_chi2;
    double _current_llhd;
  };

  /**
     \class flashana::Chi2MatchFactory
  */
  class Chi2MatchFactory : public FlashMatchFactoryBase {
  public:
    /// ctor
    Chi2MatchFactory() { FlashMatchFactory::get().add_factory("Chi2Match",this); }
    /// dtor
    ~Chi2MatchFactory() {}
    /// creation method
    BaseFlashMatch* create(const std::string instance_name) { return new Chi2Match(instance_name); }
  };
  
}

#endif
/** @} */ // end of doxygen group 

