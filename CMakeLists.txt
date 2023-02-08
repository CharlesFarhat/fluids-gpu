cmake_minimum_required(VERSION 3.24)
project(fluids_gpu)

set(CMAKE_CXX_STANDARD 17)

set(WIN_SDK_LIB "C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.22000.0\\um\\x86")
set(WIN_SDK_INCLUDE "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\um")

include_directories(${WIN_SDK_INCLUDE})
link_directories(${WIN_SDK_LIB})

find_library(D3D11 d3d11)
find_library(D3COMPILER d3dcompiler)
find_library(DXGI dxgi)

add_executable(fluids_gpu WIN32 src/main.cpp src/TrackBall.cpp)
target_link_libraries(fluids_gpu ${D3D11} ${D3COMPILER} ${DXGI})
