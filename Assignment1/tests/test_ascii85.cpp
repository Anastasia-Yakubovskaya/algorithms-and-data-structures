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
    auto [decoded, error] = ASCII85::decode(input);
    EXPECT_EQ(error, ASCII85::Error::EMPTY_INPUT);
    EXPECT_TRUE(decoded.empty());
}

TEST(ASCII85Test, DecodeHello) {
    std::string input = "BOu!rDZ";
    auto [decoded, error] = ASCII85::decode(input);
    EXPECT_EQ(error, ASCII85::Error::OK);
    std::string result(decoded.begin(), decoded.end());
    EXPECT_EQ(result, "hello");
}

TEST(ASCII85Test, DecodeWithZ) {
    std::string input = "zBOu!rDZ";
    auto [decoded, error] = ASCII85::decode(input);
    EXPECT_EQ(error, ASCII85::Error::OK);
    std::string result(decoded.begin(), decoded.end());
    EXPECT_EQ(result, std::string(4, '\0') + "hello");
}

TEST(ASCII85Test, DecodeInvalidChar) {
    std::string input = "BOu!rD$"; 
    auto [decoded, error] = ASCII85::decode(input);
    EXPECT_EQ(error, ASCII85::Error::INVALID_CHAR);
}

TEST(ASCII85Test, DecodeMultipleZ) {
    std::string input = "zzBOu!rDZ"; 
    auto [decoded, error] = ASCII85::decode(input);
    EXPECT_EQ(error, ASCII85::Error::MULTIPLE_Z);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
