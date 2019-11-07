#include <gtest/gtest.h>

using namespace std;

int main(int argc, char **argv) {
  printf("Hello there! You have selected the debug target. I'll now run tests.\n");
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
