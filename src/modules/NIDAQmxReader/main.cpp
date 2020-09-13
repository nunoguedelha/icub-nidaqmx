/* 
 * Copyright (C) 2013 Francesco Giovannini, iCub Facility - Istituto Italiano di Tecnologia
 * Authors: Francesco Giovannini
 * email:   francesco.giovannini@iit.it
 * website: www.robotcub.org 
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
 */



#include <yarp/dev/all.h>

#include "NIDAQmxReaderModule.h"
#include <iostream>

using namespace yarp::os;
using namespace yarp::dev;
using namespace yarp::sig;


int main(int argc, char *argv[]) {
    // Open network
    Network yarp;
    if (!yarp.checkNetwork()) {
         fprintf(stdout, "Error: yarp server is not available.\n");
         return -1;
    }     

    // Create the NI-DAQ reader module
    NIDAQmxReaderModule mod;

    // Create and configure the resource finder
    ResourceFinder rf;
    rf.setVerbose();
    rf.setDefaultConfigFile("confNIDAQmxReader.ini");
    rf.setDefaultContext("NIDAQmxReader");
    rf.configure(argc, argv);

    // Configure and run module
    std::cout << "Configuring and starting module.\n";
    // This calls configure(rf) and, upon success, the module execution begins with a call to updateModule()
    if (!mod.runModule(rf)) {
        std::cerr << "Error module did not start\n";
    }
  
    std::cout << "Main returning..." << '\n';
    return 0;
}

