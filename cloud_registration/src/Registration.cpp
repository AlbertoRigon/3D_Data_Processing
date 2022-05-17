#include "Registration.h"

Registration::Registration(std::string cloud_source_filename, std::string cloud_target_filename)
{
  // TO COMPLETE

  // Loading point clound from .ply file
  open3d::io::ReadPointCloud(cloud_source_filename, source_);
  open3d::io::ReadPointCloud(cloud_target_filename, target_);
}

Registration::Registration(open3d::geometry::PointCloud cloud_source, open3d::geometry::PointCloud cloud_target)
{
  // TO COMPLETE

  // Initializing point cloud variables with current source and target point clouds
  cloud_source = source_;
  cloud_target = target_;
}

void Registration::draw_registration_result()
{
  // visualize target and source with two different colors
  // TO COMPLETE

  // Cloning source and target point cloud
  open3d::geometry::PointCloud source_clone = source_;
  open3d::geometry::PointCloud target_clone = target_;

  // Apply current transformation to the source point cloud
  source_clone.Transform(transformation_);

  // Defining source and target point cloud colors
  Eigen::Vector3d yellow(1, 0.706, 0);
  Eigen::Vector3d cyan(0, 0.651, 0.929);

  // Painting point clouds
  source_clone.PaintUniformColor(yellow);
  target_clone.PaintUniformColor(cyan);

  // Create pointers for source and target point clouds
  auto source_pointer = std::make_shared<open3d::geometry::PointCloud>(source_clone);
  auto target_pointer = std::make_shared<open3d::geometry::PointCloud>(target_clone);

  // Draw source and target point clouds
  open3d::visualization::DrawGeometries({source_pointer, target_pointer});
}

void Registration::preprocess(open3d::geometry::PointCloud pcd, double voxel_size, std::shared_ptr<open3d::geometry::PointCloud> &pcd_down_ptr, std::shared_ptr<open3d::pipelines::registration::Feature> &pcd_fpfh)
{
  // downsample, estimate normals and compute FPFH features
  // TO COMPLETE

  // Point cloud downsampling
  pcd_down_ptr = pcd.VoxelDownSample(voxel_size);

  // Normals estimation
  pcd_down_ptr->EstimateNormals(open3d::geometry::KDTreeSearchParamHybrid(2 * voxel_size, 30));

  // FPFH feature computation
  pcd_fpfh = open3d::pipelines::registration::ComputeFPFHFeature(*pcd_down_ptr, open3d::geometry::KDTreeSearchParamHybrid(5 * voxel_size, 100)); 
  
  return;
}

open3d::pipelines::registration::RegistrationResult Registration::execute_global_registration(double voxel_size)
{
  // remember to apply the transformation_ matrix to source_cloud
  // create two point cloud to contain the downsampled point cloud and two structure to contain the features
  // call the Registration::preprocess function on target and transformed source
  // execute global transformation and update the transformation matrix
  // TO COMPLETE

  // Applying transform to source point cloud
  source_.Transform(transformation_);

  // Initialize point cloud and FPFH feature pointers
  std::shared_ptr<open3d::geometry::PointCloud> source_pcd_down_ptr, target_pcd_down_ptr;
  std::shared_ptr<open3d::pipelines::registration::Feature> source_pcd_fpfh, target_pcd_fpfh;

  // Pre-processing source and target point clouds
  preprocess(source_, voxel_size, source_pcd_down_ptr, source_pcd_fpfh);
  preprocess(target_, voxel_size, target_pcd_down_ptr, target_pcd_fpfh);

  open3d::pipelines::registration::RegistrationResult result;

  double distance_threshold = 0.5 * voxel_size;

  result = open3d::pipelines::registration::FastGlobalRegistrationBasedOnFeatureMatching(
        *source_pcd_down_ptr,
        *target_pcd_down_ptr,
        *source_pcd_fpfh,
        *target_pcd_fpfh,
        open3d::pipelines::registration::FastGlobalRegistrationOption(1.4, false, true, distance_threshold));
        

  /* // Defining distance threshold
  double distance_threshold = 1.5 * voxel_size;

  // Defining pruning algorithms for the pruning step
  std::vector<std::reference_wrapper<const open3d::pipelines::registration::CorrespondenceChecker>> correspondence_checkers;

  auto correspondence_checker_edge_length = open3d::pipelines::registration::CorrespondenceCheckerBasedOnEdgeLength(0.9);
  auto correspondence_checker_distance = open3d::pipelines::registration::CorrespondenceCheckerBasedOnDistance(distance_threshold);
  
  correspondence_checkers.push_back(correspondence_checker_edge_length);
  correspondence_checkers.push_back(correspondence_checker_distance);

  // Initialize result variable
  open3d::pipelines::registration::RegistrationResult result;

  // Perform RANSAC global registration based on feature matching
  result = open3d::pipelines::registration::RegistrationRANSACBasedOnFeatureMatching(
        *source_pcd_down_ptr,
        *target_pcd_down_ptr,
        *source_pcd_fpfh,
        *target_pcd_fpfh,
        true,
        distance_threshold,
        open3d::pipelines::registration::TransformationEstimationPointToPoint(false),
        3,
        correspondence_checkers,
        open3d::pipelines::registration::RANSACConvergenceCriteria(100000, 0.999));
 */
  // Update transformation
  set_transformation(result.transformation_);

  // Update source and target point clouds
  source_ = *source_pcd_down_ptr;
  target_ = *target_pcd_down_ptr;

  // Return result
  return result;
}

open3d::pipelines::registration::RegistrationResult Registration::execute_icp_registration(double threshold, double relative_fitness, double relative_rmse, int max_iteration)
{
  // Initialize result variable
  open3d::pipelines::registration::RegistrationResult result;

  // Perform ICP registration
  result = open3d::pipelines::registration::RegistrationICP(
        source_, 
        target_, 
        threshold, 
        transformation_, 
        open3d::pipelines::registration::TransformationEstimationPointToPoint(), 
        open3d::pipelines::registration::ICPConvergenceCriteria(relative_fitness, relative_rmse, max_iteration));
  
  // Update transformation
  set_transformation(result.transformation_);

  // Return result
  return result;
}

void Registration::set_transformation(Eigen::Matrix4d init_transformation)
{
  transformation_ = init_transformation;
}

Eigen::Matrix4d Registration::get_transformation()
{
  return transformation_;
}

void Registration::write_tranformation_matrix(std::string filename)
{
  std::ofstream outfile(filename);
  if (outfile.is_open())
  {
    outfile << transformation_;
    outfile.close();
  }
}

void Registration::save_merged_cloud(std::string filename)
{
  // clone input
  open3d::geometry::PointCloud source_clone = source_;
  open3d::geometry::PointCloud target_clone = target_;

  source_clone.Transform(transformation_);
  open3d::geometry::PointCloud merged = target_clone + source_clone;
  open3d::io::WritePointCloud(filename, merged);
}
