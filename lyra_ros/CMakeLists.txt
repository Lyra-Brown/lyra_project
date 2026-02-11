cmake_minimum_required(VERSION 3.8)
project(lyra_ros)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(lyra_lib REQUIRED)

add_executable(lyra_node src/lyra_node.cpp)

target_link_libraries(lyra_node
  rclcpp::rclcpp
  lyra_lib::lyra_general_lib
)

install(TARGETS lyra_node DESTINATION lib/${PROJECT_NAME})
ament_package()