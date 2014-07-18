#!/bin/bash

# Copy NIDAQmx headers and libs to system root so that Travis builds are correctly executed.
echo -e "Copying library and header files to system root. \n"

cd $PROJ_ROOT
sudo cp -R ./nidaqmx/usr /

ls -al /usr/local/lib/
ls -al /usr/local/include/

echo -e "Done. \n"
