#include <sl/Camera.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <iostream>

void Information(sl::Camera & zed) {
  auto camera_info = zed.getCameraInformation();
  std::cout << "ZED Model                 : " << camera_info.camera_model  << std::endl;
  std::cout << "ZED Camera INPUT FPS      : " << zed.getInitParameters().camera_fps  << std::endl;
  std::cout << "ZED Camera Resolution     : " << 
    camera_info.camera_configuration.resolution.width  << "x" << 
    camera_info.camera_configuration.resolution.height << std::endl;
}

void Processing(sl::Camera & zed, sl::ERROR_CODE returned_state, cv::String win_name) {

  sl::Mat image;
  sl::VIEW view_mode = sl::VIEW::LEFT;

  char   key  = ' ';
  while (key != 'q') {

    returned_state = zed.grab();

    if (returned_state == sl::ERROR_CODE::SUCCESS) {
      
      zed.retrieveImage(image, view_mode);

      // Convert sl::Mat to cv::Mat (share buffer)
      cv::Mat cvImage(image.getHeight(), image.getWidth(), 
        (image.getChannels() == 1) ? CV_8UC1 : CV_8UC4, image.getPtr<sl::uchar1>(sl::MEM::CPU));

      cv::cuda::GpuMat imgGPU;

      imgGPU.upload(cvImage);
      if (imgGPU.empty()) std::cout << "Could not load in image!" << std::endl;

      cv::cuda::bilateralFilter(imgGPU, imgGPU, 20, 70, 70);

      imgGPU.download(cvImage);

      cv::imshow(win_name, cvImage);

    } else {

      std::cout << "Error during capture : "<< returned_state << std::endl;
      break;
    }

    key = cv::waitKey(5);
  }
}


int main()
{  
  sl::Camera zed;

  sl::InitParameters init_parameters;
  init_parameters.depth_mode = sl::DEPTH_MODE::NONE;
  init_parameters.sdk_verbose = true;

  cv::String win_name = "ZED_1";
  cv::namedWindow(win_name);
  
  //camera open
  auto returned_state  = zed.open(init_parameters);
  if ( returned_state != sl::ERROR_CODE::SUCCESS)
  {
    std::cout <<"Camera Open"<< returned_state<< "Exit program."<< std::endl;
    return EXIT_FAILURE;
  }

  Information(zed);
  Processing(zed, returned_state, win_name);

  zed.close();
  return EXIT_SUCCESS;
}