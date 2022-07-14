# Structure from Motion

The goal of this homework is to estimate the 3D structure of a small scene from a sequence of images with some field of view overlaps. The code
for this homework was developed together with [Luca Scattolaro](https://github.com/LucaScattolaro).

### Usage

To execute the code, you need to first install the required dependencies; for debian-based distro, you can use the following command:

    sudo apt install build-essential cmake libboost-filesystem-dev libopencv-dev libomp-dev libceres-dev libyaml-cpp-dev libgtest-dev libeigen3-dev

To build the executable, execute the following inside the **sfm** directory:

    mkdir build
    cd build
    cmake ..
    make
    
Then, you can run the whole Structure from Motion pipeline as follows:

    ./basic_sfm <input data file> <output ply file>
    ./matcher <calibration parameters filename> <images folder filename><output data file> [focal length scale]

### Datasets

In the **../datasets** folder there are two simple test datasets and the corresponding calibration parameter file.






