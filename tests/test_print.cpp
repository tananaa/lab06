#include <gtest/gtest.h>
#include "print.hpp"
#include <sstream>

TEST(PrintTest, PrintToCout) {
    testing::internal::CaptureStdout();
    print("hello");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "hello\n");
}

TEST(PrintTest, PrintToOstream) {
    std::stringstream ss;
    print("hello", ss);
    EXPECT_EQ(ss.str(), "hello\n");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
