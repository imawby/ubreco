
# where should the scripts/..xml file be installed?  Perhaps in bin?

art_make( BASENAME_ONLY
          LIBRARY_NAME  MicroBooNEPandora
          LIB_LIBRARIES larpandora_LArPandoraInterface
                        LArPandoraContent
                        PandoraSDK
                        PandoraMonitoring
                        art::Framework_Core
                        art::Framework_Principal
                        art::Framework_Services_Registry
                        art_root_io::tfile_support ROOT::Core
                        art_root_io::TFileService_service
                        art::Persistency_Common
                        art::Persistency_Provenance
                        art::Utilities
                        canvas::canvas
                        messagefacility::MF_MessageLogger
                        fhiclcpp::fhiclcpp
                        cetlib::cetlib
                        cetlib_except::cetlib_except
                        ROOT::Geom
          MODULE_LIBRARIES MicroBooNEPandora
          )

install_headers()
install_fhicl()
install_source()

add_subdirectory(scripts)

