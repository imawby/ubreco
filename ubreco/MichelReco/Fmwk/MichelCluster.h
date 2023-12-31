/**
 * \file MichelCluster.h
 *
 * \ingroup michel_filter
 *
 * \brief Class def header for a class MichelCluster
 *
 * @author vgenty
 */

/** \addtogroup michel_filter

    @{*/
#ifndef MICHELCLUSTER_H
#define MICHELCLUSTER_H

//C++
#include <iostream>
#include <vector>
#include "ubreco/MichelReco/Fmwk/MichelTypes.h"
#include "ubreco/MichelReco/Fmwk/MichelConstants.h"
#include "ubreco/MichelReco/Fmwk/Michel.h"
#include "ubreco/MichelReco/Fmwk/HitPt.h"
#include "ubreco/MichelReco/Fmwk/ColorPrint.h"

namespace michel {
/**
   \class MichelCluster
   User defined class MichelCluster ... these comments are used to generate
   doxygen documentation!
*/

class MichelCluster : public ColorPrint {
    friend class MichelRecoManager;
    //friend class MichelCluster;
public:
    /// Default constructor
    MichelCluster(size_t min_nhits = 0,
                  double d_cutoff  = kMAX_DOUBLE );

    /// Alternative ctor from hit list reference
    MichelCluster(const std::vector<HitPt>&,
                  size_t min_nhits = 0,
                  double d_cutoff  = kMAX_DOUBLE );

#ifndef __CINT__ // CINT (ROOT5) cannot understand std::move
    /// Copy ctor
    //MichelCluster(const MichelCluster& rhs) = default;

    /// Alternative ctor from hit list reference
    MichelCluster(std::vector<HitPt>&&,
                  size_t min_nhits = 0,
                  double d_cutoff  = kMAX_DOUBLE );

    /// Alternative ctor from michel
    //MichelCluster(const MichelCluster&& rhs);
#endif

    /// Default destructor
    virtual ~MichelCluster() {}

    /// ID getter
    ClusterID_t ID() const { return _id; }

    /// Hit list setter
    void SetHits(const std::vector<michel::HitPt>& hits);

#ifndef __CINT__
    /// Hit list setter
    void SetHits(std::vector<michel::HitPt>&& hits);
#endif

    /// Verbosity level
    void SetVerbosity(msg::MSGLevel_t level)
    { _verbosity = level; }

    //
    // Operator attributes
    //
    // Binary addition
    MichelCluster operator+(const MichelCluster& other) const;

    /// Unary addition
    MichelCluster& operator+=(const MichelCluster& other);

    /// Find the closest hit to the reference from the cluster hit list
    const HitPt& ClosestHit(const HitPt& ref);

    /// Dumps information about this cluster
    void Dump() const;

    //
    // Data attributes
    //
    // Basic hit-based parameters
    std::vector<HitPt> _hits; ///< List of hits
    std::vector<HitPt> _all_hits; /// all hits in original cluster
    HitPt _start;             ///< Start point
    HitPt _end;               ///< End point

    /// boolean indicating if michel is "forward" or "backwards"
    /// in the hit-list
    // forward -> the latter hits are those of the michel
    // backwards -> the first few his are those of the michel
    bool _forward;

    // Ordered per-hit or in-between-hit quantities
    std::vector<HitIdx_t> _ordered_pts; ///< Distance ordered points
    std::vector<double>   _ds_v;        ///< Distance in-between neighboring hits (follows _ordered_pts)
    std::vector<double>   _s_v;         ///< Cumulative neighboring distance between hits

    //
    // Attributes to be filled by external algorithms
    //
    HitIdx_t _boundary;   ///< Michel/Muon boundary point (not necessarily michel start exactly)
    int GetBoundary() { return (int)_boundary; }
    Michel _michel;       ///< Michel
    std::vector<double>   _chi2_v;      ///< Local linear chi2 fit
    std::vector<double>   _t_mean_v;    ///< Truncated mean
    std::vector<double>   _t_dqds_v;    ///< Truncated dqds
    std::vector<double>   _dirs_v;      ///< vector of slope @ hit point

    // mark the position of the Bragg Peak
    // and of the end of the MIP region
    HitIdx_t _braggPeak;
    HitIdx_t _MIPend;

    //
    // Configurations
    //
    msg::MSGLevel_t _verbosity; ///< Verbosity level
    size_t _min_nhits;          ///< Minimum # of hits
    double _d_cutoff;           ///< Distance cut off value

    // boolean to store whether this cluster has been found to have a michel or not
    bool _has_michel;

    //
    // Speak for a diff
    //
    std::string Diff(const MichelCluster& rhs) const;

    /// set input cluster index (if only 1 index)
    void setInputCluster(const std::pair<unsigned short, size_t>& clus_info)
    {
      _cluster_idx_v.clear();
      _cluster_idx_v.push_back(clus_info.first);
    }

    /// set input cluster index list
    void setInputClusterIndex_v(const std::vector<unsigned short>& clus_v)
    { _cluster_idx_v = clus_v; }

    /// get input cluster index list
    std::vector<unsigned short> getInputClusterIndex_v() const { return _cluster_idx_v; }

protected:

    /// ID for a michel
    ClusterID_t _id;

    /// vector of original cluster indices being used 
    std::vector<unsigned short> _cluster_idx_v;

    //
    // Private attribute functions
    //
    /// Process set hits and do ordering
    void ProcessHits();

};

/// A set of MichelCluster
typedef std::vector<michel::MichelCluster> MichelClusterArray;
}
#endif
/** @} */ // end of doxygen group

