// opencv CPU vs GPU example

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <fmt/core.h>

// Open up the webcam
cv::VideoCapture cap(0);

void cpuSpeedTest() {

  while (cap.isOpened()) {

    cv::Mat image, result;
    bool isSuccess = cap.read(image);

    if (image.empty()) fmt::println("Could not load in image!");

    cv::bilateralFilter(image, result, 20, 70, 70);

    cv::imshow("Image", result);

    char key = ' ';
    if  (key =='q') break;
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

    if (imgGPU.empty()) fmt::println("Could not load in image!");

    cv::cuda::bilateralFilter(imgGPU, imgGPU, 20, 70, 70);

    imgGPU.download(image);

    cv::imshow("Image", image);

    char key = ' ';
    if  (key =='q') break;
  }

  cap.release();
  cv::destroyAllWindows();
}

int main() {
  
  //cpuSpeedTest();
  gpuSpeedTest();

  return EXIT_SUCCESS;
}