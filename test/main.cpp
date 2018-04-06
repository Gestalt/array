#include <gmock/gmock.h>
#include <iostream>

TEST(SimpleTest, Check) {
    std::cout << "test" << std::endl;
    ASSERT_TRUE(true);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
