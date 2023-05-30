// Hough

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

cv::RNG rng(12345);

int main()
{

  cv::Mat img;
  cv::cuda::GpuMat imgGpu, gray, circlesGpu;

  std::vector<cv::Vec3f> circles;

  while(cap.isOpened()) {

    cap.read(img);
    imgGpu.upload(img);

    cv::cuda::cvtColor(imgGpu, gray, cv::COLOR_BGR2GRAY);

    // Image Filtering
    auto gaussianFilter = cv::cuda::createGaussianFilter(CV_8UC1, CV_8UC1, {3,3}, 1);
    gaussianFilter->apply(gray, gray);

    // Circle Detector
    auto circleDetection = cv::cuda::createHoughCirclesDetector(1, 100, 120, 50, 1, 50, 5);
    circleDetection->detect(gray, circlesGpu);

    circles.resize(circlesGpu.size().width);
    if(!circles.empty()) {
      circlesGpu.row(0).download(cv::Mat(circles).reshape(3,1));
    }

    for(size_t i=0; i < circles.size();i++)
    {
      int r = rng.uniform(0,255);
      int g = rng.uniform(0, 255);
      int b = rng.uniform(0,255);

      cv::Vec3i cir = circles[i];
      circle(img, cv::Point(cir[0], cir[1]), cir[2], cv::Scalar(b,g,r), 2, cv::LINE_AA);
    }
    imshow("Image", img);
    if(cv::waitKey(1) =='q') break;
  }
  cap.release();
  return 0;
}