/*``
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
* @ingroup icub_data_acquisition
*/


#ifndef __NIDAQMXTASK_H__
#define __NIDAQMXTASK_H__

#include <map>
#include <string>
#include <vector>

#include "NIDAQmxConstants.h"
#include "NIDAQmxTaskConfig.h"
#include "NIDAQmxSamplingConfig.h"
#include "NIDAQmxCalibrationConfig.h"

/**
 * Common namespace for all NIDAQmx-related constants, structs, typedefs and classes.
 */
namespace nidaqmx {
    /**
     * Parameters object for the NIDAQmxTask.
     * This object groups the parameters contained in the NIDAQmxTaskConfig, NIDAQmxSamplingConfig and NIDAQmxCalibrationConfig objects.
     */
    struct NIDAQmxTaskParams {
        /* ******* DAQ task attributes                           ******* */
        /**
         * The DAQ device name.
         */
        std::string DAQDeviceName;

        /**
         * The DAQ task name.
         */
        std::string DAQTaskName;

        /**
         * The DAQ channels to acquire.
         */
        std::vector<std::string> DAQChannels;

        /**
         * The DAQ channel types.
         */
        std::vector<std::string> DAQChannelTypes;

        /**
         * The terminal configuration for each DAQ channel.
         */
        std::vector<std::string> DAQTerminalConfig;

        /**
         * The minimum sample values for each channel
         */
        std::vector<double> DAQMinVals;

        /**
         * The maximum sample values for each channel
         */
        std::vector<double> DAQMaxVals;

        /* ****** DAQ sampling attributes                       ****** */
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

        /* ****** DAQ sensor calibration data                   ****** */
        /**
         * The DAQ sensor calibration scales.
         * These are used to scale down the values resulting from the matrix multiplication of the analog values with the calibration matrix.
         */
        std::vector<double> DAQSensorCalibScales;

        /**
         * The DAQ sensor calibration matrix.
         */
        nidaqmx::DoubleMatrix2D DAQSensorCalibMatrix;
    };

    /**
     * Result object generated as output from the NIDAQmxTask.
     */
    struct NIDAQmxResults {
        /* ******* Acquire samples.                             ******* */
        /**
         * The analogue sensor values (Volts, Amps, etc.)
         */
        std::vector<double> analogValues;

        /**
         * The computed sensor values (Newtons, etc.)
         */
        std::vector<double> realValues;
    };

    /**
    * \defgroup icub_NIDAQmxTask NIDAQmxTask
    * @ingroup icub_data_acquisition
    *
    * \class NIDAQmxTask
    *
    * \brief The NIDAQmxTask is a C++ wrapper for the National Instruments proprietary NIDAQmx library.
    *
    *
    * \section intro_sec Description
    * The NIDAQmxTask is a C++ wrapper for the National Instruments proprietary NIDAQmx library.
    * This library can be freely downloaded from the National Instruments website.
    * It is available for the following operative systems:
    *     - Linux (NIDAQmxBase):  http://search.ni.com/nisearch/app/main/p/bot/no/ap/tech/lang/it/pg/1/sn/catnav:du/q/nidaqmxbase/
    *     - Windows (NIDAQmx):  http://search.ni.com/nisearch/app/main/p/bot/no/ap/tech/lang/it/pg/1/sn/catnav:du,n8%3A3478.41.181.5495/q/ni-daqmx/
    *
    * The typical NIDAQmx workflow is as follows:
    *     -# Create the DAQ task
    *         -# Create the data channels to acquire
    *         -# Set the DAQ timing/clock options
    *         -# Start the task
    *     -# Read the samples
    *     -# Stop the task
    *     -# Clear the task
    *
    * This library provides an interface to this NIDAQmx workflow by providing four methods:
    *     -# initialiseDAQTask()
    *     -# runDAQTask()
    *     -# stopDAQTask()
    *     -# clearDAQTask()
    *
    * It is important to clear any task which is created using this API to free any allocated memory.
    *
    * The NIDAQmxTask is configured to perform continuous data acquisition.
    * NIDAQmx continuous data acquisition tasks work by sampling data at a given frequency.
    * The samples are then placed into a circular buffer.
    * The buffer is then emptied by iteratively reading a set number of samples from it.
    *
    * Problems can arise if the sampling frequency is faster than the rate at which the buffer is emptied.
    * In this case the data in the buffer will be overwritten and some samples will be lost.
    *
    * These parameters (sampling rate, number of samples to read from the buffer, etc.) are set by the user and passed to the task constructor.
    *
    *
    * \section lib_sec Libraries
    * This wrapper depends on different libraries depending on the operative system:
    *     - Linux installations require libnidaqmxbase >= 3.7 (provided by the NIDAQmxBase software package)
    *     - Windows requires NIDAQmx.lib >= 9.7 (provided by the NIDAQmx software package).
    *
    *
    * \section supported_daq_cards Supported National Instruments DAQ cards
    * This module supports all the DAQ cards which are supported by the installed NIDAQmx (or NIDAQmxBase) library.
    * These are listed in the library Readme.
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
    * This file can be edited at contrib/src/dataAcquisition/NIDAQmx/src/lib/include/NIDAQmxTask.h.
    */
    class NIDAQmxTask {
        private:
            /* ************************************************************ */
            /* ******* DAQ task attributes                          ******* */
            /**
             * The DAQ Task handle.
             * This is a unique identifier for NIDAQmx tasks.
             */
            TaskHandle DAQTaskHandle;

            /**
             * The DAQ device name.
             */
            std::string DAQDeviceName;

            /**
             * The DAQ task configuration object.
             */
            nidaqmx::NIDAQmxTaskConfig DAQTaskConfig;

            /**
             * The DAQ sampling configuration object.
             */
            nidaqmx::NIDAQmxSamplingConfig DAQSamplingConfig;

            /**
             * The sensor calibration configuration object.
             */
            nidaqmx::NIDAQmxCalibrationConfig DAQCalibrationConfig;
            /* ************************************************************ */


            /* ************************************************************ */
            /* ******* Conversion maps.                             ******* */
            /**
             * The DAQ Channel type map.
             * Maps the string input parameters to the corresponding NIDAQmx integer constants.
             */
            std::map<std::string, int> channelTypes;
            /**
             * The DAQ Terminal configuration map.
             * Maps the string input parameters to the corresponding NIDAQmx integer constants.
             */
            std::map<std::string, int> terminalConfigs;
            /* ************************************************************ */

        public:
            /**
             * Default constructor.
             * \param aDAQTaskParams The DAQ parameters structure
             */
            NIDAQmxTask(const nidaqmx::NIDAQmxTaskParams &aDAQTaskParams);

            /**
             * Default destructor.
             */
//            ~NIDAQmxTask(void);


            /* ************************************************************ */
            /* ******* Run the task.                                ******* */
            /**
             * Initialise the DAQ Task by creating it, adding the DAQ channels,
             * configuring the sampling and starting it.
             */
            bool initialiseDAQTask(void);

            /**
             * Run the DAQ task and read the data samples in the given array.
             * \param i_results The result structure in which to store the sensor values
             */
            bool runDAQTask(nidaqmx::NIDAQmxResults &i_results);

            /**
             * Stop the DAQ task.
             */
            bool stopDAQTask(void);

            /**
             * Clear the DAQ task and delete any dynamically allocated memory associated with it.
             */
            bool clearDAQTask(void);
            /* ************************************************************ */

        private:
            /* ************************************************************ */
            /* ******* Task handling steps.                         ******* */
            /**
             * Create the DAQ task.
             */
            bool createDAQTask(void);

            /**
             * Create the DAQ channels.
             */
            bool createDAQChannels(void);

            /**
             * Start the DAQ task.
             */
            bool startDAQTask(void);

            /**
             * Reads the samples from the sensor into the input vector.
             * \param i_analog The vector in which the sensor values will be read
             */
            bool readAnalogValues(std::vector<double> &i_analog);

            /**
             * Converts the input voltage values into intelligible sensor values (force, torque, etc.).
             * \param i_analog The input voltage values to be converted
             * \param o_real The output converted values
             */
            bool computeSensorValues(std::vector<double> &i_analog, std::vector<double> &o_real);

            /**
             * Error handling done sensibly.
             * This method is called to check the error codes returned by NIDAQmx C api functions.
             * \param i_errorCode The error code returned by the called function.
             */
            bool errorCheck(int i_errorCode);
            /* ************************************************************ */


            /* ************************************************************ */
            /* ******* Generate the conversion maps for NIDAQmx constants.  */
            /**
             * Generate the maps used by this library.
             */
            void generateMaps(void);

            /**
             * Generate the mapping of NIDAQmx C API channel types to C++ DAQChannelType enum.
             */
            void generateChannelTypesMap(void);

            /**
             * Generate the mapping of NIDAQmx C API terminal configurations to C++ DAQTerminalConfig enum.
             */
            void generateTerminalConfigsMap(void);
            /* ************************************************************ */
    };
}

#endif
