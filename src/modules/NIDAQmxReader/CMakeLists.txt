# Copyright: 2013 Francesco Giovannini, iCub Facility - Istituto Italiano di Tecnologia
# Author: Francesco Giovannini
# CopyPolicy: Released under the terms of the GNU GPL v2.0.
# 

# ###########################################################################
# The NIDAQmxReader module.
# ###########################################################################
set(MODULENAME NIDAQmxReader)


# ###########################################################################
# The included source code
# ###########################################################################
set(INC_HEADERS
    include/NIDAQmxReaderModule.h
    )

set(INC_SOURCES
        main.cpp
        NIDAQmxReaderModule.cpp
    )
# ###########################################################################


# ###########################################################################
# The include directory 
# ###########################################################################
include_directories(include/)
include_directories(${YARP_INCLUDE_DIRS})
include_directories("${NIDAQMX_INCLUDE_DIR}")
# ###########################################################################


# ###########################################################################
# The executable
# ###########################################################################
# Generate list of target link libraries
list(APPEND TARG_LINK_LIBS NIDAQmxTask)
#list(APPEND TARG_LINK_LIBS Conversions)
#if(CMAKE_BUILD_TYPE MATCHES debug)
#    list(APPEND TARG_LINK_LIBS Printer)
#endif(CMAKE_BUILD_TYPE MATCHES debug)
    
add_executable(${MODULENAME} ${INC_HEADERS} ${INC_SOURCES})
target_link_libraries(${MODULENAME} ${YARP_LIBRARIES} ${TARG_LINK_LIBS})
install(TARGETS ${MODULENAME} DESTINATION bin)
# ###########################################################################
