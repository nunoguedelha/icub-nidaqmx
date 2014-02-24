# ###########################################################################
# Copyright: 2013 iCub Facility, Istituto Italiano di Tecnologia
# Author: Francesco Giovannini
# CopyPolicy: Released under the terms of the GNU GPL v2.0.
# ###########################################################################

# ###########################################################################
# ###########################################################################
# CMake FIND file for the proprietary NIDAQmx Windows library (NIDAQmx).
# 
# Try to find NIDAQmx
# Once done this will define
#   LIBNIDAQMX_FOUND - System has NIDAQmx
#   LIBNIDAQMX_LIBRARY - The NIDAQmx library
#   LIBNIDAQMX_INCLUDE_DIR - The NIDAQmx include file
# ###########################################################################
# ###########################################################################

# ###########################################################################
# Useful variables
list(APPEND NIDAQMX_ROOT "C:/Program Files (x86)/National Instruments/NI-DAQ/DAQmx ANSI C Dev")
list(APPEND NIDAQMX_ROOT "C:/Program Files/National Instruments/NI-DAQ/DAQmx ANSI C Dev")

# Find installed library using CMake functions
find_library(LIBNIDAQMX_LIBRARY 
			NAMES "NIDAQmx"
            PATHS ${NIDAQMX_ROOT}
            PATH_SUFFIXES "lib/msvc")
            
find_path(LIBNIDAQMX_INCLUDE_DIR 
			NAMES "NIDAQmx.h"
            PATHS ${NIDAQMX_ROOT}
            PATH_SUFFIXES "include")
          
# Handle the QUIETLY and REQUIRED arguments and set LIBNIDAQMX_FOUND to TRUE if all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LibNIDAQmx  DEFAULT_MSG
                                  LIBNIDAQMX_LIBRARY LIBNIDAQMX_INCLUDE_DIR)
# ###########################################################################

    
# ###########################################################################
# Mark as done
mark_as_advanced(LIBNIDAQMX_LIBRARY LIBNIDAQMX_INCLUDE_DIR)
# ###########################################################################
