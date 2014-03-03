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



#include "NIDAQmxReaderModule.h"

#include <iostream>
#include <vector>

#include <yarp/os/Time.h>

using yarp::os::Bottle;
using namespace nidaqmx;

/* *********************************************************************************************************************** */
/* ******* Constructor                                                      ********************************************** */   
NIDAQmxReaderModule::NIDAQmxReaderModule() : RFModule() {
    dbgTag = "NIDAQmxReaderModule: ";
}
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* Destructor                                                       ********************************************** */   
NIDAQmxReaderModule::~NIDAQmxReaderModule() {
    //freeMemory();
}
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* Get Period                                                       ********************************************** */   
double NIDAQmxReaderModule::getPeriod() { return period; }
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* Configure module                                                 ********************************************** */   
bool NIDAQmxReaderModule::configure(yarp::os::ResourceFinder &rf) {
    using std::cout;
    using std::vector;
    using std::string;
    using yarp::os::Value;

    /* ****** Configure the Module                            ****** */
    // Get resource finder and extract properties
    // Module attributes
    moduleName = rf.check("name", Value("NIDAQmxReader"), "The module name.").asString().c_str();
    period = rf.check("period", 1.0).asDouble();
    robotName = rf.check("robot", Value("icub"), "The robot name.").asString().c_str();

    // Open ports
    portNIDAQmxReaderOutAnalog.open("/NIDAQmxReader/data/analog:o");
    portNIDAQmxReaderOutReal.open("/NIDAQmxReader/data/real:o");
    
    // DAQ task attributes
    size_t DAQNChannels;
    Bottle &DAQTaskConf = rf.findGroup("DAQTask");
    if (!DAQTaskConf.isNull()) {
        // DAQ device name
        DAQTaskConfig.DAQDeviceName = DAQTaskConf.check("deviceName", Value("DAQ_FT"), "The DAQ device name.").asString().c_str();
        // DAQ task name
        DAQTaskConfig.DAQTaskName = DAQTaskConf.check("taskName", Value(""), "The DAQ task name.").asString().c_str();
        // DAQ channels
        Bottle *DAQChannelsList = DAQTaskConf.find("channels").asList();
        // DAQ channel types
        Bottle *DAQChannelTypesList = DAQTaskConf.find("channelType").asList();
        // DAQ channel terminal configuration
        Bottle *DAQTerminalConfigList = DAQTaskConf.find("terminalConfig").asList();
        // DAQ minimum values foreach channel
        Bottle *DAQMinValsList = DAQTaskConf.find("minVals").asList();
        // DAQ maximum values foreach channel
        Bottle *DAQMaxValsList = DAQTaskConf.find("maxVals").asList();
        
        if (!(DAQChannelsList->isNull() || DAQChannelTypesList->isNull() || DAQTerminalConfigList->isNull()
                    || DAQMinValsList->isNull() || DAQMaxValsList->isNull())) { // Check for parameter existence
            // Get number of channels 
            DAQNChannels = DAQChannelsList->size();
            if ((DAQNChannels == DAQMinValsList->size()) && (DAQNChannels == DAQChannelTypesList->size())
                   && (DAQNChannels == DAQTerminalConfigList->size()) && (DAQNChannels == DAQMaxValsList->size())) { // Check for same number of elements
                // Initialise vectors
                DAQTaskConfig.DAQChannels = vector<string>(DAQNChannels);
                DAQTaskConfig.DAQChannelTypes = vector<string>(DAQNChannels);
                DAQTaskConfig.DAQTerminalConfig = vector<string>(DAQNChannels);
                DAQTaskConfig.DAQMinVals = vector<double>(DAQNChannels);
                DAQTaskConfig.DAQMaxVals = vector<double>(DAQNChannels);
                // Fill vector values from ini file
                for (int i = 0; i < DAQChannelsList->size(); ++i) {
                    DAQTaskConfig.DAQChannels[i] = DAQChannelsList->get(i).asString();
                    DAQTaskConfig.DAQChannelTypes[i] = DAQChannelTypesList->get(i).asString();
                    DAQTaskConfig.DAQTerminalConfig[i] = DAQTerminalConfigList->get(i).asString();
                    DAQTaskConfig.DAQMinVals[i] = DAQMinValsList->get(i).asDouble();
                    DAQTaskConfig.DAQMaxVals[i] = DAQMaxValsList->get(i).asDouble();
                }
            } else {    // Parameter lists contain different number of elements
                cout << moduleName << ": One or more parameter lists contain either too few or too many parameters. \n";
                cout << moduleName << ": Expecting lists of size equal to the number of parameters. \n";
                return false;
            }
        } else {    // Can't find one or more configuration parameters
            cout << moduleName << ": Could not find one or more configuration parameters in the config file specified under the [DAQTask] parameter group. \n";
            cout << moduleName << ": Expecting the following parameter lists: channels, channelType, terminalConfig, minVals, maxVals. \n";
            return false;
        }
    } else {    // Can't find task configuration in ini file
        cout << moduleName << ": Could not find the task configuration details [DAQTask] in the ini file provided. \n";
        cout << moduleName << ": Please refer to the documentation. \n";
        return false;
    }

    // DAQ Sampling attributes
    Bottle &DAQSamplingConf = rf.findGroup("DAQSampling");
    if (!DAQSamplingConf.isNull()) {    // Check for parameter existence
       DAQTaskConfig.DAQSamplesPerChannel = DAQSamplingConf.check("samplesPerChannel", Value("1"), "The number of samples to read per channel.").asInt();
       DAQTaskConfig.DAQSamplingRate = DAQSamplingConf.check("samplingRate", 20000, "The sampling rate in Hz.").asDouble();
       DAQTaskConfig.DAQSamplingTimeout = DAQSamplingConf.check("timeout", 10, "The sampling timeout in ms.").asDouble();
       DAQTaskConfig.DAQSamplingBufferSize = DAQSamplingConf.check("bufferSize", 100000, "The sampling buffer size.").asInt();
    } else {    // Can't find sampling configuration in ini file
        cout << moduleName << ": Could not find the sampling configuration details [DAQSampling] in the ini file provided. \n";
        cout << moduleName << ": Using default sampling configuration values. \n";
        // Using default
        DAQTaskConfig.DAQSamplesPerChannel = 1;
        DAQTaskConfig.DAQSamplingRate = 20000;
        DAQTaskConfig.DAQSamplingTimeout = 10;
        DAQTaskConfig.DAQSamplingBufferSize = 100000;
    }

    // DAQ Sensor calibration data
    Bottle &DAQSensorCalib = rf.findGroup("DAQSensorCalib");
    if (!DAQSensorCalib.isNull()) {     // Check for parameter existence
        // Sensor calibration scales
        Bottle *DAQSensorCalibScalesList = DAQSensorCalib.find("scales").asList();
        // Sensor calibration matrix
        Bottle *DAQSensorCalibMatrixList = DAQSensorCalib.find("calibMatrix").asList();

        if (!(DAQSensorCalibScalesList->isNull() || DAQSensorCalibMatrixList->isNull())) {    // Check for parameter existence
            if (DAQNChannels == DAQSensorCalibScalesList->size()
                    && DAQNChannels == (DAQSensorCalibMatrixList->size() / DAQNChannels)) {
                // Initialise vectors
                DAQTaskConfig.DAQSensorCalibScales = vector<double>(DAQNChannels);
                DAQTaskConfig.DAQSensorCalibMatrix = DoubleMatrix2D(DAQNChannels);
                // Fill vectors from ini file
                for (size_t i = 0; i < DAQNChannels; ++i) {
                    DAQTaskConfig.DAQSensorCalibScales[i] = DAQSensorCalibScalesList->get(i).asDouble();
                    DAQTaskConfig.DAQSensorCalibMatrix[i] = vector<double> (DAQNChannels);
                }

                for (size_t i = 0; i < DAQNChannels; ++i) {     // Matrix rows
                    for (size_t j = 0; j < DAQNChannels; ++j) { // Matrix cols
                        DAQTaskConfig.DAQSensorCalibMatrix[i][j] = DAQSensorCalibMatrixList->get((i*DAQNChannels)+j).asDouble();
                    }
                }
            } else {    // Invalid size of scales/calibration matrix
                cout << moduleName << ": Invalid number of elements in either the calibration scales or the calibration matrix. \n";
                cout << moduleName << ": Please check the configuration .ini file provided. \n";
                return false;
            }
        }  else {       // Can't find scales/calibration matrix
            cout << moduleName << ": Could not find the DAQ sensor calibration matrix or the calibration scales. \n";
            return false;
        }
    } else {    // Can't find calibration matrix and/or scales
        cout << moduleName << ": Could not find the DAQ sensor calibration details [DAQSensorCalib] in the ini file provided. \n";
        cout << moduleName << ": Please refer to the documentation. \n";
        return false;
    }

#if 0    
    printf("Calibration matrix: \n");
    for (DoubleMatrix2D::iterator it = DAQSensorCalibMatrix.begin(); it != DAQSensorCalibMatrix.end(); ++it) {
        for (vector<double>::iterator jt = it->begin(); jt != it->end(); ++jt) {
            printf("%f\t", *jt);
        }
        printf("\n");
    }

    printf("Scales: \n");
    for (size_t i = 0; i < DAQSensorCalibScales.size(); ++i) {
        cout << DAQSensorCalibScales[i] << "\t";
    }
    cout << "\n";

    printf("Scales: \n");
    for (size_t i = 0; i < DAQTaskConfig.DAQMinVals.size(); ++i) {
        cout << DAQTaskConfig.DAQMinVals[i] << "\t";
        cout << DAQTaskConfig.DAQMaxVals[i] << "\n";
    }
#endif


    /* ******* Build DAQ Task object.                            ******* */
    DAQTask = new NIDAQmxTask(DAQTaskConfig);    // Build task


    /* ******* Initialise the DAQ Task.                         ******* */
    if (DAQTask->initialiseDAQTask()) {
        yarp::os::Time::delay(1);
        return true;
    } else {
        return false;
    }
}
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* Update module                                                    ********************************************** */   
bool NIDAQmxReaderModule::updateModule() {
    using std::vector;
    using yarp::sig::Vector;

    /* ******* Initialise the DAQ Task.                         ******* */
    NIDAQmxResults res;
    if (DAQTask->runDAQTask(res)) {
        if (res.analogValues.size() > 0) {
            // Output data on port
            int nChannels = DAQTaskConfig.DAQChannels.size();
            int samplesPerChannel = DAQTaskConfig.DAQSamplesPerChannel;
            int totSamples = nChannels * samplesPerChannel;

            //for (size_t i = 0; i < samplesPerChannel; ++i) {
            for (size_t i = 0; i < res.analogValues.size() / nChannels; ++i) {
                // Store timestamp
                portStamp.update();

                Vector &outAnalog = portNIDAQmxReaderOutAnalog.prepare();
                Vector &outReal = portNIDAQmxReaderOutReal.prepare();
                outAnalog.clear();
                outReal.clear();

                for (int j = 0; j < nChannels; ++j) {
                    outAnalog.push_back(res.analogValues[nChannels*i+j]);
                    outReal.push_back(res.realValues[nChannels*i+j]);
                }

                // Attach timestamp
                portNIDAQmxReaderOutAnalog.setEnvelope(portStamp);
                portNIDAQmxReaderOutReal.setEnvelope(portStamp);

                // Write data
                portNIDAQmxReaderOutAnalog.write();
                portNIDAQmxReaderOutReal.write();
            }
        }
    } else {        // Could not run task, close module
        std::cerr << dbgTag << "Error: Could not run the DAQ Task. \n";

        return false;
    }

    return true;
}
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* Close module                                                     ********************************************** */   
bool NIDAQmxReaderModule::close() {
    std::cout << dbgTag << "Closing module. \n";
    
    // Stop the currently running task
    if (!DAQTask->stopDAQTask()) {
        std::cout << dbgTag << "Can't close the DAQ Task. \n";
    }
    // Clear DAQ Task 
    if (!DAQTask->clearDAQTask()) {
        std::cout << dbgTag << "Can't clear the DAQ Task. \n";
    }
    freeMemory();
 
    // Close ports
    portNIDAQmxReaderOutAnalog.close();
    portNIDAQmxReaderOutReal.close();

    std::cout << dbgTag << "Closed. \n";
    
    return true;
}
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* Interrupt module                                                 ********************************************** */   
bool NIDAQmxReaderModule::interruptModule() {
    std::cout << dbgTag << "Interrupting module. \n";
    
    // Interrupt ports
    portNIDAQmxReaderOutAnalog.interrupt();
    portNIDAQmxReaderOutReal.interrupt();

    std::cout << dbgTag << "Interrupted. \n";

    return true;
}
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* Respond to rpc calls                                             ********************************************** */   
bool NIDAQmxReaderModule::respond(const Bottle &command, Bottle &reply) {

    return true;
}
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* Delete allocated memory.                                         ********************************************** */
void NIDAQmxReaderModule::freeMemory(void) {
    if (DAQTask) {
        delete DAQTask;
    }
}
/* *********************************************************************************************************************** */
