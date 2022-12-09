find_package(Eigen3 REQUIRED)

add_library(canvas canvas.cpp)

target_link_libraries(canvas Eigen3::Eigen)
