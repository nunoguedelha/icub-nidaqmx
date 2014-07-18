#!/bin/bash

# Copy NIDAQmx headers and libs to system root so that Travis builds are correctly executed.
echo -e "Copying library and header files to system root. \n"

cd $PROJ_ROOT
ls -al
sudo cp -R ./.nidaqmx/usr /
if [ $? -gt 0 ]; then
    echo ERROR
    exit 1
fi

ls -al /usr/local/lib/
ls -al /usr/local/include/

echo -e "Done. \n"
