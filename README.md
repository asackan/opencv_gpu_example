본 예제는 zed example 과 Nicolai Nielsen Youtube 채널을 보며 따라만들었습니다.
- https://github.com/stereolabs/zed-sdk
- https://www.youtube.com/@NicolaiAI

# System
- **Orin AGX Developer 보드**
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


```
  mkdir build && cd build
  cmake ..
  make -j {core num}

  ./example
  ./with_zed
```