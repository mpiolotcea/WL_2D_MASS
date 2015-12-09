# File automatically generated: DO NOT EDIT.

# Compute the installation prefix relative to this file.
get_filename_component(_IMPORT_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)
get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)

add_library(Tools SHARED IMPORTED)
set_target_properties(Tools PROPERTIES
  REQUIRED_INCLUDE_DIRS "ElementsKernel;Boost;Log4CPP"
  REQUIRED_LIBRARIES "fftw3;ElementsKernel;dl;/usr/lib64/libboost_filesystem-mt.so;/usr/lib64/libboost_thread-mt.so;/usr/lib64/libboost_program_options-mt.so;/usr/lib64/libboost_system-mt.so;/usr/lib64/libboost_regex-mt.so;/usr/lib64/liblog4cpp.so"
  IMPORTED_SONAME "libTools.so"
  IMPORTED_LOCATION "${_IMPORT_PREFIX}/lib/libTools.so"
  )
add_executable(ShearInversions_test IMPORTED)
set_target_properties(ShearInversions_test PROPERTIES
  IMPORTED_LOCATION "${_IMPORT_PREFIX}/bin/ShearInversions_test"
  )
set(Tools_DEPENDENCIES ElementsKernel)
set(Tools_VERSION 1.0)
