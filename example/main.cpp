#include <iostream>
#include <opencv2/opencv.hpp>
#include "stitch_Images.h"
namespace fs = std::filesystem;
int main()
{
    stitch_Images m_stitch_Images;
    std::string directory = "C:\\Users\\mao\\Desktop\\bjxn\\test02\\feature_matching\\cpp\\test02\\test003\\test\\1";
    //std::string directory = "C:\\Users\\mao\\Desktop\\bjxn\\test02\\feature_matching\\image2\\1";
    std::vector<std::string> folderPaths;
    for (const auto& entry : fs::directory_iterator(directory)) 
    {
        if (entry.is_regular_file()) {
            std::string fileName = entry.path().filename().string();
            // 检查文件扩展名是否是图片格式
            if (m_stitch_Images.endsWith(fileName, ".jpg") || m_stitch_Images.endsWith(fileName, ".png") ||
                m_stitch_Images.endsWith(fileName, ".jpeg") || m_stitch_Images.endsWith(fileName, ".bmp")) {
                folderPaths.push_back(entry.path().string());
            }
        }
    }

    std::vector<std::string> testfloder;

    std::string image_name = m_stitch_Images.stitchImages(folderPaths,testfloder,1);

    //m_stitch_Images.merge_image(folderPaths);

}
