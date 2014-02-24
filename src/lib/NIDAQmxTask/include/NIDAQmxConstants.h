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


/*
 * Include file containing conversion between NIDAQmx defines and type-safe enums.
 */

#ifndef __NIDAQMXCONSTANTS_H__
#define __NIDAQMXCONSTANTS_H__

#ifdef __linux__ 
    #include <NIDAQmxBase.h>
#elif _WIN32
    #include <NIDAQmx.h>
#endif

namespace nidaqmx {
    /**
     * Enum to provide interface conversion for NIDAQmx channel types.
     * Existing channel types include Vols, Amps, etc.
     */
    struct DAQChannelType {
    public:
        enum Type  {
            Volts = DAQmx_Val_Volts,
            Amps = DAQmx_Val_Amps
        };

        Type t_;
        DAQChannelType(Type t) : t_(t) {}
        operator Type () const {return t_;}

    private:
       //prevent automatic conversion for any other built-in types such as bool, int, etc
       template<typename T>
       operator T () const;
    };


    /**
     * Enum to provide interface conversion for NIDAQmx terminal configurations.
     * Existing terminal configurations include Default, Differential, etc.
     */
    struct DAQTerminalConfig {
    public:
        enum Type  {
            Default = DAQmx_Val_Cfg_Default,
            Diff = DAQmx_Val_Diff
        };

        Type t_;
        DAQTerminalConfig(Type t) : t_(t) {}
        operator Type () const {return t_;}

    private:
       //prevent automatic conversion for any other built-in types such as bool, int, etc
       template<typename T>
       operator T () const;
    };
}
#endif
