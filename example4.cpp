// Image Filter

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
 
int main(int argc, char** argv)
{
  cv::VideoCapture cap(0);

  cv::cuda::printCudaDeviceInfo(0);

  cv::Mat img;
  cv::cuda::GpuMat imgGpu;

  while(cap.isOpened()) {

    cap.read(img);
    imgGpu.upload(img);

    cv::cuda::cvtColor(imgGpu, imgGpu, cv::COLOR_BGR2GRAY);

  // Image filtering
    
    // Gaussian Filter
    auto gaussianFilter = cv::cuda::createGaussianFilter(CV_8UC1, CV_8UC1, {3,3}, 1);
    gaussianFilter->apply(imgGpu, imgGpu);

    // Laplacian Filter
    // auto laplacianFilter = cv::cuda::createLaplacianFilter(CV_8UC1, CV_8UC1, 3, 3);
    // laplacianFilter->apply(imgGpu, imgGpu);

    // Morp Filter
    // auto morpFilter = cv::cuda::createMorphologyFilter(cv::MORPH_ERODE, CV_8UC1, 6);
    // morpFilter->apply(imgGpu, imgGpu);

    imgGpu.download(img);

    imshow("Image", img);

    if(cv::waitKey(1) == 'q') break;
  }
  cap.release();
  return 0;
}