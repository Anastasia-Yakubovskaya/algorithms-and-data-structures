#include <gtest/gtest.h>
#include "ASCII_85.h"


TEST(ASCII85Test, EncodeEmptyString) {
    std::vector<unsigned char> input = {};
    std::string encoded = ASCII85::encode(input);
    EXPECT_EQ(encoded, "");
}


TEST(ASCII85Test, EncodeHello) {
    std::vector<unsigned char> input = {'h', 'e', 'l', 'l', 'o'};
    std::string encoded = ASCII85::encode(input);
    EXPECT_EQ(encoded, "BOu!rDZ");
}


TEST(ASCII85Test, DecodeEmptyString) {
    std::string input = "";
    std::vector<unsigned char> decoded = ASCII85::decode(input);
    EXPECT_TRUE(decoded.empty());
}


TEST(ASCII85Test, DecodeHello) {
    std::string input = "BOu!rDZ";
    std::vector<unsigned char> decoded = ASCII85::decode(input);
    std::string result(decoded.begin(), decoded.end());
    EXPECT_EQ(result, "hello");
}


TEST(ASCII85Test, DecodeWithZ) {
    std::string input = "zBOu!rDZ";
    std::vector<unsigned char> decoded = ASCII85::decode(input);
    std::string result(decoded.begin(), decoded.end());
    EXPECT_EQ(result, std::string(4, '\0') + "hello");
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
