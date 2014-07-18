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
* @ingroup icub_data_acquisition
*/


#ifndef __NIDAQMXTASKCONFIG_H__
#define __NIDAQMXTASKCONFIG_H__

#include <string>
#include <vector>

namespace nidaqmx {
    /**
    * \cond
    * @ingroup icub_NIDAQmxTask
    * \endcond
    * \class NIDAQmxTaskConfig
    *
    * \brief The NIDAQmxTaskConfig is the configuration object for the NIDAQmxTask.
    *
    *
    * \section intro_sec Description
    * The NIDAQmxTaskConfig is the configuration object for the NIDAQmxTask.
    * It contains all those parameters which are needed to configure the NIDAQmx task before running it.
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
    * This file can be edited at contrib/src/dataAcquisition/NIDAQmx/src/lib/include/NIDAQmxTaskConfig.h.
    */
    class NIDAQmxTaskConfig {
        private:
            /* ************************************************************ */
            /* ******* DAQ task attributes                          ******* */
            /**
             * The DAQ task name.
             */
            std::string DAQTaskName;

            /**
             * The number of DAQ channels to acquire.
             */
            int DAQNChannels;

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
            /* ************************************************************ */

        public:
            /**
             * Default constructor.
             * \param aDAQTaskName The DAQ task name
             * \param aDAQChannels The DAQ channels to acquire
             * \param aDAQChannelTypes The DAQ channel types
             * \param aDAQTerminalConfig The terminal configuration for each DAQ channel
             * \param aDAQMinVals The minimum sample values for each channel
             * \param aDAQMaxVals The maximum sample values for each channel
             */
            NIDAQmxTaskConfig(const std::string &aDAQTaskName, const std::vector<std::string> &aDAQChannels, const std::vector<std::string> &aDAQChannelTypes,
                const std::vector<std::string> &aDAQTerminalConfig, const std::vector<double> &aDAQMinVals, const std::vector<double> &aDAQMaxVals);

            /* ************************************************************ */
            /* ******* Getters.                                     ******* */

            /**
             * Get the DAQ Task name.
             * \returns An std::string containing the DAQ Task name.
             */
            std::string &getDAQTaskName();

            /**
             * Get the number of DAQ channels to acquire.
             * \returns An integer containing the number of DAQ channels.
             */
            int &getDAQNChannels();

            /**
             * Get the list of DAQ channels to acquire.
             * \returns An std::vector<std::string> containing the list of DAQ channels to acquire.
             */
            std::vector<std::string> &getDAQChannels();

            /**
             * Get the DAQ channel types for each channel.
             * \returns An std::vector<std::string> containing the DAQ channel types.
             */
            std::vector<std::string> &getDAQChannelTypes();

            /**
             * Get the DAQ terminal configurations for each channel.
             * \returns An std::vector<std::string> containing the DAQ terminal configurations.
             */
            std::vector<std::string> &getDAQTerminalConfig();

            /**
             * Get the DAQ minimum sample values for each channel.
             * \returns An std::vector<double> containing the minimum sample values.
             */
            std::vector<double> &getDAQMinVals();

            /**
             * Get the DAQ maximum sample values for each channel.
             * \returns An std::vector<double> containing the maximum sample values.
             */
            std::vector<double> &getDAQMaxVals();
            /* ************************************************************ */
    };
}

#endif
