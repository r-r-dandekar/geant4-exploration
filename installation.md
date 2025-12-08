# Installing Geant4 on Linux
Performed on Ubuntu 22.04.1 LTS (with GUI)

I'm doing everything inside directory \~/CSAT/geant4-exploration. 
Will refer to this directory as /base/dir/ here.\n
`cd /base/dir/`

Following steps from:
https://groups.google.com/g/adcs-csat-current/c/CghA1wsCbLM


## Install Prerequisites
```sudo apt-get install cmake cmake-curses-gui gcc g++ libexpat1-dev libxmu-dev libmotif-dev freeglut3-dev qt6-base-dev qt6-declarative-dev```

## Download and Extract Geant4's .tar.gz
Download the *source code* from Geant4's website. At time of writing, latest version is: https://geant4.web.cern.ch/download/11.4.0.html\n\n


Extract:
`tar -zxvf geant4-v11.4.0.tar.gz`
This creates a directory `geant4-v11.4.0`

## Build Geant4
```cd geant4-v11.4.0
mkdir build
cd build
cmake \
  -D CMAKE_INSTALL_PREFIX="~/CSAT/geant4-exploration/geant4-v11.4.0-install" \
  -D GEANT4_BUILD_MULTITHREADED=ON \
  -D GEANT4_INSTALL_DATA=ON \
  -D GEANT4_USE_OPENGL_X11=ON \
  -D GEANT4_USE_QT=ON \
  -D GEANT4_USE_RAYTRACER_X11=ON \
  -D GEANT4_USE_SYSTEM_EXPAT=ON \
  ~/CSAT/geant4-exploration/geant4-v11.4.0```

Compile the code using
`make -jn` 
where _n_ is the number of threads you want to make. On my system (which has 16 cores), I've run:
`make -j16`