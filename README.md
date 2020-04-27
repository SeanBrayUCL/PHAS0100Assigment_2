PHAS0100Assignment2
------------------

[![Build Status](https://travis-ci.com/MattClarkson/PHAS0100Assignment2.svg?branch=master)](https://travis-ci.com/MattClarkson/PHAS0100Assignment2)
[![Build Status](https://ci.appveyor.com/api/projects/status/5pm89ej732c1ekf0/branch/master)](https://ci.appveyor.com/project/MattClarkson/cmakecatch2)


Purpose
-------

Implement the Social Force Model from [Helbing & Molner Phys. Rev. E51, 4282 (1995)].


Build Instructions
------------------
After opening the zip folder 12007217 the project can be built using the following commands:
``` cmake
mkdir PHAS0100Assignment2-Build
cd PHAS0100Assignment2-Build
cmake ../PHAS0100Assignment2
make
```
If you want to use the VTK visualiser you need the VTK development libraries. On Ubuntu these can be installed with:
``` shell
apt-get install libvtk7-dev
```

Applications
------------------
The project contains four seperate applications.

A first example where the model is implmented for three random pedestrians ("sfmNewton_Equations_three_Pedestrians.cpp")

A second, where the model is implemented and visualised for two groups of pedestrians traveling in a corridor towards each other ("sfmVisualiseCorridorModel.cpp").

A third, where the model is implemented and visualised for for a group of pedestrians starting at one end of the two dimensional space with a target at the opposite end of the two dimensional space ("sfm_Visualiser_TargetedPedestrians.cpp").

Finally a fourth, which implements the model for a mix of targeted and directed pedestrians ("sfmVisualiser_Targeted_Directed_Pedestrians.cpp").

Each of these applications can be found in the "bin" folder after the project has been built.



