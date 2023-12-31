#ifndef __FLASHFINDERFMWKINTERFACE_CXX__
#define __FLASHFINDERFMWKINTERFACE_CXX__

//#include "cetlib/exception.h"
#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Handle.h"
#include "art/Framework/Principal/Run.h"
#include "art/Framework/Principal/SubRun.h"
#include "canvas/Utilities/InputTag.h"
#include "fhiclcpp/ParameterSet.h"
#include "messagefacility/MessageLogger/MessageLogger.h"
#include "art_root_io/TFileService.h"
#include "larcore/Geometry/Geometry.h"
#include "larcorealg/Geometry/CryostatGeo.h"
#include "larcorealg/Geometry/PlaneGeo.h"
#include "larcorealg/Geometry/OpDetGeo.h"
#include "ubcore/Geometry/UBOpReadoutMap.h"


#include "FlashFinderFMWKInterface.h"
namespace pmtana {

  size_t NOpDets() {
    ::art::ServiceHandle<geo::Geometry> geo;
    return geo->NOpDets();
  }

  size_t OpDetFromOpChannel(size_t opch) {
    ::art::ServiceHandle<geo::Geometry> geo;
    return geo->OpDetFromOpChannel(opch);
  }

  void OpDetCenterFromOpChannel(size_t opch, double *xyz) {
    ::art::ServiceHandle<geo::Geometry> geo;
    auto const tmp = geo->OpDetGeoFromOpChannel(opch).GetCenter();
    xyz[0] = tmp.X();
    xyz[1] = tmp.Y();
    xyz[2] = tmp.Z();
  }

}
#endif
