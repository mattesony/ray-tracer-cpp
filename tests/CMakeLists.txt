find_package(GTest REQUIRED)

add_executable (canvas_test canvas_test.cpp)
target_link_libraries (canvas_test 
 PRIVATE
  GTest::GTest
  canvas)

include(GoogleTest)
gtest_discover_tests(canvas_test)

