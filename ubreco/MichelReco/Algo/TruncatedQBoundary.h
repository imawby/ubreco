/**
 * \file TruncatedQBoundary.h
 *
 * \ingroup MichelCluster
 * 
 * \brief Class def header for a class TruncatedQBoundary
 *
 * @author kazuhiro
 */

/** \addtogroup MichelCluster

    @{*/
#ifndef MICHELCLUSTER_TRUNCATEDQBOUNDARY_H
#define MICHELCLUSTER_TRUNCATEDQBOUNDARY_H

#include "ubreco/MichelReco/Fmwk/BaseMichelAlgo.h"
#include <algorithm>

namespace michel {
  /**
     \class TruncatedQBoundary
  */
  class TruncatedQBoundary : public BaseMichelAlgo {
    
  public:
    
    /// Default constructor
    TruncatedQBoundary()
      : _maxDistance(20),
      _covariance_dip_cutoff(0.9),
      _covariance_window(11),
      _n_window_size(15),
      _p_above(0.25),
      _window_cutoff(3),
      _edgefix(3)
	{_name="TruncatedQBoundary";}
    
    /// Default destructor
    ~TruncatedQBoundary(){}
    
    /// Event resetter
    void EventReset();
    
    /// A function to identify a michel's boundary point
    bool ProcessCluster(MichelCluster& cluster,
			const std::vector<HitPt>& hits);
    
    /// setter function for max distance between min in dQds
    /// and max in dQ
    void SetMaxDistanceTruncatedPeaks(size_t n) { _maxDistance = n; }

    /// setter function for strength SINGLE dip in covariance must be
    /// 0.9 is default
    void SetCovarianceDipCutoff(double d)    { _covariance_dip_cutoff = d; }

    /// setter function for window size for calculating covariance and slope
    /// this in principle (and currently is) different from truncated Q window size
    void SetCovarianceWindowSize(size_t s)   { _covariance_window = s; }

    /// setter function for window size used to calculated truncated Q
    void SetTruncatedQWindowSize(size_t s)   { _n_window_size     = s; }

    /// setter function for fraction of points to keep in truncated Q calc
    void SetPAbove(double p)                 { _p_above = p; }

    // setter function for truncated Q window cutoff, windows less than
    // this size have no truncation
    void SetMinWindowSize(size_t w)          { _window_cutoff = w; }

    /// setter function for mitigating edge effect, this number of points on the
    /// edge set equal to truncatedQ[_edgefix], maybe 0 is best I don't know
    
    void SetEdgeEffectFix(size_t e)          { _edgefix = e; }
    
  private:

    /// number of hits that sets max allowed distance between
    /// min in trunc. dQdx and max in trunc. dQ
    /// if the min and max are more than this number of hits
    /// apart -> do not create a michel
    size_t _maxDistance;
    
    /// single dip in covariance strenght, must be below this value to
    /// be considered a dip
    double _covariance_dip_cutoff;
    
    /// Sliding window size for calculating covariance/slope window
    size_t _covariance_window;

    /// Sliding window size for calculating truncated Q window
    size_t _n_window_size;
    
    /// Fraction of points to keep in truncated Q calculation, for example
    /// a value of 0.25 means we keep 25% of the lowest points in the specified
    /// window size, then do mean
    double _p_above;

    /// Minimum window size to apply truncation, if window size is smaller than this
    /// then we keep all the points 
    size_t  _window_cutoff;
    
    /// Try to correct edge effect by setting this number of points equal
    /// on both edges
    size_t _edgefix;
     
  };
}

#endif
/** @} */ // end of doxygen group 

