본 예제는 zed example 과 Nicolai Nielsen Youtube 채널을 보며 따라만들었습니다.
- https://github.com/stereolabs/zed-sdk
- https://www.youtube.com/@NicolaiAI

# System
- **Orin AGX Developer Board**
- **ZED 1 Camera**

# Need
- **jetpack 5.1**
- **CMake 3.16**
- **C++ 17**
- **CuDA 11.4**
- **OpenCV 4.7**
- **fmt**
- **zed(lib)**

# Use
## inside of example folder you want to build

- **example 1**
  - OpenCV uses CPU
  - OpenCV Mat 사용법

- **example 2**
  - OpenCV uses GPU
  - OpenCV GpuMat 사용법

- **example 3**
  - OpenCV with ZED 1 Camera
  - Zed Mat -> OpenCV Mat -> OpenCV GpuMat 사용법
  - zed 1 카메라 스트리밍 및 이미지 처리 방법

- **example 4**
  - writing..
  - writing..
  
## 코드 사용법
```
  mkdir build && cd build
  cmake ..
  make -j {core num}

  ./example {example num}
```