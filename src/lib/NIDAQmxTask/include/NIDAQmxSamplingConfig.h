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


/**
* \defgroup icub_data_acquisition Data Acquisition 
* @ingroup icub_data_acquisition
*/


#ifndef __NIDAQMXSAMPLINGCONFIG_H__
#define __NIDAQMXSAMPLINGCONFIG_H__

namespace nidaqmx {
    /**
    * \cond
    * @ingroup icub_contrib_software
    * \defgroup icub_NIDAQmxTask NIDAQmxTask
    * \endcond
    * \class NIDAQmxSamplingConfig
    * 
    * \brief The NIDAQmxSamplingConfig is the configuration object for the sensor calibration.
    *
    *
    * \section intro_sec Description
    * The NIDAQmxSamplingConfig is the configuration object for the DAQ sampling.
    * It contains all those parameters which are needed to configure the data sampling and acquisition before the DAQ task is run.
    * These include the sampling rate, the number of samples per channel, etc.
    *
    * The configuration of a NIDAQmxTask object is a fairly cumbersome taks.
    * This class was created to simplify the interface for the end-user while maintaining a most flexible functionality.
    * 
    *
    * \section tested_os_sec Tested OS
    * Linux, Windows
    * 
    * 
    * \author Francesco Giovannini (francesco.giovannini@iit.it)
    * 
    * \copyright
    * 
    * Copyright (C) 2013 Francesco Giovannini, iCub Facility - Istituto Italiano di Tecnologia
    * 
    * CopyPolicy: Released under the terms of the GNU GPL v2.0.
    * 
    * This file can be edited at contrib/src/dataAcquisition/NIDAQmx/src/lib/include/NIDAQmxSamplingConfig.h.
    */
    class NIDAQmxSamplingConfig {
        private:
            /* ************************************************************ */
            /* ******* DAQ sampling attributes                      ******* */
            /**
             * The number of samples to acquire for each channel.
             */
            int DAQSamplesPerChannel;

            /**
             * The DAQ sampling rate in Hz.
             */
            double DAQSamplingRate;

            /**
             * The DAQ sampling timeout in ms.
             */
            double DAQSamplingTimeout;

            /**
             * The DAQ sampling buffer size.
             */
            int DAQSamplingBufferSize;
            /* ************************************************************ */

        public:
            /**
             * Default constructor.
             * \param aDAQSamplesPerChannel The number of samples to acquire for each channel
             * \param aDAQSamplingRate The DAQ sampling rate in Hz
             * \param aDAQSamplingTimeout The DAQ sampling timeout in ms
             */
            NIDAQmxSamplingConfig(const int &aDAQSamplesPerChannel, const double &aDAQSamplingRate, const double &aDAQSamplingTimeout, const  int &aDAQSamplingBufferSize);

            /* ************************************************************ */
            /* ******* Getters.                                     ******* */

            /**
             * Get the number of samples to acquire for each channel.
             * \returns An integer containing the number of samples per channel
             */
            int &getDAQSamplesPerChannel();

            /**
             * Get the DAQ sampling rate in Hz.
             * \returns A double containing the sampling rate.
             */
            double &getDAQSamplingRate();

            /**
             * Get the DAQ sampling timeout in ms.
             * \returns The DAQ sampling timeout
             */
            double &getDAQSamplingTimeout();

            /**
             * Get the DAQ sampling buffer size.
             * \returns The DAQ sampling buffer size
             */
            int &getDAQSamplingBufferSize();
            /* ************************************************************ */
    };
}

#endif
