# Installing Geant4 on Linux
Performed on Ubuntu 22.04.1 LTS (with GUI)

I'm doing everything inside directory \~/CSAT/geant4-exploration. 
Will refer to this directory as /base/dir/ here.  
`cd /base/dir/`

If you're following these steps, you should probably use find-and-replace to replace every instance of /base/dir/ in this file with the path you are using.


I did this loosely following steps from:
https://groups.google.com/g/adcs-csat-current/c/CghA1wsCbLM


## Install Prerequisites
```sudo apt-get install cmake cmake-curses-gui gcc g++ libexpat1-dev libxmu-dev libmotif-dev freeglut3-dev qt6-base-dev qt6-declarative-dev```

## Download and Extract Geant4's .tar.gz
Download the *source code* from Geant4's website. At time of writing, latest version is: https://geant4.web.cern.ch/download/11.4.0.html    


Extract:
`tar -zxvf geant4-v11.4.0.tar.gz`
This creates a directory `geant4-v11.4.0`

## Build Geant4
```
cd geant4-v11.4.0
mkdir build
cd build
cmake \
  -D CMAKE_INSTALL_PREFIX="~/base/dir/geant4-v11.4.0-install" \
  -D GEANT4_BUILD_MULTITHREADED=ON \
  -D GEANT4_INSTALL_DATA=ON \
  -D GEANT4_USE_OPENGL_X11=ON \
  -D GEANT4_USE_QT=ON \
  -D GEANT4_USE_RAYTRACER_X11=ON \
  -D GEANT4_USE_SYSTEM_EXPAT=ON \
  ~/CSAT/geant4-exploration/geant4-v11.4.0
```

Compile the code using:  
`make -jn` 
where _n_ is the number of threads you want to make. On my system (which has 16 cores), I've run:  
`make -j16`  
This takes a while and might need to be run multiple times if it times out.

After it finishes successfully, run:  
`make install`

Now there should be a directory: `/base/dir/geant4-v11.4.0-install`
Go to this directory:  
`cd /base/dir/geant4-v11.4.0-install`

This will have 4 subdirectories: bin, include, lib, and share. Navigate into: `.../share/Geant4/geant4make`

There should be a .csh and a .sh file (e.g. geant4make.sh). Run the appropriate one depending on your shell using _source_. On my system,
`source geant4make.sh`

Now similarly execute the geant4.sh  in bin/ folder which sets all the required the path variables.
```
$ cd /base/dir/geant4-v11.1.1-install/bin/
$ source geant4.sh 
```

Now add the line in .bashrc file in home directory:
`export LD_LIBRARY_PATH=/base/dir/geant4-v11.4.0-install/lib/:$LD_LIBRARY_PATH`


This finishes the installation process. Some official documentation: https://geant4-userdoc.web.cern.ch/UsersGuides/InstallationGuide/html/postinstall.html

`export LD_LIBRARY_PATH=/base/dir/geant4-v11.4.0-install/lib/:$LD_LIBRARY_PATH`


## Verify Installation

To verify the installation, run an example script
```
cd /base/dir/geant4-v11.4.0/examples/basic/B1/
mkdir build
cd build
cmake ..
make
./exampleB1
```


## Adding the source to ~/.bashrc
I've made a small script to source the required file:
```
#!/usr/bin/env bash
# Note: Run this as 'source ./activate.sh'
#       Or, more precisely 'source /base/dir/activate.sh'
# The 'source' is important!
echo "Activating Geant4 Stuff..."
source /base/dir/geant4-v11.4.0-install/bin/geant4.sh
```

And then I added the following line to ~/.bashrc:
`alias sourcegeant4='source ~/base/dir/activate.sh'`

And then I run:
`source ~/.bashrc`

So now every time I want to source geant4 before I start working on something, I only need to run:
`sourcegeant4`


## Installing ROOT

CERN ROOT is not a part of Geant4, but is useful for data analysis. You can install it based on the information in the official website:
https://root.cern/install/

I installed it (on Ubuntu) using snap:
```
sudo snap install root-framework
snap run root-framework
```

To confirm installation, run `root` and then type in `new TBrowser`. It should open a window titled 'ROOT Object Browser' if it was successfully installed. You can ROOT by typing `.q`.