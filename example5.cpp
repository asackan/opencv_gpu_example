// Corner Detection

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
 
cv::VideoCapture cap(0);

cv::RNG rng(12345); // random number

int main(int argc, char** argv)
{
  cv::cuda::printCudaDeviceInfo(0);

  cv::Mat img, corners;
  cv::cuda::GpuMat imgGpu, gray, cornersGpu;

  while(cap.isOpened()) {

    cap.read(img);
    imgGpu.upload(img);

    cv::cuda::cvtColor(imgGpu, gray, cv::COLOR_BGR2GRAY);

    auto cornerDetector = 
      cv::cuda::createGoodFeaturesToTrackDetector(gray.type(), 100, 0.01, 10, 3, true);
    cornerDetector->detect(gray, cornersGpu);

    cornersGpu.download(corners);

    for(int i=0; i<corners.cols;++i) {
      
      int r = rng.uniform(0,255);
      int g = rng.uniform(0,255);
      int b = rng.uniform(0,255);
      cv::Point2f point = corners.at<cv::Point2f>(0, i);
      circle(img, point, 6, cv::Scalar(b,g,r), 2, 8); 
    }

    imshow("Image", img);

    if(cv::waitKey(1) == 'q') break;
  }
  cap.release();
  return 0;
}