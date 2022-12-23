find_package(GTest REQUIRED)
include(GoogleTest)

add_executable (canvas_test canvas_test.cpp)
target_link_libraries (canvas_test 
 PRIVATE
  GTest::GTest
  canvas)

add_executable (transformations_test transformations_test.cpp)
target_link_libraries (transformations_test 
 PRIVATE
  GTest::GTest
  Eigen3::Eigen
  transformations
  tuple)



gtest_discover_tests(canvas_test)
gtest_discover_tests(transformations_test)

