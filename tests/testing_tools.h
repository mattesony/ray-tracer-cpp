#ifndef TESTS_TESTING_TOOLS_H_
#define TESTS_TESTING_TOOLS_H_

#include <Eigen/Eigen>

#include "gmock/gmock.h"

using Eigen::Vector4f;
using ::testing::FloatNear;

void compareVectors(const Vector4f& result, const Vector4f& expected) {
  for (int i = 0; i < 4; i++) {
    ASSERT_THAT(result(i), FloatNear(expected(i), 0.0001));
  }
}
void compareColors(const Vector3f& result, const Vector3f& expected) {
  for (int i = 0; i < 3; i++) {
    ASSERT_THAT(result(i), FloatNear(expected(i), 0.0001));
  }
}

#endif  // TESTS_TESTING_TOOLS_H_
