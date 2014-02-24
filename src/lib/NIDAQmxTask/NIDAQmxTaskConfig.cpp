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


#include "NIDAQmxTaskConfig.h"

using nidaqmx::NIDAQmxTaskConfig;
using std::vector;
using std::string;

/* *********************************************************************************************************************** */
/* ******* Default Constructor.                                             ********************************************** */
NIDAQmxTaskConfig::NIDAQmxTaskConfig(const string &aDAQTaskName, const vector<string> &aDAQChannels, const vector<string> &aDAQChannelTypes,
        const vector<string> &aDAQTerminalConfig, const vector<double> &aDAQMinVals, const vector<double> &aDAQMaxVals) {
    DAQTaskName = aDAQTaskName;
    DAQNChannels = aDAQChannels.size();
    DAQChannels = aDAQChannels;
    DAQChannelTypes = aDAQChannelTypes;
    DAQTerminalConfig = aDAQTerminalConfig;
    DAQMinVals = aDAQMinVals;
    DAQMaxVals = aDAQMaxVals;
}
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* Get the DAQ Task name.                                           ********************************************** */
string &NIDAQmxTaskConfig::getDAQTaskName() {
    return DAQTaskName;
}
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* Get the DAQ Channel list.                                        ********************************************** */
int &NIDAQmxTaskConfig::getDAQNChannels() {
    return DAQNChannels;
}
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* Get the DAQ Channel list.                                        ********************************************** */
vector<string> &NIDAQmxTaskConfig::getDAQChannels() {
    return DAQChannels;
}
/* *********************************************************************************************************************** */

/* *********************************************************************************************************************** */
/* ******* Get the DAQ Channel type list.                                   ********************************************** */
vector<string> &NIDAQmxTaskConfig::getDAQChannelTypes() {
    return DAQChannelTypes;
}
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* Get the DAQ Terminal configuration list.                         ********************************************** */
vector<string> &NIDAQmxTaskConfig::getDAQTerminalConfig() {
    return DAQTerminalConfig;
}
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* Get the DAQ Minimum values.                                      ********************************************** */
vector<double> &NIDAQmxTaskConfig::getDAQMinVals() {
    return DAQMinVals;
}
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* Get the DAQ Maximum values.                                      ********************************************** */
vector<double> &NIDAQmxTaskConfig::getDAQMaxVals() {
    return DAQMaxVals;
}
/* *********************************************************************************************************************** */
