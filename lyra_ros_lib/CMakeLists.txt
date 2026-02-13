cmake_minimum_required(VERSION 3.10)
project(lyra_ros_lib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(lyra_ros_lib STATIC
  src/default_node.cpp
)

target_include_directories(lyra_ros_lib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

find_package(ament_cmake QUIET)

if(ament_cmake_FOUND)
  install(TARGETS lyra_ros_lib
    EXPORT export_${PROJECT_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
  )
  install(DIRECTORY include/ DESTINATION include)

  ament_export_targets(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)
  ament_package()
else()
  message(STATUS "lyra_ros_lib: Building in Pure CMake mode (for STM32/etc.)")
endif()