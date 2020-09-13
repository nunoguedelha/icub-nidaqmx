# Copyright: 2013 iCub Facility, Istituto Italiano di Tecnologia
# Author: Francesco Giovannini
# CopyPolicy: Released under the terms of the GNU GPL v2.0.
# 

# ###########################################################################
# The NIDAQmx Library encapsulator.
# ###########################################################################


# ###########################################################################
# Library Details
# ###########################################################################
set(LIBNAME NIDAQmxTask)
project(${LIBNAME})
# ###########################################################################


# ###########################################################################
# NIDAQmx Includes
# ###########################################################################
# Set package directory
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Check for required library
if(WIN32)
    find_package(LibNIDAQmx REQUIRED)
    set(NIDAQMX_FOUND ${LIBNIDAQMX_FOUND})
    set(NIDAQMX_LIB_NAME NIDAQmx)
	set(NIDAQMX_LIBRARY ${LIBNIDAQMX_LIBRARY})
	set(NIDAQMX_INCLUDE_DIR ${LIBNIDAQMX_INCLUDE_DIR} CACHE STRING "Platform-independent NIDAQmx include directory")
elseif(UNIX)
    find_package(LibNIDAQmx REQUIRED)
    set(NIDAQMX_FOUND ${LIBNIDAQMX_FOUND})
    set(NIDAQMX_LIB_NAME NIDAQmx)
	set(NIDAQMX_LIBRARY ${LIBNIDAQMX_LIBRARY})
	set(NIDAQMX_INCLUDE_DIR ${LIBNIDAQMX_INCLUDE_DIR} CACHE STRING "Platform-independent NIDAQmx include directory")
endif(WIN32)

if("${NIDAQMX_FOUND}")
    MESSAGE(STATUS "${NIDAQMX_LIB_NAME} library found at '${NIDAQMX_LIBRARY}'.")
	MESSAGE(STATUS "${NIDAQMX_LIB_NAME} headers found at '${NIDAQMX_INCLUDE_DIR}'.")
else("${NIDAQMX_FOUND}")
    MESSAGE(FATAL_ERROR "Could not find the ${NIDAQMX_LIB_NAME} library.")
endif("${NIDAQMX_FOUND}")
# ###########################################################################


# ###########################################################################
# The included source code
# ###########################################################################
set(INC_HEADERS
        include/NIDAQmxConstants.h
#        include/NIDAQmxFunctions.h
        include/NIDAQmxTypedefs.h
        include/NIDAQmxTask.h
        include/NIDAQmxTaskConfig.h
        include/NIDAQmxSamplingConfig.h
        include/NIDAQmxCalibrationConfig.h
    )

set(INC_SOURCES
        NIDAQmxTask.cpp
        NIDAQmxTaskConfig.cpp
        NIDAQmxSamplingConfig.cpp
        NIDAQmxCalibrationConfig.cpp
    )
# ###########################################################################


# ###########################################################################
# The include directories
# ###########################################################################
include_directories("${NIDAQMX_INCLUDE_DIR}")
include_directories(include/)
# ###########################################################################

# ###########################################################################
# The library
# ###########################################################################
# Generate list of target link libraries
if(UNIX)
    list(APPEND TARG_LINK_LIBS nidaqmx)
elseif(WIN32)
    list(APPEND TARG_LINK_LIBS ${NIDAQMX_LIBRARY})
endif(UNIX)

add_library(${LIBNAME} STATIC ${INC_HEADERS} ${INC_SOURCES})
#set(CMAKE_CXX_FLAGS "-m32")
#set(CMAKE_C_FLAGS "-m32")

target_link_libraries(${LIBNAME} ${YARP_LIBRARIES} ${TARG_LINK_LIBS})
# ###########################################################################

