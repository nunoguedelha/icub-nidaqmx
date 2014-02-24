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


#ifndef __NIDAQMXCALIBRATIONCONFIG_H__
#define __NIDAQMXCALIBRATIONCONFIG_H__

#include <vector>

#include "NIDAQmxTypedefs.h"

namespace nidaqmx {
    /**
    * \class NIDAQmxCalibrationConfig
    * 
    * \brief The NIDAQmxCalibrationConfig is the configuration object for the sensor calibration.
    *
    *
    * \section intro_sec Description
    * The NIDAQmxCalibrationConfig is the configuration object for the sensor calibration.
    * It contains all those parameters which are dependent on the sensor to be acquired.
    * These include the calibration scales, the calibration matrix, etc.
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
    * This file can be edited at contrib/src/dataAcquisition/NIDAQmx/src/lib/include/NIDAQmxCalibrationConfig.h.
    */
    class NIDAQmxCalibrationConfig {
        private:
            /* ************************************************************ */
            /* ******* DAQ sensor calibration data                  ******* */
            /**
             * The DAQ sensor calibration scales.
             * These are used to scale down the values resulting from the matrix multiplication of the analog values with the calibration matrix.
             */
            std::vector<double> DAQSensorCalibScales;

            /**
             * The DAQ sensor calibration matrix.
             */
            DoubleMatrix2D DAQSensorCalibMatrix;
            /* ************************************************************ */

        public:
            /**
             * Default constructor.
             * \param aDAQSensorCalibScales The sensor calibration scales
             * \param aDAQSensorCalibMatrix The sensor calibration matrix
             */
            NIDAQmxCalibrationConfig(const std::vector<double> &aDAQSensorCalibScales, const DoubleMatrix2D &aDAQSensorCalibMatrix);

            /* ************************************************************ */
            /* ******* Getters.                                     ******* */
            /**
             * Get the DAQ sensor calibration scales.
             * \returns An std::vector<double> containing the calibration scales
             */
            std::vector<double> &getDAQSensorCalibScales();

            /**
             * Get the DAQ sensor calibration matrix.
             * \returns A DoubleMatrix2D object containing the calibration matrix
             */
            DoubleMatrix2D &getDAQSensorCalibMatrix();
            /* ************************************************************ */
    };
}

#endif
