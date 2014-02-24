# ###########################################################################
# Copyright: 2013 iCub Facility, Istituto Italiano di Tecnologia
# Author: Francesco Giovannini
# CopyPolicy: Released under the terms of the GNU GPL v2.0.
# ###########################################################################

# ###########################################################################
# ###########################################################################
# CMake FIND file for the proprietary NIDAQmx Linux library (NIDAQmxBase).
# 
# Try to find NIDAQmxBase
# Once done this will define
#   LIBNIDAQMXBASE_FOUND - System has NIDAQmxBase
#   LIBNIDAQMXBASE_LIBRARY - The NIDAQmxBase library
#   LIBNIDAQMXBASE_INCLUDE_DIR - The NIDAQmxBase include file
# ###########################################################################
# ###########################################################################

# ###########################################################################
# Find installed library using CMake functions
find_library(LIBNIDAQMXBASE_LIBRARY 
			NAMES "nidaqmxbase"
            PATHS /usr/local)
            
find_path(LIBNIDAQMXBASE_INCLUDE_DIR 
			NAMES "NIDAQmxBase.h"
            PATHS /usr/local)
          
# Handle the QUIETLY and REQUIRED arguments and set LIBNIDAQMXBASE_FOUND to TRUE if all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LibNIDAQmxBase  DEFAULT_MSG
                                  LIBNIDAQMXBASE_LIBRARY LIBNIDAQMXBASE_INCLUDE_DIR)
# ###########################################################################

    
# ###########################################################################
# Mark as done
mark_as_advanced(LIBNIDAQMXBASE_LIBRARY LIBNIDAQMXBASE_INCLUDE_DIR)
# ###########################################################################
