#!/bin/bash

# Copy NIDAQmx headers and libs to system root so that Travis builds are correctly executed.
sudo cp -R ./usr /
