art_make(
	  LIB_LIBRARIES
			art::Framework_Core
			art::Framework_Services_Registry
			art::Framework_Principal art::Framework_Core
			larcorealg_Geometry lardataobj_RecoBase
			larcorealg_Geometry
			larcore_Geometry_Geometry_service
                        lardataalg_DetectorInfo
			art::Utilities
                        canvas::canvas
                        messagefacility::MF_MessageLogger
			art::Framework_Services_Registry
			art_root_io::tfile_support
                        ROOT::Core
			messagefacility::MF_MessageLogger
			cetlib::cetlib
                        cetlib_except::cetlib_except

        )

install_fhicl()
install_headers()
install_source()
