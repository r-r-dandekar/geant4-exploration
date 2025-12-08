# Installing Geant4 on Linux
Performed on Ubuntu 22.04.1 LTS (with GUI)

I'm doing everything inside directory \~/CSAT/geant4-exploration
Will refer to this directory as /base/dir/ here.

Following steps from:
https://groups.google.com/g/adcs-csat-current/c/CghA1wsCbLM


## Install Prerequisites
`sudo apt-get install cmake cmake-curses-gui gcc g++ libexpat1-dev libxmu-dev libmotif-dev freeglut3-dev`

## Download and Extract Geant4's .tar.gz
I downloaded Linux-g++11.5.0-Alma9.tar.gz from https://geant4.web.cern.ch/download/11.4.0.html

Extract:
`cd /base/dir/`
`tar -zvf Linux-g++11.5.0-Alma9.tar.gz ./`
This creates a directory Geant4-11.4-Linux