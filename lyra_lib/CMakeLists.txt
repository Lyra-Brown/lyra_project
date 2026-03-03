cmake_minimum_required(VERSION 3.10)
project(lyra_lib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(lyra_general_lib STATIC
  src/PID.cpp
  src/omni_drive_kinematics.cpp
  src/math_utils.cpp
  src/utils.cpp
  src/CAN_tool.cpp
)

find_package(Eigen3 QUIET NO_MODULE)

target_include_directories(lyra_general_lib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

if(TARGET Eigen3::Eigen)
  target_link_libraries(lyra_general_lib PUBLIC Eigen3::Eigen)
  target_compile_options(lyra_general_lib PUBLIC -Wno-psabi)
elseif(EXISTS "/usr/include/eigen3/Eigen/Dense")
  target_include_directories(lyra_general_lib SYSTEM PUBLIC /usr/include/eigen3)
  target_compile_options(lyra_general_lib PUBLIC -Wno-psabi)
else()
  message(WARNING "lyra_lib: Eigen3 was not found. Install libeigen3-dev or provide Eigen3::Eigen.")
endif()

find_package(ament_cmake QUIET)

if(ament_cmake_FOUND)
  install(TARGETS lyra_general_lib
    EXPORT export_${PROJECT_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
  )
  install(DIRECTORY include/ DESTINATION include)

  ament_export_targets(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)
  ament_package()
else()
  message(STATUS "lyra_lib: Building in Pure CMake mode (for STM32/etc.)")
endif()