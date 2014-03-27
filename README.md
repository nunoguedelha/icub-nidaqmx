iCub NIDAQmx
============

This repository contains classes and modules to perform data acquisition from sensors that are not embodied in the iCub using National Instruments (NI) cards and proprietary libraries.
There is one iCub module which relies on a C++ wrapper of the NIDAQmx proprietary NI data acquisition API to acquire data from such sensors.


Documentation
-------------
To generate the documentation for this project run:
```bash
    doxygen conf/Doxyfile
```
from the root of the cloned repository.
The documentation will be generated in the _doc/_ directory.
