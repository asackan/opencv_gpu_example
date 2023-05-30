// Monocular Camera Depth Estimation

#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/dnn/all_layers.hpp>
#include <vector>
 
int clip(int n, int lower, int upper) {
  return std::max(lower, std::min(n, upper));
}

std::vector<std::string> getOutputsNames(const cv::dnn::Net& net) {

  static std::vector<std::string> names;

  if (names.empty()){

    std::vector<int32_t> out_layers = net.getUnconnectedOutLayers();
    std::vector<std::string> layers_names = net.getLayerNames();

    names.resize(out_layers.size());

    for (size_t i=0; i < out_layers.size(); ++i)
      names[i] = layers_names[out_layers[i] - 1];
  }
  return names;
}

int main(int argc, char** argv)
{
  std::string file_path = "/";
  std::string model = "model name.onnx";

  // Read in the neural network form the files
  auto net = cv::dnn::readNet(file_path + model);

  if (net.empty()) return -1;

  // Run on either CPU or GPU
  net.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
  net.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA);

  cv::VideoCapture cap(0);

  while (cap.isOpened()) {

    cv::Mat image;
    cap.read(image);

    if(image.empty()) {
      cv::waitKey(0);
      std::cout << "image not available!" << std::endl;
      break;
    }

    int image_width = image.rows;
    int image_height = image.cols;

    cv::Mat blob = cv::dnn::blobFromImage(image, 1 / 255.f, cv::Size(384, 384), cv::Scalar(123.675, 116.28, 103.53), true, false);

    // Set the blob to be input to the NN
    net.setInput(blob);

    // Forward pass of the blob through the NN to get the predictions
    cv::Mat output = net.forward(getOutputsNames(net)[0]);

    // Convert Size to 384 x 384 from 1 x 384 x 384
    const std::vector<int32_t> size = { output.size[1], output.size[2] };
    output = cv::Mat(static_cast<int32_t>(size.size()), &size[0], CV_32F, output.ptr());

    cv::resize(output, output, image.size());

    // Visualize Output Image
    double min, max;
    cv::minMaxLoc(output, &min, &max);
    const double range = max - min;

    // Normalize
    output.convertTo(output, CV_32F, 1.0 / range, -(min / range));
  
    // Scaling (0 - 255)
    output.convertTo(output, CV_8U, 255.0);

    imshow("image", image);
    imshow("depth", output);

    if(cv::waitKey(1) =='q') break;
  }
  cap.release();
  cv::destroyAllWindows();
  return 0;
}