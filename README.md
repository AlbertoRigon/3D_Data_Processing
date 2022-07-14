# Point Cloud Segmentation
The request of the assignment was to segment a point cloud taken from the famous *Semantic-Kitti* dataset using **PointNet** ([*Qi et al.*](https://arxiv.org/abs/1612.00593)).
In particular, the original dataset counts about 30 labels, but in this assignment we had to remap them to only 3 labels:
- *Traversable* (road, parking, sidewalk, ecc.)
- *Not-Traversable* (cars, trucks, fences, trees, people, objects)
- *Unknown* (outliers)

The main request was to complete the definition of the `PointNet` and `PointNetSeg` modules by implementing the
`__init__` and `forward` methods. I used as reference for the original model the GitHub repository that you can find [here](https://github.com/fxia22/pointnet.pytorch/blob/master/pointnet/model.py).

### Experiments
I made two different experiments:
1. Remove the third and fourth MLPs (i.e., `MLP(256,128)` and `MLP(128, self.classes)`) from the `PointNetSeg` model and replace it by directly mapping the feature maps of size 256 to the size equal to the number of classes (i.e., by adding instead a `MLP(256, self.classes)`)
2. Add two MLPs `MLP(64,64)` to the `PointNet` model before `MLP(64,128)` and another MLP `MLP(128,128)` to `PointNetSeg` before `MLP(128, self.classes)`

### Results

<div align="center">

| **Architecture** 	| baseline 	| Experiment 1 	| Experiment 2 	|
|:----------------:	|:--------:	|:------------:	|:------------:	|
|  test accuracy   	|  92.083  	|    83.889    	|    91.7465   	|
|  total time (s)  	|   13.06  	|     13.04    	|     12.93    	|
|   avg time (s)   	|   0.43   	|     0.43     	|     0.43     	|

</div>

![image](http://stanford.edu/~rqi/pointnet/images/pointnet.jpg)
