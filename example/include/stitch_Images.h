#ifndef STITCH_IMAGES
#define STITCH_IMAGES

#ifdef STITCH_IMAGES_EXPORTS
#define STITCH_IMAGES_API __declspec(dllexport)
#else
#define STITCH_IMAGES_API __declspec(dllimport)
#endif

#include <opencv2/opencv.hpp>  
#include <opencv2/stitching.hpp>  
#include <open3d/Open3D.h>
#include <limits>
#include <filesystem>  
#include <functional>
#include <algorithm>

#include <iostream>  
#include <vector>  
#include <numeric>
using namespace cv;
using namespace std;
namespace fs = std::filesystem;  

class STITCH_IMAGES_API stitch_Images
{
private:
public:
    stitch_Images();
    using ProgressStringCallback = std::function<void(const std::string&)>;

    void croppedImage(cv::Mat& input, cv::Mat& output);
    void enhanceUnderwaterImage(const cv::Mat& input, cv::Mat& output);
    std::pair<std::vector<cv::Mat>, std::vector<cv::Point>> randomCropImages(const cv::Mat& image, int numCrops, int cropWidth, int cropHeight, int border);
    cv::Point templateMatch(const cv::Mat& image, const cv::Mat& templateImage, double threshold);
    int filter_data(std::vector<std::string>& folderPath, std::vector<std::string>& sucessedimagefloder,std::vector<std::string>& failedimagefloder,std::vector<cv::Point>& trajectoryPoints);
    std::vector<cv::Point> combinedTrajectoryPoints(std::vector<std::vector<cv::Point>> allTrajectoryPoints);
    cv::Mat blendImages(const cv::Point& positions,cv::Mat& largeImage,cv::Mat& img1);
    bool endsWith(const std::string& str, const std::string& suffix);
    
    void ProcessImage(cv::Mat& img);
    cv::Mat binarizeImage(const std::string& imagePath, int threshold);
    cv::Mat combineImages(const cv::Mat& img1, const cv::Mat& img2);
    std::shared_ptr<open3d::geometry::PointCloud>depthToPointCloud(const cv::Mat& depth);
    open3d::pipelines::registration::RegistrationResult registerPointClouds(std::shared_ptr<open3d::geometry::PointCloud> source,std::shared_ptr<open3d::geometry::PointCloud> target);
    std::shared_ptr<open3d::geometry::PointCloud> mergePointClouds(const std::shared_ptr<open3d::geometry::PointCloud>& cloud1,const std::shared_ptr<open3d::geometry::PointCloud>& cloud2);
    cv::Mat pointCloudToDepthImage(const open3d::geometry::PointCloud& cloud, int width, int height);
    Eigen::Matrix4d combineTransformations(const std::vector<Eigen::Matrix4d>& transformations);
    std::vector<Eigen::Matrix4d> registerAllPointClouds(const std::shared_ptr<open3d::geometry::PointCloud>& cloud1,const std::vector<std::shared_ptr<open3d::geometry::PointCloud>>& clouds);
    std::pair<double, double> GetMinXY(const std::shared_ptr<open3d::geometry::PointCloud>& pointCloud);
    std::pair<double, double> GetMaxXY(const std::shared_ptr<open3d::geometry::PointCloud>& pointCloud);
    void ShiftPointCloudToPositive(std::shared_ptr<open3d::geometry::PointCloud>& pointCloud,double min_x,double min_y);
    void merge_image(std::vector<std::string>& folderPaths);
    void setProgressStringCallback(ProgressStringCallback callback);
    std::string stitchImages(std::vector<std::string> folderPaths,std::vector<std::string>& failedFolders,int imagetype);
    ~stitch_Images();
public:
    std::vector<std::string> imagestring;
    cv::Mat largeImage;
private:
    ProgressStringCallback m_progressStringCallback;
};

#endif // MYCLASS_H