# Stereo Matching

The request of the assignment was to complete the implementation of a software used to obtain disparity maps of pairs of
images. In particular, the goal was to extend the `process()` method by implementing different functions that performed
3 **PatchMatch Stereo** ([*Bleyer et al.*](http://www.bmva.org/bmvc/2011/proceedings/paper14/paper14.pdf)) phases:
- *Spatial Propagation*
- *Disparity Perturbation*
- *View Propagation*

Notice that this implementation just finds disparities rather than planes.

### Usage

To compile open a terminal from the parent folder of ```patchmatch``` and type the following commands in order:
```
cd patchmatch
mkdir build && cd build
cmake ..
make 
```
Execute it using:
```
./patchmatch path/to/dataset
```
where `path/to/dataset` is the path of the directory containing the pair of images from which the disparity maps will be extracted.

### Results
In this section the results obtained are reported, including the left and right MSE error and the disparity maps obtained
for all datasets. 

<div align="center">

|   **Dataset**   	|   Aloe  	|  Cones  	|  Rocks1 	|
|:---------------:	|:-------:	|:-------:	|:-------:	|
|  left image MSE 	| 20.1773 	| 32.2238 	| 17.5073 	|
| right image MSE 	| 30.9049 	| 37.7625 	| 24.9337 	|

</div>

Below are reported the output left and right disparity maps obtained with the 3 datasets:

- **Aloe**
<p align="center">
  <img src="https://github.com/AlbertoRigon/3D_Data_Processing/blob/Stereo_Matching/imgs/left_aloe.png?raw=true" width="377" height="270"/>
  <img src="https://github.com/AlbertoRigon/3D_Data_Processing/blob/Stereo_Matching/imgs/right_aloe.png?raw=true" width="377" height="270"/>
</p>

- **Cones**
<p align="center">
  <img src="https://github.com/AlbertoRigon/3D_Data_Processing/blob/Stereo_Matching/imgs/left_cones.png?raw=true" width="377" height="270"/>
  <img src="https://github.com/AlbertoRigon/3D_Data_Processing/blob/Stereo_Matching/imgs/right_cones.png?raw=true" width="377" height="270"/>
</p>

- **Rocks1**
<p align="center">
  <img src="https://github.com/AlbertoRigon/3D_Data_Processing/blob/Stereo_Matching/imgs/left_rocks.png?raw=true" width="377" height="270"/>
  <img src="https://github.com/AlbertoRigon/3D_Data_Processing/blob/Stereo_Matching/imgs/right_rocks.png?raw=true" width="377" height="270"/>
</p>


