# CMakeList.txt : CMake project for UEDumper, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("UE-study")

file(GLOB_RECURSE main CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}/*.hpp ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}/*.cpp)

add_library(${PROJECT_NAME} SHARED ${main})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

