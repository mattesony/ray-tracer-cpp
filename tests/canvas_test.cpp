#include "../src/canvas.h"

#include "gmock/gmock.h"

using ::testing::EndsWith;
using ::testing::StartsWith;

TEST(CanvasTest, PPMHeader) {
  Canvas canvas = Canvas(5, 3);

  std::string ppm = canvas.getPPM();

  ASSERT_THAT(ppm, StartsWith("P3\n"
                              "5 3\n"
                              "255\n"));
}

TEST(CanvasTest, ConstructingPPMPixelData) {
  Canvas canvas = Canvas(5, 3);

  Vector3f c1 = {1.5, 0, 0};
  Vector3f c2 = {0, 0.5, 0};
  Vector3f c3 = {-0.5, 0, 1};

  canvas.writePixel(0, 0, c1);
  canvas.writePixel(2, 1, c2);
  canvas.writePixel(4, 2, c3);

  std::string ppm = canvas.getPPM();

  ASSERT_THAT(ppm, EndsWith("255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
                            "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n"
                            "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n"));
}

TEST(CanvasTest, SplittingLongLinesPPM) {
  Canvas canvas = Canvas(10, 2);

  Vector3f c1 = {1.5, 0, 0};
  Vector3f c2 = {0, 0.5, 0};
  Vector3f c3 = {-0.5, 0, 1};

  // every pixel of c is set to color(1, 0.8, 0.6)

  std::string ppm = canvas.getPPM();

  ASSERT_THAT(
      ppm, EndsWith("255 204 153 255 204 153 255 204 153 255 204 153 255 204 "
                    "153 255 204\n"
                    "153 255 204 153 255 204 153 255 204 153 255 204 153\n"
                    "255 204 153 255 204 153 255 204 153 255 204 153 255 204 "
                    "153 255 204\n"
                    "153 255 204 153 255 204 153 255 204 153 255 204 153\n"));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
