// Try OpenCV func example 

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>

#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/cudaarithm.hpp>
#include <opencv2/cudafilters.hpp>
#include <opencv2/cudabgsegm.hpp>
#include <opencv2/cudaobjdetect.hpp>
#include <opencv2/cudaoptflow.hpp>
#include <opencv2/cudastereo.hpp>
#include <opencv2/cudafeatures2d.hpp>

#include <iostream>

int main(int argc, char** argv)
{
  // Open up the webcam
  cv::VideoCapture cap(0);
  if (!cap.isOpened()) {
    std::cerr << "Camera open failed!\n";
    return -1;
  }

  // Print GPU info
  cv::cuda::printCudaDeviceInfo(0);

  // Setup variables and matrices
  cv::Mat img;
  cv::cuda::GpuMat imgGpu, mat;
  std::vector<cv::cuda::GpuMat> gpuMats;

  while(cap.isOpened()) {

    cap >> img;

    imgGpu.upload(img);

  // Core operations
    // 그레이 스케일로 변경
    cv::cuda::cvtColor(imgGpu, imgGpu, cv::COLOR_BGR2GRAY);

    // 회전 90도
    //cv::cuda::transpose(imgGpu, imgGpu);

    // 3채널로 분해
    //cv::cuda::split(imgGpu, gpuMats);
    //std::cout << gpuMats.size() << std::endl;

  // Do the operations
    // 스플릿 한거 합치기
    //cv::cuda::merge(gpuMats, imgGpu);

  // Elements wise operations
    // 채널 제한
    //cv::cuda::threshold(imgGpu, imgGpu, 100, 255, cv::THRESH_BINARY);

  // Matrix operations
    // 정규화
    //cv::cuda::normalize(imgGpu, imgGpu, 0, 1, cv::NORM_MINMAX, CV_32F);

    imgGpu.download(img);

    cv::imshow("Image", img);

    if(cv::waitKey(1) == 'q') break;
  }
  cap.release();
  return 0;
}