#include "../src/canvas.h"

#include "gmock/gmock.h"

using ::testing::StartsWith;

TEST(CanvasTest, PPMHeader) {
  Canvas canvas = Canvas(5, 3);

  std::string ppm = canvas.getPPM();

  ASSERT_THAT(ppm, StartsWith("P3\n"
                              "5 3\n"
                              "255\n"));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
