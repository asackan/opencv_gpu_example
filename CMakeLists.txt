CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
PROJECT(OpenCV_CuDA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(LINK_SHARED_ZED "Link with the ZED SDK shared executable" ON)

if (NOT LINK_SHARED_ZED AND MSVC)
    message(FATAL_ERROR "LINK_SHARED_ZED OFF : ZED SDK static libraries not available on Windows")
endif()

find_package(ZED 3 REQUIRED)
find_package(CUDA ${ZED_CUDA_VERSION} REQUIRED)
find_package(OpenCV REQUIRED )
find_package(fmt)

include_directories(${CUDA_INCLUDE_DIRS})
include_directories(${ZED_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${fmt_INCLUDE_DIRS})

link_directories(${ZED_LIBRARY_DIR})
link_directories(${CUDA_LIBRARY_DIRS})

if (LINK_SHARED_ZED)
    SET(ZED_LIBS ${ZED_LIBRARIES} ${CUDA_CUDA_LIBRARY} ${CUDA_CUDART_LIBRARY})
else()
    SET(ZED_LIBS ${ZED_STATIC_LIBRARIES} ${CUDA_CUDA_LIBRARY} ${CUDA_LIBRARY})
endif()

ADD_EXECUTABLE(example1 example1.cpp)
ADD_EXECUTABLE(example2 example2.cpp)
ADD_EXECUTABLE(example3 example3.cpp)
ADD_EXECUTABLE(example4 example4.cpp)
ADD_EXECUTABLE(example5 example5.cpp)
ADD_EXECUTABLE(example6 example5.cpp)

TARGET_LINK_LIBRARIES(example1 ${ZED_LIBS} ${OpenCV_LIBS} fmt::fmt)
TARGET_LINK_LIBRARIES(example2 ${ZED_LIBS} ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(example3 ${ZED_LIBS} ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(example4 ${ZED_LIBS} ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(example5 ${ZED_LIBS} ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(example6 ${ZED_LIBS} ${OpenCV_LIBS})