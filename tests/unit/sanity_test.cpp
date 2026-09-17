#include <gtest/gtest.h>

// Smoke test confirming the CMake + GoogleTest harness is wired up
// correctly. Replace/delete once real tests exist for core/net/storage.
TEST(Sanity, BuildIsWorking) {
    EXPECT_EQ(1 + 1, 2);
}
