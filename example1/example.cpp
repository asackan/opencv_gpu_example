#include <sl/Camera.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <fmt/core.h>
#include <iostream>

// Open up the webcam
cv::VideoCapture cap(0);

void cpuSpeedTest() {

  while (cap.isOpened()) {

    cv::Mat image;
    bool isSuccess = cap.read(image);

    if (image.empty()) {
      fmt::println("Could not load in image!");
    }

    float start = cv::getTickCount();

    cv::Mat result;

    cv::bilateralFilter(image, result, 20, 70, 70);

    float end = cv::getTickCount();

    float totalTime = (end - start) / cv::getTickCount();
    int fps = ceil(1 / totalTime * 0.0001);
    fmt::println("FPS: {}", fps);

    cv::putText(result, "FPS: " + std::to_string(
      static_cast<int>(fps)), cv::Point(50, 50),
      cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0, 255, 255));
    
    cv::imshow("Image", result);

    char key = ' ';
    if(key =='q') break;
  }

  cap.release();
  cv::destroyAllWindows();
}

void gpuSpeedTest() {

  while (cap.isOpened()) {

    cv::Mat image;
    bool isSuccess = cap.read(image);

    cv::cuda::GpuMat imgGPU;

    imgGPU.upload(image);

    if (imgGPU.empty()) {
      fmt::println("Could not load in image!");
    }

    float start = cv::getTickCount();

    cv::cuda::bilateralFilter(imgGPU, imgGPU, 20, 70, 70);

    float end = cv::getTickCount();

    float totalTime = (end - start) / cv::getTickCount();
    int fps = ceil(1 / totalTime * 0.001);
    fmt::println("FPS: {}", fps);

    imgGPU.download(image);

    cv::putText(image, "FPS: " + std::to_string(
      static_cast<int>(fps)), cv::Point(50,50),
      cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0, 255, 255));
    
    cv::imshow("Image", image);

    char key = ' ';
    if(key =='q') break;
  }

  cap.release();
  cv::destroyAllWindows();
}

int main() {
  
  //cpuSpeedTest();
  gpuSpeedTest();

  return EXIT_SUCCESS;
}