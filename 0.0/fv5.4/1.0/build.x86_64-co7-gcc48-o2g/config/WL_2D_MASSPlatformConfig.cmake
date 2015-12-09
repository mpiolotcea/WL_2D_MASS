# File automatically generated: DO NOT EDIT.

# Get the exported informations about the targets
get_filename_component(_dir ${CMAKE_CURRENT_LIST_FILE} PATH)
#include(${_dir}/WL_2D_MASSExports.cmake)

# Set useful properties
get_filename_component(_dir ${_dir} PATH)
set(WL_2D_MASS_INCLUDE_DIRS ${_dir}/include)
set(WL_2D_MASS_LIBRARY_DIRS ${_dir}/lib)

set(WL_2D_MASS_BINARY_PATH ${_dir}/bin ${_dir}/scripts)
set(WL_2D_MASS_PYTHON_PATH ${_dir}/python)
set(WL_2D_MASS_CONF_PATH ${_dir}/conf)
set(WL_2D_MASS_AUX_PATH ${_dir}/auxdir)

set(WL_2D_MASS_COMPONENT_LIBRARIES )
set(WL_2D_MASS_LINKER_LIBRARIES Tools)

set(WL_2D_MASS_ENVIRONMENT PREPEND;PATH;\${.}/scripts;PREPEND;PATH;\${.}/bin;PREPEND;LD_LIBRARY_PATH;\${.}/lib;PREPEND;PYTHONPATH;\${.}/python;PREPEND;PYTHONPATH;\${.}/python/lib-dynload;PREPEND;ELEMENTS_CONF_PATH;\${.}/conf;PREPEND;ELEMENTS_AUX_PATH;\${.}/auxdir;SET;WL_2D_MASS_PROJECT_ROOT;\${.}/../..;SET;TOOLSROOT;\${WL_2D_MASS_PROJECT_ROOT}/Tools)

set(WL_2D_MASS_EXPORTED_SUBDIRS)
foreach(p Tools)
  get_filename_component(pn ${p} NAME)
  if(EXISTS ${_dir}/cmake/${pn}Export.cmake)
    set(WL_2D_MASS_EXPORTED_SUBDIRS ${WL_2D_MASS_EXPORTED_SUBDIRS} ${p})
  endif()
endforeach()

set(WL_2D_MASS_OVERRIDDEN_SUBDIRS )
