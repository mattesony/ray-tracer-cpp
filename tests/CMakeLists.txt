find_package(GTest REQUIRED)
include(GoogleTest)

add_executable (canvas_test canvas_test.cpp)
target_link_libraries (canvas_test 
 PRIVATE
  GTest::GTest
  canvas)
gtest_discover_tests(canvas_test)

add_executable (intersections_test intersections_test.cpp)
target_link_libraries (intersections_test 
 PRIVATE
  GTest::GTest
  ray
  intersection
  sphere
  transformations
  tuple)
gtest_discover_tests(intersections_test)

add_executable (light_test light_test.cpp)
target_link_libraries (light_test 
 PRIVATE
  GTest::GTest
  light
  tuple)
gtest_discover_tests(light_test)

add_executable (material_test material_test.cpp)
target_link_libraries (material_test 
 PRIVATE
  GTest::GTest
  light
  material
  tuple)
gtest_discover_tests(material_test)

add_executable (ray_test ray_test.cpp)
target_link_libraries (ray_test 
 PRIVATE
  GTest::GTest
  Eigen3::Eigen
  ray
  transformations
  tuple)
gtest_discover_tests(ray_test)

add_executable (sphere_test sphere_test.cpp)
target_link_libraries (sphere_test 
 PRIVATE
  GTest::GTest
  Eigen3::Eigen
  intersection
  material
  ray
  sphere
  transformations
  tuple)
gtest_discover_tests(sphere_test)

add_executable (transformations_test transformations_test.cpp)
target_link_libraries (transformations_test 
 PRIVATE
  GTest::GTest
  Eigen3::Eigen
  transformations
  tuple)
gtest_discover_tests(transformations_test)

add_executable (tuple_test tuple_test.cpp)
target_link_libraries (tuple_test 
 PRIVATE
  GTest::GTest
  Eigen3::Eigen
  tuple)
gtest_discover_tests(tuple_test)

add_executable (world_test world_test.cpp)
target_link_libraries (world_test 
 PRIVATE
  GTest::GTest
  Eigen3::Eigen
  light
  sphere
  world)
gtest_discover_tests(world_test)

