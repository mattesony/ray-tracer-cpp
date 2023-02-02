add_library(canvas canvas.cpp)
target_link_libraries(canvas Eigen3::Eigen)

add_library(intersection intersection.cpp)
target_link_libraries(intersection Eigen3::Eigen)

add_library(ray ray.cpp)
target_link_libraries(ray Eigen3::Eigen)

add_library(sphere sphere.cpp)
target_link_libraries(sphere ray Eigen3::Eigen)

add_library(transformations transformations.cpp)
target_link_libraries(transformations Eigen3::Eigen)

add_library(tuple tuple.cpp)
target_link_libraries(tuple Eigen3::Eigen)
