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


#include "NIDAQmxTask.h"

#include <iostream>
#include <sstream>

using namespace nidaqmx;

using std::cerr;
using std::cout;
using std::string;


/* *********************************************************************************************************************** */
/* ******* Default constructor.                                             ********************************************** */
NIDAQmxTask::NIDAQmxTask(const nidaqmx::NIDAQmxTaskParams &aDAQTaskParams) 
    : DAQDeviceName(aDAQTaskParams.DAQDeviceName)
      , DAQTaskConfig(aDAQTaskParams.DAQTaskName, aDAQTaskParams.DAQChannels, aDAQTaskParams.DAQChannelTypes,
            aDAQTaskParams.DAQTerminalConfig, aDAQTaskParams.DAQMinVals, aDAQTaskParams.DAQMaxVals)
      , DAQSamplingConfig(aDAQTaskParams.DAQSamplesPerChannel, aDAQTaskParams.DAQSamplingRate, aDAQTaskParams.DAQSamplingTimeout, aDAQTaskParams.DAQSamplingBufferSize)
      , DAQCalibrationConfig(aDAQTaskParams.DAQSensorCalibScales, aDAQTaskParams.DAQSensorCalibMatrix) {
    DAQTaskHandle = 0;

    generateMaps();
}
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* Default destructor.                                              ********************************************** */
//NIDAQmxTask::~NIDAQmxTask(void) { }
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* Initialise the DAQ Task.                                         ********************************************** */
bool NIDAQmxTask::initialiseDAQTask(void) {
    // Creates and starts the DAQ Task
    if(createDAQTask()) {
        return startDAQTask();
    } else {
        return false;
    }
}
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* Run the DAQ Task.                                                ********************************************** */
bool NIDAQmxTask::runDAQTask(nidaqmx::NIDAQmxResults &i_results) {
    // Read sensor values
    if(readAnalogValues(i_results.analogValues)) {
        return computeSensorValues(i_results.analogValues, i_results.realValues);
    } else {
        return false;
    }
}
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* Stop the DAQ Task.                                               ********************************************** */
bool NIDAQmxTask::stopDAQTask(void) {
    if(DAQTaskHandle != 0)  {
        // Ensure the task is stopped correctly
        cout << "NIDAQmxTask: Stopping the DAQ Task. \n";

#ifdef __linux__
        if(!errorCheck(DAQmxBaseStopTask(DAQTaskHandle))) {
            return false;
        }
//        DAQmxBaseClearTask(DAQTaskHandle);
#elif _WIN32
        if (!errorCheck(DAQmxStopTask(DAQTaskHandle))) {
            return false;
        }
//        DAQmxClearTask(DAQTaskHandle);
#endif
        
        cout << "NIDAQmxTask: DAQ Task stopped. \n";

        return true;
    }

    return false;
}
/* *********************************************************************************************************************** */

            
/* *********************************************************************************************************************** */
/* ******* Clear the DAQ Task.                                               ********************************************** */
bool NIDAQmxTask::clearDAQTask(void) {
    if(DAQTaskHandle != 0)  {
        // Ensure the task is stopped correctly
        cout << "NIDAQmxTask: Clearing the DAQ Task. \n";

#ifdef __linux__
//        DAQmxBaseStopTask(DAQTaskHandle);
        if (!errorCheck(DAQmxBaseClearTask(DAQTaskHandle))) {
            return false;
        }
#elif _WIN32
//        DAQmxStopTask(DAQTaskHandle);
        if (!errorCheck(DAQmxClearTask(DAQTaskHandle))) {
            return false;
        }
#endif
        
        cout << "NIDAQmxTask: DAQ Task cleared. \n";

        return true;
    }

    return false;
}
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* Create the DAQ Task.                                             ********************************************** */
bool NIDAQmxTask::createDAQTask(void) {
    // Create the DAQ task
    cout << "NIDAQmxTask: Creating the DAQ task. \n";

#ifdef __linux__
    if (!errorCheck(DAQmxBaseCreateTask(DAQTaskConfig.getDAQTaskName().c_str(), &DAQTaskHandle))) {
        return false;
    }
#elif _WIN32
    if (!errorCheck(DAQmxCreateTask(DAQTaskConfig.getDAQTaskName().c_str(), &DAQTaskHandle))) {
        return false;
    }
#endif

    cout << "NIDAQmxTask: DAQ Task created. \n";


    // Create the DAQ channels
    cout << "NIDAQmxTask: Creating the DAQ channels associated with the task. \n";
    if (!createDAQChannels()) {
        return false;
    }
    cout << "NIDAQmxTask: All DAQ channels created. \n";

    // Define the sampling rate and timing
    cout << "NIDAQmxTask: Defining sampling rate and timing. \n";
    int nTotSamples = DAQSamplingConfig.getDAQSamplesPerChannel() * DAQTaskConfig.getDAQChannels().size();        // Total number of samples

#ifdef __linux__
    if (!errorCheck(DAQmxBaseCfgSampClkTiming(DAQTaskHandle, "OnboardClock", DAQSamplingConfig.getDAQSamplingRate(), 
//            DAQmx_Val_Rising, DAQmx_Val_FiniteSamps, DAQSamplingConfig.getDAQSamplesPerChannel()))) {
            DAQmx_Val_Rising, DAQmx_Val_ContSamps, DAQSamplingConfig.getDAQSamplesPerChannel()))) {
        return false;
    }
#elif _WIN32
    if (!errorCheck(DAQmxCfgSampClkTiming(DAQTaskHandle, "OnBoardClock", DAQSamplingConfig.getDAQSamplingRate(), 
//            DAQmx_Val_Rising, DAQmx_Val_FiniteSamps, DAQSamplingConfig.getDAQSamplesPerChannel()))) {
            DAQmx_Val_Rising, DAQmx_Val_ContSamps, DAQSamplingConfig.getDAQSamplesPerChannel()))) {
        return false;
    }
#endif

    cout << "NIDAQmxTask: Sampling rate and timing defined. \n";


//    if (!errorCheck(DAQmxBaseCfgInputBuffer(DAQTaskHandle, nTotSamples*2))) {
#ifdef __linux__
    if (!errorCheck(DAQmxBaseCfgInputBuffer(DAQTaskHandle, DAQSamplingConfig.getDAQSamplingBufferSize()))) {
        return false;
    }
#elif _WIN32
	if (!errorCheck(DAQmxCfgInputBuffer(DAQTaskHandle, DAQSamplingConfig.getDAQSamplingBufferSize()))) {
        return false;
    }
#endif

    return true;
}
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* Create the DAQ Channels.                                         ********************************************** */
bool NIDAQmxTask::createDAQChannels(void) {
    using std::stringstream;
    using std::map;

    bool result = true;

    // Create the acquisition channels according to the task configuration object
    stringstream channelName;
    int channelType;
    int terminalConfig;

    // TODO: Change this to construct channel depending on channel type
    for (int i = 0; i < DAQTaskConfig.getDAQChannels().size(); ++i) {
        channelName.str(std::string());     // Clear stringstream
        channelName << DAQDeviceName << "/" << DAQTaskConfig.getDAQChannels()[i];      // Construct the channel name
        cout << "NIDAQmxTask: Creating DAQ channel - " << channelName.str()  << ". \n";
        
        // Find channel type
        map<string, int>::iterator curVal = channelTypes.find(DAQTaskConfig.getDAQChannelTypes()[i]);
        if (curVal != channelTypes.end()) {       // Current channel type exists
            channelType = curVal->second;
        } else {        // Current channel type does not exist
            cerr << "NIDAQmxTask: Error: The DAQ channel type provided - (" << DAQTaskConfig.getDAQChannelTypes()[i] << ") is invalid. Check the configuration file. \n";
            cerr << "NIDAQmxTask: Error: Could not initalise the DAQ task. \n";

            result = false;
            break;
        }
        // Find terminal config
        curVal = terminalConfigs.find(DAQTaskConfig.getDAQTerminalConfig()[i]);
        if (curVal != terminalConfigs.end()) {       // Current channel type exists
            terminalConfig = curVal->second;    // Convert to int
        } else {        // Current channel type does not exist
            cerr << "NIDAQmxTask: Error: The DAQ terminal configuration provided - (" << DAQTaskConfig.getDAQTerminalConfig()[i] << ") is invalid. Check the configuration file. \n";
            cerr << "NIDAQmxTask: Error: Could not initalise the DAQ task. \n";

            result = false;
            break;
        }
        
#ifdef __linux__
        if(!errorCheck(DAQmxBaseCreateAIVoltageChan(DAQTaskHandle, channelName.str().c_str(), "", terminalConfig,
                    DAQTaskConfig.getDAQMinVals()[i], DAQTaskConfig.getDAQMaxVals()[i], channelType, NULL))) {
            result = false;
            break;
        }
#elif _WIN32
		if(!errorCheck(DAQmxCreateAIVoltageChan(DAQTaskHandle, channelName.str().c_str(), "", terminalConfig,
                    DAQTaskConfig.getDAQMinVals()[i], DAQTaskConfig.getDAQMaxVals()[i], channelType, NULL))) {
            result = false;
            break;
        }
#endif
        cout << "NIDAQmxTask: DAQ channel created. \n";
    }

    return result;
}
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* Start the DAQ Task.                                              ********************************************** */
bool NIDAQmxTask::startDAQTask(void) {
    cout << "NIDAQmxTask: Starting the DAQ Task. \n";

    string errMsg = "NIDAQmxTask: Could not start the DAQ task. \n";
#ifdef __linux__
    if(!errorCheck(DAQmxBaseStartTask(DAQTaskHandle))) {
        cerr << errMsg;
        return false;
    }
#elif _WIN32
    if(!errorCheck(DAQmxStartTask(DAQTaskHandle))) {
        cerr << errMsg;
        return false;
    }
#endif

    cout << "NIDAQmxTask: DAQ Task started. \n";

	return true;
}
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* Read the values and store them.                                  ********************************************** */
bool NIDAQmxTask::readAnalogValues(std::vector<double> &i_analog) {
    int nTotSamples = DAQSamplingConfig.getDAQSamplesPerChannel() * DAQTaskConfig.getDAQChannels().size();        // Total number of samples
    int bufSize = nTotSamples * 2;
  
    // Read samples
    cout << "NIDAQmxTask: Reading samples. \n";
    //double data[bufSize];
	double *data = new double[bufSize];		// FG: Dynamically allocate this to please Visual Studio
    int32 readSamples = 0;

#ifdef __linux__
    if(!errorCheck(DAQmxBaseReadAnalogF64(DAQTaskHandle, -1, DAQSamplingConfig.getDAQSamplingTimeout(), DAQmx_Val_GroupByScanNumber, 
                data, bufSize, &readSamples, NULL))) {
        return false;
    }
#elif _WIN32
    if(!errorCheck(DAQmxReadAnalogF64(DAQTaskHandle, -1, DAQSamplingConfig.getDAQSamplingTimeout(), DAQmx_Val_GroupByScanNumber, 
                data, bufSize/2, &readSamples, NULL))) {
        return false;
    }
#endif
    
    // Store data
    int totReadVals = readSamples * DAQTaskConfig.getDAQChannels().size();
    //    // Resize output vector
    i_analog.resize(totReadVals, 0.0);
//	i_analog.assign(data, data+totReadVals);
    for (int i = 0; i < totReadVals; ++i) {
        i_analog[i] = data[i];
//		i_analog.push_back(data[i]);
    
#if 0
        cout << i_analog[i] << " ";
        if ((i+1) % 6 == 0) {
            cout << "\n";
        }
#endif
    }
//    cout << "\n";

    cout << "NIDAQmxTask: " << readSamples << " samples read per channel. \n";

	// Deallocate memory
	delete data;

    return true;
}
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* Computer actual sensor values from analogue samples.             ********************************************** */
bool NIDAQmxTask::computeSensorValues(std::vector<double> &i_analog, std::vector<double> &o_real) {
    // Resize output vector
    o_real.resize(i_analog.size(), 0.0);

    // Matrix multiply samples x calibrationMatrix
    int DAQNChannels = DAQTaskConfig.getDAQChannels().size();

    int samp = 0;
    while (samp < i_analog.size()) {    // Loop all samples
        // Multiply calibration matrix
        for (size_t i = 0; i < DAQNChannels; ++i) {    // Loop rows
            double tmpVal = 0;
            for (size_t j = 0; j < DAQNChannels; ++j) {    // Loop columns
                // Matrix multiply with calibration matrix
                tmpVal +=  DAQCalibrationConfig.getDAQSensorCalibMatrix()[i][j] * i_analog[j+samp];
            }

            // Divide by calibration scales
            tmpVal = tmpVal / DAQCalibrationConfig.getDAQSensorCalibScales()[i];

            // Store value
            o_real[i+samp] = tmpVal;
        }
        samp += DAQNChannels;
    }

    return true;
}
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* DAQmx Error handling done sensibly.                              ********************************************** */
bool NIDAQmxTask::errorCheck(int i_errorCode) {
    if(DAQmxFailed(i_errorCode)) {
        // Print the error
        char errorBuff[2048] = {'\0'};

#ifdef __linux__
        DAQmxBaseGetExtendedErrorInfo(errorBuff, 2048);
#elif _WIN32
        DAQmxGetExtendedErrorInfo(errorBuff, 2048);
#endif
        cerr << "NIDAQmxTask: Error: " << errorBuff << ". \n";

        //// Stop the task
        //stopDAQTask();
        //clearDAQTask();

        return false;
    } else {
		return true;
	}
}
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* Generate the maps.                                               ********************************************** */
void NIDAQmxTask::generateMaps(void) {
    generateChannelTypesMap();
    generateTerminalConfigsMap();
}
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* Generate the mapping for channel types.                          ********************************************** */
void NIDAQmxTask::generateChannelTypesMap(void) {
    using std::map;
    using std::pair;

    channelTypes.insert(pair<string, int> ("AIVoltage", DAQChannelType::Volts));
    channelTypes.insert(pair<string, int> ("AICurrent", DAQChannelType::Amps));
}
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* Generate the mapping for terminal configurations.                ********************************************** */
void NIDAQmxTask::generateTerminalConfigsMap(void) {
    using std::map;
    using std::pair;

    terminalConfigs.insert(pair<string, int> ("Default", DAQTerminalConfig::Default));
    terminalConfigs.insert(pair<string, int> ("Diff", DAQTerminalConfig::Diff));
}
/* *********************************************************************************************************************** */
