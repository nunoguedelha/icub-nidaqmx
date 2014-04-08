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
 * \defgroup icub_NIDAQmxReader NIDAQmxReader
 * 
 * The NIDAQmxReader is a module which acquires data from a National Instruments data acquisition (DAQ) card and outputs it on two YARP ports.
 * 
 * \section intro_sec Description
 * This module relies on the NIDAQmxTask C++ wrapper for the National Instruments proprietary NIDAQmx library.
 * It invokes the API methods defined in the NIDAQmxTask API to initialise, run, stop and clear DAQ tasks.
 *
 * Below is a block diagram showing the architecture of a NIDAQmx system:
 * \image html DAQSystemArch.png "NIDAQmx System architecture."
 * \image latex DAQSystemArch.pdf "NIDAQmx System architecture."
 *
 * 
 * \section lib_sec Libraries
 * The NIDAQmxReader depends on standard YARP libraries.
 * 
 * The module also depends on the NIDAQmxTask C++ wrapper for the NIDAQmx library.
 * 
 * 
 * \section parameters_sec Parameters
 * <b>Command-line Parameters</b>
 *     - <i>name</i>: The module name.
 *     - <i>period</i>: The module period in seconds.
 *     - <i>robot</i>: The robot on which the module will run.
 *  
 * <b>Configuration File Parameters </b>
 *     - <i>name</i>: The module name.
 *     - <i>period</i>: The module period in seconds.
 *     - <i>robot</i>: The robot on which the module will run.
 *     - <i>deviceName</i>: The DAQ device name.
 *     - <i>taskName</i>: The DAQ task name.
 *     - <i>channels</i>: The physical channels to sample.
 *     - <i>channelType</i>: The physical channel type - (see http://zone.ni.com/reference/en-XX/help/370471W-01/TOC8.htm).
 *     - <i>terminalConfig</i>: The terminal configuration mode for each channel - (see http://zone.ni.com/reference/en-XX/help/370466V-01/measfunds/connectaisigs/).
 *     - <i>minVals</i>: The minimum values to be read for each channel.
 *     - <i>maxVals</i>: The maximum values to be read for each channel.
 *     - <i>samplesPerChannel</i>: The number of samples to read per channel.
 *     - <i>samplingRate</i>: The sampling rate in Hz.
 *     - <i>timeout</i>: The sampling timeout in ms.
 *     - <i>bufferSize</i>: The sampling buffer size.
 *     - <i>scales</i>: The calibration scales.
 *     - <i>calibMatrix</i>: The calibration matrix.
 *  
 * 
 * \section portsc_sec Ports Created
 * <b>Output ports </b>
 * The NIDAQmxReader creates the following output ports:
 *     - /NIDAQmxReader/data/analog:o [yarp::sig::Vector]  [default carrier:tcp]: This port outputs the analog sensor values (Volts, Amps, etc).
 *     - /NIDAQmxReader/data/real:o [yarp::sig::Vector]  [default carrier:tcp]: This port outputs the real sensor values (Newtons, Newton millimeters, etc).
 * 
 * 
 * \section conf_file_sec Configuration Files
 * The DAQ task configuration is fairly cumbersome and requires many parameters.
 * The NIDAQmxReader therefore takes a mandatory configuration file confNIDAQmxReader.ini which must be placed in its context (NIDAQmxReader).
 * The module will not run if the configuration file does not exist.
 * This is because it would be impossible to define default parameters for the DAQ task.
 * This file defines all the afore-mentioned parameters and can be modified to suit your needs.
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
 * This file can be edited at contrib/src/dataAcquisition/NIDAQmx/src/modules/include/NIDAQmxReaderModule.h.
 */

#ifndef __NIDAQMXREADERMODULE_H__
#define __NIDAQMXREADERMODULE_H__

#include <vector>

#include <yarp/os/RFModule.h>
#include <yarp/os/BufferedPort.h>
#include <yarp/os/Stamp.h>
#include <yarp/sig/Vector.h>

#include <NIDAQmxTask/include/NIDAQmxTask.h>


/**
 * The NIDAQmxReaderModule is a module which reads data acquired from a sensor using a National Instruments DAQ card.
 */
class NIDAQmxReaderModule : public yarp::os::RFModule {
    private:
        /* ******* Module attributes                             ******* */
        /**
         * The module refresh period.
         */
        double period;

        /**
         * The module name.
         */
        std::string moduleName;
        /**
         * The robot name.
         */
        std::string robotName;


        /* ******* DAQ task config object                        ******* */
        /**
         * The DAQ Task configuration object.
         * This object is passed to the NIDAQmxTask constructor.
         */
        nidaqmx::NIDAQmxTaskParams DAQTaskConfig;

        /* ******* DAQ task objects                              ******* */
        /**
         * The NIDAQmxTAsk object.
         */
        nidaqmx::NIDAQmxTask *DAQTask;
        
        /* ****** Ports                                         ****** */
        /** 
         * Output port for sensor analog values. 
         */
        yarp::os::BufferedPort<yarp::sig::Vector> portNIDAQmxReaderOutAnalog;

        /** 
         * Output port for sensor real values.
         */
        yarp::os::BufferedPort<yarp::sig::Vector> portNIDAQmxReaderOutReal;

        /** 
         * The port timestamp. 
         */
        yarp::os::Stamp portStamp;

        /* ****** Debug attributes                              ****** */
        std::string dbgTag;
        
    public:
        /**
         * Default constructor.
         */
        NIDAQmxReaderModule();
        virtual ~NIDAQmxReaderModule();
        virtual double getPeriod();
        virtual bool updateModule();
        virtual bool configure(yarp::os::ResourceFinder &rf);
        virtual bool respond(const yarp::os::Bottle &command, yarp::os::Bottle &reply);
        virtual bool interruptModule();
        virtual bool close();

    private:
        void freeMemory(void);

};

#endif

