# Copyright: 2013 iCub Facility, Istituto Italiano di Tecnologia
# Author: Francesco Giovannini
# CopyPolicy: Released under the terms of the GNU GPL v2.0.
# 

#
# The project root CMakeLists.
#

# ###########################################################################
# Project details
# ###########################################################################
cmake_minimum_required(VERSION 2.6)
CMAKE_POLICY(SET CMP0012 NEW) 
set(PROJECTNAME NIDAQmxWrapper)
project(${PROJECTNAME})

# Project Version
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
 
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)      # Set build path
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)         # Set lib path

set(CMAKE_BUILD_TYPE debug)     # Compile in debug mode
set(GCC_DEBUG_COMPILE_FLAGS, "-g")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_DEBUG_COMPILE_FLAGS}" )
# ###########################################################################


# ###########################################################################
# iCub and YARP Includes
# ###########################################################################
find_package(YARP REQUIRED)
#find_package(ICUB REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${YARP_MODULE_PATH})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ICUB_MODULE_PATH})
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${ICUB_LINK_FLAGS}")

#include(iCubHelpers)

include_directories(${YARP_INCLUDE_DIRS})
#include_directories(${ICUB_INCLUDE_DIRS} ${YARP_INCLUDE_DIRS})
# ###########################################################################


# ###########################################################################
# Project content
# ###########################################################################
# Included directories
include_directories(lib/)

# Subdirectories
add_subdirectory(lib/)      # Libraries
add_subdirectory(modules/)  # Modules
# ###########################################################################
