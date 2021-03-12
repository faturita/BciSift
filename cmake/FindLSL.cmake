SET(LSL_ROOT /home/shipu/facu/pf/libs/liblsl-1.14.0)

include(FindPackageHandleStandardArgs)
include(SelectLibraryConfigurations)
find_path(LSL_INCLUDE_DIR
          NAMES lsl
          PATHS ${LSL_ROOT}
          DOC "LSL include directory")
find_library(LSL_LIBRARY_RELEASE
             NAMES lsl
             PATHS ${LSL_ROOT}/bin/glnxa64
             DOC "LSL library file (release version)")

mark_as_advanced(LSL_INCLUDE_DIR
    LSL_LIBRARY_RELEASE)

set(LSL_LIBRARIES ${LSL_LIBRARY})
set(LSL_INCLUDE_DIRS ${LSL_INCLUDE_DIR}) 

# find_package_handle_standard_args(LSL
#                                   FOUND_VAR LSL_FOUND
#                                   REQUIRED_VARS LSL_LIBRARIES LSL_INCLUDE_DIRS)

