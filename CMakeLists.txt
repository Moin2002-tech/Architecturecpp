cmake_minimum_required(VERSION 4.2)
project(ArchitecturesInC__)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD 17)
set(TORCH_CUDA_ARCH_LIST "7.5")
set(CAFFE2_USE_CUDNN 9)

find_package(SDL3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)


add_executable(ArchitecturesInC__ src/ModelViewControllerArchitecture/main.cpp
        #external/third_party/doctest.cpp
       # external/third_party/doctest.hpp
        include/ModelViewControllerArchitecture/SnakeAI.hpp
        src/ModelViewControllerArchitecture/SnakeAI.cpp
        include/ModelViewControllerArchitecture/Utils.h
)

find_package(SDL3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)




find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)


target_include_directories(ArchitecturesInC__ PRIVATE
        "${CMAKE_SOURCE_DIR}/external/libtorch/include"
        "${CMAKE_SOURCE_DIR}/external/libtorch/include/torch/csrc/api/include"
)



target_link_libraries(ArchitecturesInC__ PRIVATE


        -Wl,--no-as-needed
        -Wl,--whole-archive
        "${CMAKE_SOURCE_DIR}/external/libtorch/lib/libtorch_cuda.so"
        "${CMAKE_SOURCE_DIR}/external/libtorch/lib/libtorch_cpu.so"
        "${CMAKE_SOURCE_DIR}/external/libtorch/lib/libtorch.so"
        -Wl,--no-whole-archive

        "${CMAKE_SOURCE_DIR}/external/libtorch/lib/libc10_cuda.so"
        "${CMAKE_SOURCE_DIR}/external/libtorch/lib/libc10.so"

        # 1. CUDA Runtime (from your toolkit)
        "/usr/local/cuda/lib64/libcudart.so"

        # 2. CUDA Driver (The one usually missing - found in system libs)
        "/usr/lib/x86_64-linux-gnu/libcuda.so.1"

        # 3. NVRTC (Compiler library)
        "/usr/local/cuda/lib64/libnvrtc.so"

        ${OpenCV_LIBS}
        # System base libs
        pthread
        dl
        m
)


set_target_properties(ArchitecturesInC__ PROPERTIES
        INSTALL_RPATH "${CMAKE_SOURCE_DIR}/external/libtorch/lib"
        BUILD_WITH_INSTALL_RPATH TRUE
)

