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


#include "NIDAQmxSamplingConfig.h"

using nidaqmx::NIDAQmxSamplingConfig;

/* *********************************************************************************************************************** */
/* ******* Default Constructor.                                             ********************************************** */
NIDAQmxSamplingConfig::NIDAQmxSamplingConfig(const int &aDAQSamplesPerChannel, const double &aDAQSamplingRate, const double &aDAQSamplingTimeout, const  int &aDAQSamplingBufferSize) {
    DAQSamplesPerChannel = aDAQSamplesPerChannel;
    DAQSamplingRate = aDAQSamplingRate;
    DAQSamplingTimeout = aDAQSamplingTimeout;
    DAQSamplingBufferSize = aDAQSamplingBufferSize;
}
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* Get the number of DAQ Samples per channel.                       ********************************************** */
int &NIDAQmxSamplingConfig::getDAQSamplesPerChannel() {
    return DAQSamplesPerChannel;
}
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* Get the DAQ Sampling rate.                                       ********************************************** */
double &NIDAQmxSamplingConfig::getDAQSamplingRate() {
    return DAQSamplingRate;
}
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* Get the DAQ Sampling timeout.                                    ********************************************** */
double &NIDAQmxSamplingConfig::getDAQSamplingTimeout() {
     return DAQSamplingTimeout;
 }
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* Get the DAQ Sampling buffer size.                                ********************************************** */
int &NIDAQmxSamplingConfig::getDAQSamplingBufferSize() {
     return DAQSamplingBufferSize;
 }
/* *********************************************************************************************************************** */
