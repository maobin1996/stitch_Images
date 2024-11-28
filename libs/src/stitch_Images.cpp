#include "stitch_Images.h"

using namespace cv;  
using namespace std;  
namespace fs = std::filesystem;

int ribbon_C[256][3] =
{
    { 0 , 1 , 2 },{ 0 , 2 , 4 },{ 0 , 4 , 6 },{ 0 , 5 , 8 },{ 0 , 6 , 10 },{ 0 , 7 , 12 },{ 0 , 9 , 14 },{ 0 , 10 , 15 },{ 0 , 11 , 17 },{ 0 , 12 , 19 },
    { 0 , 14 , 21 },{ 0 , 15 , 23 },{ 0 , 16 , 25 },{ 0 , 17 , 27 },{ 0 , 18 , 29 },{ 0 , 20 , 31 },{ 0 , 21 , 33 },{ 0 , 22 , 35 },{ 0 , 23 , 37 },
    { 0 , 25 , 39 },{ 0 , 26 , 41 },{ 0 , 27 , 43 },{ 0 , 28 , 45 },{ 0 , 29 , 46 },{ 0 , 31 , 48 },{ 0 , 32 , 50 },{ 0 , 33 , 52 },{ 0 , 34 , 54 },
    { 0 , 36 , 56 },{ 0 , 37 , 58 },{ 0 , 38 , 60 },{ 0 , 39 , 62 },{ 0 , 41 , 64 },{ 0 , 42 , 66 },{ 0 , 43 , 68 },{ 0 , 44 , 70 },{ 0 , 45 , 72 },
    { 0 , 47 , 74 },{ 0 , 48 , 76 },{ 0 , 49 , 77 },{ 0 , 50 , 79 },{ 0 , 52 , 81 },{ 0 , 53 , 83 },{ 0 , 54 , 85 },{ 0 , 55 , 87 },{ 0 , 57 , 89 },
    { 0 , 58 , 91 },{ 0 , 59 , 93 },{ 0 , 60 , 95 },{ 0 , 61 , 97 },{ 0 , 63 , 99 },{ 0 , 64 , 101 },{ 0 , 65 , 103 },{ 0 , 66 , 105 },{ 0 , 68 , 107 },
    { 0 , 69 , 108 },{ 0 , 70 , 110 },{ 0 , 71 , 112 },{ 0 , 72 , 114 },{ 0 , 74 , 116 },{ 0 , 75 , 118 },{ 0 , 76 , 120 },{ 0 , 77 , 122 },{ 0 , 79 , 124 },
    { 0 , 80 , 126 },{ 0 , 81 , 128 },{ 0 , 82 , 130 },{ 0 , 83 , 131 },{ 0 , 85 , 133 },{ 0 , 86 , 135 },{ 0 , 87 , 137 },{ 0 , 88 , 139 },{ 0 , 89 , 141 },
    { 0 , 91 , 143 },{ 0 , 92 , 145 },{ 0 , 93 , 146 },{ 0 , 94 , 148 },{ 0 , 95 , 150 },{ 0 , 97 , 152 },{ 0 , 98 , 154 },{ 0 , 99 , 156 },{ 0 , 100 , 158 },
    { 0 , 101 , 160 },{ 0 , 103 , 161 },{ 0 , 104 , 163 },{ 0 , 105 , 165 },{ 0 , 106 , 167 },{ 0 , 107 , 169 },{ 0 , 109 , 171 },{ 0 , 110 , 173 },{ 0 , 111 , 175 },
    { 0 , 112 , 176 },{ 0 , 113 , 178 },{ 0 , 115 , 180 },{ 0 , 116 , 182 },{ 0 , 117 , 184 },{ 0 , 118 , 186 },{ 0 , 119 , 188 },{ 0 , 120 , 190 },{ 0 , 122 , 191 },
    { 0 , 123 , 193 },{ 0 , 124 , 195 },{ 0 , 125 , 197 },{ 0 , 126 , 199 },{ 0 , 128 , 201 },{ 0 , 129 , 203 },{ 0 , 130 , 205 },{ 0 , 131 , 206 },{ 0 , 132 , 208 },
    { 0 , 134 , 210 },{ 0 , 135 , 212 },{ 0 , 136 , 214 },{ 0 , 137 , 216 },{ 0 , 138 , 218 },{ 0 , 140 , 220 },{ 0 , 141 , 221 },{ 0 , 142 , 223 },{ 0 , 143 , 225 },
    { 0 , 144 , 227 },{ 0 , 146 , 229 },{ 0 , 147 , 231 },{ 0 , 148 , 233 },{ 0 , 149 , 235 },{ 0 , 150 , 236 },{ 0 , 152 , 238 },{ 0 , 153 , 240 },{ 0 , 154 , 242 },
    { 6 , 157 , 242 },{ 6 , 157 , 242 },{ 12 , 159 , 243 },{ 19 , 162 , 243 },{ 25 , 165 , 244 },{ 31 , 167 , 244 },{ 37 , 170 , 244 },{ 43 , 173 , 245 },{ 49 , 176 , 245 },
    { 56 , 178 , 246 },{ 62 , 181 , 246 },{ 68 , 184 , 246 },{ 74 , 186 , 247 },{ 80 , 189 , 247 },{ 86 , 192 , 248 },{ 93 , 194 , 248 },{ 99 , 197 , 248 },{ 105 , 200 , 249 },
    { 111 , 203 , 249 },{ 117 , 205 , 249 },{ 124 , 208 , 250 },{ 130 , 211 , 250 },{ 136 , 213 , 251 },{ 142 , 216 , 251 },{ 148 , 219 , 251 },{ 154 , 221 , 252 },
    { 161 , 224 , 252 },{ 167 , 227 , 253 },{ 173 , 229 , 253 },{ 179 , 232 , 253 },{ 185 , 235 , 254 },{ 192 , 238 , 254 },{ 198 , 240 , 255 },{ 204 , 243 , 255 },
    { 205 , 243 , 255 },{ 205 , 243 , 255 },{ 206 , 243 , 255 },{ 206 , 244 , 255 },{ 207 , 244 , 255 },{ 208 , 244 , 255 },{ 208 , 244 , 255 },{ 209 , 244 , 255 },
    { 209 , 244 , 255 },{ 210 , 244 , 255 },{ 210 , 244 , 255 },{ 211 , 245 , 255 },{ 212 , 245 , 255 },{ 212 , 245 , 255 },{ 213 , 245 , 255 },{ 213 , 245 , 255 },
    { 214 , 245 , 255 },{ 215 , 245 , 255 },{ 215 , 245 , 255 },{ 216 , 246 , 255 },{ 216 , 246 , 255 },{ 217 , 246 , 255 },{ 218 , 246 , 255 },{ 218 , 246 , 255 },
    { 219 , 246 , 255 },{ 219 , 246 , 255 },{ 220 , 247 , 255 },{ 221 , 247 , 255 },{ 221 , 247 , 255 },{ 222 , 247 , 255 },{ 222 , 247 , 255 },
    { 223 , 247 , 255 },{ 223 , 247 , 255 },{ 224 , 247 , 255 },{ 224 , 248 , 255 },{ 225 , 248 , 255 },{ 225 , 248 , 255 },{ 226 , 248 , 255 },{ 226 , 248 , 255 },
    { 227 , 248 , 255 },{ 227 , 248 , 255 },{ 228 , 248 , 255 },{ 228 , 249 , 255 },{ 229 , 249 , 255 },{ 230 , 249 , 255 },{ 230 , 249 , 255 },{ 231 , 249 , 255 },
    { 231 , 249 , 255 },{ 232 , 249 , 255 },{ 232 , 249 , 255 },{ 233 , 250 , 255 },{ 233 , 250 , 255 },{ 234 , 250 , 255 },{ 234 , 250 , 255 },{ 235 , 250 , 255 },
    { 235 , 250 , 255 },{ 236 , 250 , 255 },{ 236 , 250 , 255 },{ 237 , 251 , 255 },{ 237 , 251 , 255 },{ 238 , 251 , 255 },{ 238 , 251 , 255 },{ 239 , 251 , 255 },
    { 239 , 251 , 255 },{ 240 , 251 , 255 },{ 240 , 251 , 255 },{ 241 , 252 , 255 },{ 241 , 252 , 255 },{ 242 , 252 , 255 },{ 243 , 252 , 255 },{ 243 , 252 , 255 },
    { 244 , 252 , 255 },{ 244 , 252 , 255 },{ 245 , 252 , 255 },{ 245 , 253 , 255 },{ 246 , 253 , 255 },{ 246 , 253 , 255 },{ 247 , 253 , 255 },{ 247 , 253 , 255 },
    { 248 , 253 , 255 },{ 248 , 253 , 255 },{ 249 , 253 , 255 },{ 249 , 254 , 255 },{ 250 , 254 , 255 },{ 250 , 254 , 255 },{ 251 , 254 , 255 },{ 251 , 254 , 255 },
    { 252 , 254 , 255 },{ 252 , 254 , 255 },{ 253 , 254 , 255 },{ 253 , 255 , 255 },{ 254 , 255 , 255 },{ 254 , 255 , 255 },{ 255 , 255 , 255 },{ 255 , 255 , 255 },
};

cv::Mat ribbon(cv::Mat image) 
{
    Mat jet_map = Mat::zeros(256, 1, CV_8UC3);
    for (int i = 0; i < 256; i++)
    {
        jet_map.at<Vec3b>(i, 0)[0] = ribbon_C[i][0];
        jet_map.at<Vec3b>(i, 0)[1] = ribbon_C[i][1];
        jet_map.at<Vec3b>(i, 0)[2] = ribbon_C[i][2];
    }
    Mat color_image;
    LUT(image, jet_map, color_image);
    return color_image;
}

stitch_Images::stitch_Images()
{
    

}

void stitch_Images::croppedImage(cv::Mat& input, cv::Mat& output)
{
    int left = 0;  
    int upper = 90;  
    int right = 1920;
    int lower = 800; 

    cv::resize(input,input,cv::Size(1920,1080));
    //std::cout<<"111: "<<std::endl;
    if (right > input.cols || lower > input.rows) {  
        std::cerr << "Crop dimensions exceed image size!" << std::endl;  
    }  
    
    cv::Rect cropRegion(left, upper, right - left, lower - upper);
    output = input(cropRegion);
    //output  = kmeans_clustering(output);
}

void stitch_Images::enhanceUnderwaterImage(const cv::Mat& input, cv::Mat& output) {
    // 1. 去雾（这里使用简单的直方图均衡化作为示例）
    cv::Mat hsv;
    cv::cvtColor(input, hsv, cv::COLOR_BGR2HSV);
    std::vector<cv::Mat> hsvChannels;
    cv::split(hsv, hsvChannels);
    cv::equalizeHist(hsvChannels[2], hsvChannels[2]); // 增强亮度通道
    cv::merge(hsvChannels, hsv);
    cv::cvtColor(hsv, output, cv::COLOR_HSV2BGR);

    // 2. 增强对比度
    cv::Mat lab;
    cv::cvtColor(output, lab, cv::COLOR_BGR2Lab);
    std::vector<cv::Mat> labChannels;
    cv::split(lab, labChannels);
    cv::equalizeHist(labChannels[0], labChannels[0]); // 增强亮度通道
    cv::merge(labChannels, lab);
    cv::cvtColor(lab, output, cv::COLOR_Lab2BGR);

    // 3. 锐化
    // cv::Mat kernel = (cv::Mat_<float>(3, 3) << 
    //     0, -1, 0, 
    //     -1, 5, -1, 
    //     0, -1, 0);
    // cv::filter2D(output, output, CV_32F, kernel);
    // cv::convertScaleAbs(output, output);
}

std::pair<std::vector<cv::Mat>, std::vector<cv::Point>> stitch_Images::randomCropImages(const cv::Mat& image, int numCrops, int cropWidth, int cropHeight, int border) 
{ 
    std::vector<cv::Mat> croppedImages; std::vector<cv::Point> cropPoints; 
    // 获取图像的尺寸 
    int height = image.rows; int width = image.cols; 
    // 设置随机种子 
    std::srand(static_cast<unsigned int>(std::time(0))); 
    for (int i = 0; i < numCrops; ++i)
    { 
        // 计算随机裁剪的起始坐标 
        int startX = std::rand() % (width - cropWidth - 2 * border) + border; 
        int startY = std::rand() % (height - cropHeight - 2 * border) + border; 
        // 进行裁剪 
        cv::Rect cropRegion(startX, startY, cropWidth, cropHeight); 
        cv::Mat croppedImage = image(cropRegion); 
        // 将裁剪后的图像添加到向量中 
        croppedImages.push_back(croppedImage); 
        // 将裁剪区域的左上角坐标添加到向量中 
        cropPoints.push_back(cv::Point(startX, startY));
    } 
    return std::make_pair(croppedImages, cropPoints);
}


cv::Point stitch_Images::templateMatch(const cv::Mat& image, const cv::Mat& templateImage, double threshold) {  
    // 1. 获取模板的尺寸  
    int h = templateImage.rows;  
    int w = templateImage.cols;  

    // 2. 在主图像中进行模板匹配  
    cv::Mat result;  
    cv::matchTemplate(image, templateImage, result, cv::TM_CCOEFF_NORMED);  

    // 3. 查找最大值和最大值位置  
    double minVal, maxVal;  
    cv::Point minLoc, maxLoc;  
    cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);  

    // 4. 判断是否绘制矩形框并返回位置  
    if (maxVal >= threshold) {  
        // 5. 在主图像上绘制矩形框标出匹配的位置  
        cv::Point topLeft = maxLoc; // 左上角坐标  
        cv::Point bottomRight(topLeft.x + w, topLeft.y + h);  
        
        // 在图像上绘制矩形框  
        cv::Mat imageWithRect = image.clone();  // 克隆主图像以保留原图  
        cv::rectangle(imageWithRect, topLeft, bottomRight, cv::Scalar(0, 255, 0), 2); // 绘制绿色矩形框  

        // 这里我们可以返回topLeft坐标，实际绘制可以根据需要在外部执行  
        return topLeft;  
    } 
    else {  
        // 如果没有找到匹配的对象，可以返回(-1, -1)表示未找到  
        return cv::Point(-1, -1);  
    }  
} 

int stitch_Images::filter_data(std::vector<std::string>& folderPath, std::vector<std::string>& sucessedimagefloder,std::vector<std::string>& failedimagefloder,std::vector<cv::Point>& trajectoryPoints)
{
    cv::Mat image1 = cv::imread(folderPath[0]);
    cv::Mat cropimage1,cropimage2;
    int ii;
    cv::Mat output1,output2;
    croppedImage(image1,cropimage1);
    // cv::imwrite("001.jpg",cropimage1);
    enhanceUnderwaterImage(cropimage1,output1);
    // cv::imwrite("002.jpg",output1);
    //cv::medianBlur(output1,output1, 5);

    std::vector<int> x_vector;
    std::vector<int> y_vector;
    for(int i = 1 ;i<folderPath.size();++i)
    {
        cv::Mat image2 = cv::imread(folderPath[i]);
        croppedImage(image2,cropimage2);
        enhanceUnderwaterImage(cropimage2,output2);
        int cropWidth = 1750;  
        int cropHeight = 500;  
        int border = 100;  
        auto result  = randomCropImages(output2, 5, cropWidth, cropHeight, border);
        std::vector<cv::Mat> croppedImages = result.first;
        std::vector<cv::Point> cropPoints = result.second;

        //cv::medianBlur(output2,output2, 5);
        for (int j = 0; j < croppedImages.size(); ++j) 
        {  
            //cv::medianBlur(croppedImages[j], croppedImages[j], 5); 
            cv::Point topLeft1 = templateMatch(output1,croppedImages[j],0.70);
            if(topLeft1.x !=-1 && topLeft1.y !=-1)
            {
                int temp_x = topLeft1.x - cropPoints[j].x;
                int temp_y = topLeft1.y - cropPoints[j].y;
                x_vector.push_back(temp_x);
                y_vector.push_back(temp_y);
            }
        }
        int pos_x = accumulate(x_vector.begin(), x_vector.end(), 0)/5;
        int pos_y = accumulate(y_vector.begin(), y_vector.end(), 0)/5;
        //std::cout<<"pos_x:"<<pos_x<<"pos_y:"<<pos_y<<std::endl;
        
        if(pos_x == 0 && pos_y==0)
        {
            failedimagefloder.push_back(folderPath[i]);
        }
        else if(abs(pos_x)>50 || abs(pos_y)>50)
        {
            failedimagefloder.push_back(folderPath[i]);
        }
        else
        {
            trajectoryPoints.push_back(cv::Point(pos_x,pos_y));
            sucessedimagefloder.push_back(folderPath[i]);
        }

        if(abs(pos_x)>5 || abs(pos_y)>5)
        {
            ii = i;
            return ii;
        }
    }
    ii = folderPath.size();
    return ii;    
}

std::vector<cv::Point> stitch_Images::combinedTrajectoryPoints(std::vector<std::vector<cv::Point>> allTrajectoryPoints)
{
    // 创建一个存储结果的 vector  
    std::vector<cv::Point> combinedTrajectoryPoints_v;
    if (!allTrajectoryPoints.empty()) {  
        combinedTrajectoryPoints_v = allTrajectoryPoints[0]; // 直接将第一个向量添加到结果中  
    } 
    // 遍历所有后续的点集  
    for (size_t i = 1; i < allTrajectoryPoints.size(); ++i) {  
        // 获取当前向量的最后一个点  
        cv::Point lastPoint = combinedTrajectoryPoints_v.back();  

        // 创建一个新的向量，用于存储累加后的结果  
        std::vector<cv::Point> modifiedPoints;  

        // 遍历当前向量并做累加  
        for (const auto& point : allTrajectoryPoints[i]) {  
            modifiedPoints.push_back(point + lastPoint); // 累加当前点和最后一个点  
        }  

        // 将修改后的点添加到最终的 combinedTrajectoryPoints  
        combinedTrajectoryPoints_v.insert(combinedTrajectoryPoints_v.end(), modifiedPoints.begin(), modifiedPoints.end());  
    }  

    return combinedTrajectoryPoints_v;
}

cv::Mat stitch_Images::blendImages(const cv::Point& positions,cv::Mat& largeImage,cv::Mat& img1) 
{  
    img1.copyTo(largeImage(Rect(positions.x, positions.y, img1.cols, img1.rows))); 
    return largeImage;
    //cv::imwrite("mer.jpg",largeImage);
}  

namespace fs = std::filesystem;

bool stitch_Images::endsWith(const std::string& str, const std::string& suffix) {
    if (str.length() >= suffix.length()) {
        return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
    }
    return false;
}

    // 设置回调函数
void stitch_Images::setProgressStringCallback(ProgressStringCallback callback) 
{
    m_progressStringCallback = callback;
}



// 尝试接拼图像  
std::string stitch_Images::stitchImages(std::vector<std::string> folderPaths,std::vector<std::string>& failedFolders,int imagetype)
{  

    if (imagetype == 0)
    {
        std::cout<<"folderPaths: "<<folderPaths.size()<<std::endl;
        std::vector<std::string> successFolders;  
    // std::vector<std::string> failedFolders;  
        std::vector<cv::Point> trajectoryPoints;
        std::vector<std::vector<cv::Point>> allTrajectoryPoints;
        int flag; 
        trajectoryPoints.push_back(cv::Point(0,0));
        successFolders.push_back(folderPaths[0]);


        if (m_progressStringCallback) {
            m_progressStringCallback("开始接拼");
        }
        do {  
        
            flag = filter_data(folderPaths, successFolders, failedFolders,trajectoryPoints);  
            
            //std::cout<<"flag: "<<flag<<std::endl;
            // std::cout<<"trajectoryPoints: "<<trajectoryPoints.size()<<std::endl;
            allTrajectoryPoints.push_back(trajectoryPoints);
            trajectoryPoints.clear();
            // 检查 newFolderSize 是否为 0，以避免访问越界  
            if (flag > 0 && flag <= folderPaths.size()) {  
                // 保留从 newFolderSize 之后的元素  
                folderPaths.erase(folderPaths.begin(), folderPaths.begin() + flag);  
            } else {  
                break; // 如果 newFolderSize <= 0，跳出循环  
            }  

        } while (!folderPaths.empty());  
        
        // 创建一个存储结果的 vector  
        std::vector<cv::Point> combinedTrajectoryPoints_v;  
        combinedTrajectoryPoints_v = combinedTrajectoryPoints(allTrajectoryPoints);

        // // 输出最终的 combinedTrajectoryPoints 中的所有点  
        // for (const auto& point : combinedTrajectoryPoints_v) {  
        //     std::cout << "(" << point.x << ", " << point.y << ")" << std::endl;  
        // }  

        int minX = INT_MAX; // 大的初始值  
        int maxX = INT_MIN; // 小的初始值  
        int minY = INT_MAX; // 大的初始值  
        int maxY = INT_MIN; // 小的初始值  

        // 遍历所有点以找出最大和最小值  
        for (const auto& point : combinedTrajectoryPoints_v) 
        {  
            if (point.x < minX) minX = point.x;  
            if (point.x > maxX) maxX = point.x;  
            if (point.y < minY) minY = point.y;  
            if (point.y > maxY) maxY = point.y;  
        }  
        
        cv::Mat img1 = cv::imread(successFolders[0]);  

        int width = img1.cols + abs(minX) + abs(maxX); 
        int height = img1.rows + abs(minY) + abs(maxY);
        largeImage = Mat::zeros(height, width, CV_8UC3);
        // 定义左上角位置int i = 1 ;i<folderPath.size();++i
        std::cout<<successFolders.size()<<std::endl;
        for (int i = 0;i<successFolders.size();++i) 
        {  
            string success_str;
            cv::Mat img = cv::imread(successFolders[i]); 
            Point pos1(abs(minX)+combinedTrajectoryPoints_v[i].x,combinedTrajectoryPoints_v[i].y+abs(minY));
            largeImage = blendImages(pos1,largeImage,img);  
           // img.copyTo(largeImage(Rect(pos1.x, pos1.y, img.cols, img.rows))); 
            // std::cout<<"i ="<<i<<std::endl;
            // cv::imshow("test",largeImage);
            // cv::waitKey(0);
             
            // success_str += successFolders[i];  // 添加当前字符串
            // if (i < successFolders.size() - 1) {
            //     success_str += ",";  // 在字符串之间添加空格
            // }
            // m_progressStringCallback(success_str +"图片组接拼(" + std::to_string(successFolders.size())+")张，接拼成功!");
        }  

        // for (int i = 0;i<failedFolders.size();++i) 
        // {  
        //     string failed_str;
        //     failed_str += failedFolders[i];
        //     if (i < failedFolders.size() - 1) {
        //         failed_str += ",";  // 在字符串之间添加空格
        //     }
        //     m_progressStringCallback(failed_str +"图片组接拼(" + std::to_string(failedFolders.size())+")张，接拼失败!");
        // } 
        
        cv::imwrite("merge_image_camera.jpg",largeImage);
    }
    else
    {
        merge_image(folderPaths);
    }
}   

void stitch_Images::ProcessImage(cv::Mat& img)
{  
    // 定义要处理的行和列范围  
    int rowStart = 0;  
    int rowEnd = 350;  
    int colStart = 505;  
    int colEnd = 517;  

    // 确保指定范围在图像的有效范围内  
    rowEnd = (std::min)(rowEnd, img.rows);  
    colEnd = (std::min)(colEnd, img.cols);  

    // 对指定区域进行处理  
    for (int i = rowStart; i < rowEnd; ++i) {  
        for (int j = colStart; j < colEnd; ++j) {  
            if (img.at<uchar>(i, j) > 130) {  
                img.at<uchar>(i, j) -= 50; // 减去50  
            }  
        }  
    }  
}

cv::Mat stitch_Images::binarizeImage(const std::string& imagePath, int threshold) 
{
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);

    ProcessImage(image);
    if (image.empty()) {
        throw std::runtime_error("Unable to load image, please check the path.");
    }

    cv::Mat binaryImage;
    cv::threshold(image, binaryImage, threshold, 255, cv::THRESH_BINARY);
    return binaryImage;

}

cv::Mat stitch_Images::combineImages(const cv::Mat& img1, const cv::Mat& img2) {  
    // 检查输入图像的有效性  
    if (img1.empty() || img2.empty()) {  
        throw std::invalid_argument("输入图像无效");  
    }  

    // 检查两幅图像的尺寸是否相同  
    if (img1.size() != img2.size() || img1.type() != img2.type()) {  
        throw std::invalid_argument("两幅图像的尺寸或类型不相同");  
    }  

    // 创建一个结果图像  
    cv::Mat result = cv::Mat::zeros(img1.size(), img1.type());  

    // 遍历每一个像素  
    for (int y = 0; y < img1.rows; ++y) {  
        for (int x = 0; x < img1.cols; ++x) {  
            // 获取 img1 和 img2 的对应像素值  
            uchar value1 = img1.at<uchar>(y, x);  
            uchar value2 = img2.at<uchar>(y, x);  

            // 如果 img1 的像素值为 0，取 img2 的对应像素值，否则取 img1 的像素值  
            result.at<uchar>(y, x) = (value1 <= 3) ? value2 : value1;  
        }  
    }  

    return result;  
}

std::shared_ptr<open3d::geometry::PointCloud>stitch_Images::depthToPointCloud(const cv::Mat& depth) {
    auto cloud = std::make_shared<open3d::geometry::PointCloud>();
    for (int y = 0; y < depth.rows; ++y) {
        for (int x = 0; x < depth.cols; ++x) {
            // 确保深度值被正确读取
            float z = depth.at<uchar>(y, x); // 假设是 CV_8U 类型
            if (z > 0) {
                cloud->points_.emplace_back(Eigen::Vector3d(x, y, z));
            }
        }
    }
    return cloud;
}

// Function to register two point clouds
open3d::pipelines::registration::RegistrationResult stitch_Images::registerPointClouds(
    std::shared_ptr<open3d::geometry::PointCloud> source,
    std::shared_ptr<open3d::geometry::PointCloud> target) {
    
    double distanceThreshold = 100.0; // Adjust as needed
    auto result = open3d::pipelines::registration::RegistrationICP(
        *source, *target, distanceThreshold, Eigen::Matrix4d::Identity(),
        open3d::pipelines::registration::TransformationEstimationPointToPoint());

    // 判断配准是否成功  
    if (!result.fitness_ || result.inlier_rmse_ > distanceThreshold) {  
        std::cerr << "配准失败: RMSE = " << result.inlier_rmse_ << std::endl;  
        // 在失败时可以选择返回一个默认的结果或处理方式  
        return result; // 可以根据需要返回原始结果或做进一步处理  
    }  

    //std::cout << "配准成功: RMSE = " << result.inlier_rmse_ << std::endl;  

    return result;
}
 

std::shared_ptr<open3d::geometry::PointCloud> stitch_Images::mergePointClouds(
    const std::shared_ptr<open3d::geometry::PointCloud>& cloud1,
    const std::shared_ptr<open3d::geometry::PointCloud>& cloud2) {
    
    auto mergedCloud = std::make_shared<open3d::geometry::PointCloud>();
    *mergedCloud += *cloud1; // 合并第一个点云
    *mergedCloud += *cloud2; // 合并第二个点云
    return mergedCloud;
}

// Function to convert a point cloud to a depth image  
cv::Mat stitch_Images::pointCloudToDepthImage(const open3d::geometry::PointCloud& cloud, int width, int height) {  
    cv::Mat depthImage = cv::Mat::zeros(height, width, CV_8U);  
    for (const auto& point : cloud.points_) {  
        int x = static_cast<int>(point[0]);  
        int y = static_cast<int>(point[1]);  
        float z = static_cast<float>(point[2]);  
        if (x >= 0 && x < width && y >= 0 && y < height) {  
            depthImage.at<uchar>(y, x) = static_cast<uchar>(z); // Normalize z to fit in uchar  
        }  
    }  
    return depthImage;  
} 


Eigen::Matrix4d stitch_Images::combineTransformations(const std::vector<Eigen::Matrix4d>& transformations) {
    Eigen::Matrix4d combined = Eigen::Matrix4d::Identity();
    for (const auto& transform : transformations) {
        combined = transform * combined; // 注意变换顺序
    }
    return combined;
}

std::vector<Eigen::Matrix4d> stitch_Images::registerAllPointClouds(
    const std::shared_ptr<open3d::geometry::PointCloud>& cloud1,
    const std::vector<std::shared_ptr<open3d::geometry::PointCloud>>& clouds) {
    
    std::vector<Eigen::Matrix4d> transformationMatrices;

    // 第一个点云与目标点云的匹配
    auto result1 = registerPointClouds(clouds[0], cloud1);
    transformationMatrices.push_back(result1.transformation_);

    // 对后续点云进行连续匹配
    for (size_t i = 1; i < clouds.size(); ++i) {
        auto result = registerPointClouds(clouds[i], clouds[i - 1]);
        transformationMatrices.push_back(result.transformation_);
    }

    // 计算相对于 cloud1 的最终转换矩阵
    std::vector<Eigen::Matrix4d> finalTransforms;
    for (size_t i = 0; i < transformationMatrices.size(); ++i) {
        if (i == 0) {
            finalTransforms.push_back(transformationMatrices[i]); // cloud2 到 cloud1
        } else {
            Eigen::Matrix4d combinedTransform = combineTransformations(
                std::vector<Eigen::Matrix4d>(transformationMatrices.begin(), 
                                              transformationMatrices.begin() + i + 1));
            finalTransforms.push_back(combinedTransform);
        }
    }

    return finalTransforms;
}

std::pair<double, double> stitch_Images::GetMinXY(const std::shared_ptr<open3d::geometry::PointCloud>& pointCloud) {  
    if (!pointCloud || pointCloud->points_.empty()) 
    {  
        std::cerr << "点云为空，无法获取最小值。" << std::endl;  
        return {0.0, 0.0}; // 或者返回一个错误值  
    }  

    double min_x = 1e10;  // 一个较大的常数值
    double min_y = 1e10;  // 一个较大的常数值
    const auto& points = pointCloud->points_;  
    for (const auto& point : points) {  
        min_x = (std::min)(min_x, point[0]);  
        min_y = (std::min)(min_y, point[1]);  
    }  

    return {min_x, min_y};  
}

 // 获取点云的最大 x 和 y 值  
std::pair<double, double> stitch_Images::GetMaxXY(const std::shared_ptr<open3d::geometry::PointCloud>& pointCloud) {  
    if (!pointCloud || pointCloud->points_.empty()) {  
        std::cerr << "点云为空，无法获取最大值。" << std::endl;  
        return {0.0, 0.0}; // 返回一个错误值  
    }  

    double max_x = 0;  
    double max_y = 0;  

    for (const auto& point : pointCloud->points_) {  
        max_x = (std::max)(max_x, point[0]);  
        max_y = (std::max)(max_y, point[1]);  
    }  

    return {max_x, max_y};  
}

// 偏移点云使得坐标均为正  
void stitch_Images::ShiftPointCloudToPositive(std::shared_ptr<open3d::geometry::PointCloud>& pointCloud,double min_x,double min_y)
{  
    if (!pointCloud || pointCloud->points_.empty())
    {  
       // std::cerr << "点云为空，无法进行偏移。" << std::endl;  
    }  

    // 获取最小坐标值  
    //auto [min_x, min_y] = GetMinXY(pointCloud);  

    // 计算偏移量，如果最小值小于0，进行偏移  
    double offset_x = min_x < 0 ? -min_x : 0.0;  
    double offset_y = min_y < 0 ? -min_y : 0.0;  

    // 应用偏移量  
    auto& points = pointCloud->points_;  
    for (auto& point : points) {  
        point[0] += offset_x;  
        point[1] += offset_y;  
    }  

    //std::cout << "点云已偏移，确保坐标值均为正。" << std::endl;  
} 


// void stitch_Images::setProgressStringCallback(ProgressStringCallback callback) 
// {
//     m_progressStringCallback = callback;
// }


void stitch_Images::merge_image(std::vector<std::string>& folderPaths)
{
    cv::Mat binaryImg1 = binarizeImage(folderPaths[0], 128);
    std::shared_ptr<open3d::geometry::PointCloud> cloud1 = depthToPointCloud(binaryImg1);
    std::vector<std::shared_ptr<open3d::geometry::PointCloud>> clouds;

    for (int i = 1; i < folderPaths.size(); i++)
    {
       cv::Mat binaryImg = binarizeImage(folderPaths[i], 128);
       std::shared_ptr<open3d::geometry::PointCloud> pointCloud = depthToPointCloud(binaryImg);
       clouds.push_back(pointCloud);
    }
    
    std::cout<<"clouds size is :"<<clouds.size()<<std::endl;
    std::vector<Eigen::Matrix4d> transformations = registerAllPointClouds(cloud1, clouds);

    // Load original images
    cv::Mat image1 = cv::imread(folderPaths[0], cv::IMREAD_GRAYSCALE);
    auto mergedPointCloud = depthToPointCloud(image1);
    std::vector<std::shared_ptr<open3d::geometry::PointCloud>> Transformclouds;
    for (int i = 1; i < folderPaths.size(); i++)
    {
       cv::Mat image2 = cv::imread(folderPaths[i], cv::IMREAD_GRAYSCALE);
       auto pointCloud2Original = depthToPointCloud(image2);
       //std::cout<<transformations[i-1]<<std::endl;

       pointCloud2Original->Transform(transformations[i-1]);
       Transformclouds.push_back(pointCloud2Original);
       mergedPointCloud = mergePointClouds(mergedPointCloud, pointCloud2Original);
    }

    // mergedPointCloud->PaintUniformColor(Eigen::Vector3d(0, 1, 0)); // Green
    // open3d::visualization::DrawGeometries({mergedPointCloud});
    // 获取 min_x 和 min_y  
    auto [minX, minY] = GetMinXY(mergedPointCloud);  
    // 偏移点云  
    ShiftPointCloudToPositive(mergedPointCloud,minX,minY);
    auto [maxX, maxY] = GetMaxXY(mergedPointCloud);
    //std::cout << "最小 x: " << minX << ", 最小 y: " << minY << std::endl;  
    //std::cout << "最大 x: " << maxX << ", 最大 y: " << maxY << std::endl;

    std::vector<cv::Mat>all_TransformMats;
    cv::Mat merge_image;
    for (int i = 0; i < Transformclouds.size(); i++)
    {
        ShiftPointCloudToPositive(Transformclouds[i],minX,minY);
        cv::Mat tempimage = pointCloudToDepthImage(*Transformclouds[i], maxX,maxY);
        cv::medianBlur(tempimage, tempimage, 3); 
        all_TransformMats.push_back(tempimage);
    }
    
    merge_image = all_TransformMats[0];
    for (int i = 0; i < all_TransformMats.size()-1; i++)
    {
        merge_image = combineImages(merge_image, all_TransformMats[i+1]);
        //cv::addWeighted(merge_image, 0.5, all_TransformMats[i+1], 0.5,0, merge_image);
        std::string filename = "merge_image_" + std::to_string(i) + ".png";
    }
    cv::medianBlur(merge_image, merge_image, 3);

    std::vector<Mat>src;
    src.emplace_back(merge_image);
    src.emplace_back(merge_image);
    src.emplace_back(merge_image);
    static cv::Mat dst;
    cv::merge(src, dst);
    Mat result_0;
    result_0 = ribbon(dst);
    cv::imwrite("merge_image_sonar.png", result_0);

}

stitch_Images::~stitch_Images()
{
}
