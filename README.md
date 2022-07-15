# Point Cloud Registration
The request of the assignment was to implement a cloud registration pipeline used to obtain the rigid-body transformation between a source and a target point clouds. In particular, the goal was to implement several different methods that performed the following tasks:
- **Point clouds pre-processing**
  - Cloud filtering
  - Downsampling
  - Normals computation
- **Global registration**
  - *Fast Point Feature Histograms* (FPFH) feature extraction and matching
  - Registration based on feature matching
- **Registration refinement**
  - *Iterative Closest Point* (ICP) algorithm
- **Point clouds visualization**

The whole code is implemented using the Open3D library. You can install it by following the tutorial [here](http://www.open3d.org/docs/release/compilation.html#ubuntu-macos).

### Usage

Compile the code by typing the following commands inside the `cloud_registration` folder:
```
mkdir build && cd build
cmake ..
make
```
To execute:
```
./registration path/to/source path/to/target path/to/output_transformation_matrix path/to/fused_cloud
```

### Results

<p align="center">
  <img src="https://github.com/AlbertoRigon/3D_Data_Processing/blob/Point_Cloud_Registration/results.png" width="500" height="500"/>
</p>


