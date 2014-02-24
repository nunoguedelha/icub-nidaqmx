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


#include "NIDAQmxCalibrationConfig.h"

using nidaqmx::NIDAQmxCalibrationConfig;
using nidaqmx::DoubleMatrix2D;
using std::vector;

/* *********************************************************************************************************************** */
/* ******* Default Constructor.                                             ********************************************** */
NIDAQmxCalibrationConfig::NIDAQmxCalibrationConfig(const std::vector<double> &aDAQSensorCalibScales, const DoubleMatrix2D &aDAQSensorCalibMatrix) {
    DAQSensorCalibScales = aDAQSensorCalibScales;
    DAQSensorCalibMatrix = aDAQSensorCalibMatrix;
}
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* Get the sensor calibration scales.                               ********************************************** */
vector<double> &NIDAQmxCalibrationConfig::getDAQSensorCalibScales() {
    return DAQSensorCalibScales;
}
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* Get the sensor calibration scales.                               ********************************************** */
DoubleMatrix2D &NIDAQmxCalibrationConfig::getDAQSensorCalibMatrix() {
    return DAQSensorCalibMatrix;
}
/* *********************************************************************************************************************** */
