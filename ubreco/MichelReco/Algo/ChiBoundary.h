/**
 * \file ChiBoundary.h
 *
 * \ingroup MichelCluster
 * 
 * \brief Class def header for a class ChiBoundary
 *
 * @author kazuhiro
 */

/** \addtogroup MichelCluster

    @{*/
#ifndef MICHELCLUSTER_CHIBOUNDARY_H
#define MICHELCLUSTER_CHIBOUNDARY_H

#include "ubreco/MichelReco/Fmwk/BaseMichelAlgo.h"
#include <math.h>

namespace michel {
  /**
     \class ChiBoundary
  */
  class ChiBoundary : public BaseMichelAlgo {
    
  public:
    
    /// Default constructor
    ChiBoundary(){_name="ChiBoundary";}
    
    /// Default destructor
    ~ChiBoundary(){}

    /// Event resetter
    void EventReset();
    
    /// A function to identify a michel's boundary point
    bool ProcessCluster( MichelCluster& cluster,
			const std::vector<HitPt>& hits);

    //other functions
    std::vector<double> do_chi(const MichelCluster& cluster, size_t window_size);
    
    template<typename T>
    std::vector<std::vector<T> > get_windows(const std::vector<T>& the_thing,
					     const size_t window_size);
    
    std::vector<HitIdx_t> find_max_pos(const std::vector<double> chi,
				       bool forward,
				       size_t window,
				       float cutoff,
				       float rise_edge, 
				       float fall_edge, 
				       float threshold);
    
    HitIdx_t find_max_peak(const std::vector<double>& data,
			   HitIdx_t istart, 
			   HitIdx_t iend);
    
    std::pair<float,float> PedEstimate(const std::vector<double>& data,
				       bool start,
				       HitIdx_t window,
				       HitIdx_t cutoff);

    std::pair<float,float> getrms (const std::vector<double>& data,
				   HitIdx_t k,
				   HitIdx_t m,
				   HitIdx_t window) ;
    
   
    
  };
}

#endif
/** @} */ // end of doxygen group 

