# Point Cloud Segmentation
The request of the assignment was to segment a point cloud taken from the famous *Semantic-Kitti* dataset using **PointNet** ([*Qi et al.*](https://arxiv.org/abs/1612.00593)).
In particular, the original dataset counts about 30 labels, but in this assignment we had to remap them to only 3 labels:
- *Traversable* (road, parking, sidewalk, ecc.)
- *Not-Traversable* (cars, trucks, fences, trees, people, objects)
- *Unknown* (outliers)

The main request was to complete the definition of the `PointNet` and `PointNetSeg` modules by implementing the
`__init__` and `forward` methods. I used as reference for the original model the GitHub repository that you can find [here](https://github.com/fxia22/pointnet.pytorch/blob/master/pointnet/model.py).

![image](http://stanford.edu/~rqi/pointnet/images/pointnet.jpg)
