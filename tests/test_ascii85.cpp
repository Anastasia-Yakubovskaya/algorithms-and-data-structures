#include <gtest/gtest.h>
#include "../src/ASCII_85.h"

// Тест для кодирования
TEST(ASCII85Test, EncodeTest) {
    std::vector<unsigned char> input = {'H', 'e', 'l', 'l', 'o'};
    std::string expected = "87cURDZBb;";

    std::string result = ASCII85::encode(input);
    EXPECT_EQ(result, expected);
}

// Тест для декодирования
TEST(ASCII85Test, DecodeTest) {
    std::string input = "87cURDZBb;";
    std::vector<unsigned char> expected = {'H', 'e', 'l', 'l', 'o'};

    std::vector<unsigned char> result = ASCII85::decode(input);
    EXPECT_EQ(result, expected);
}

// Тест для кодирования и декодирования
TEST(ASCII85Test, EncodeDecodeTest) {
    std::vector<unsigned char> input = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    std::string encoded = ASCII85::encode(input);
    std::vector<unsigned char> decoded = ASCII85::decode(encoded);

    EXPECT_EQ(decoded, input);
}

// Тест для пустого ввода
TEST(ASCII85Test, EmptyInputTest) {
    std::vector<unsigned char> input = {};
    std::string encoded = ASCII85::encode(input);
    std::vector<unsigned char> decoded = ASCII85::decode(encoded);

    EXPECT_TRUE(encoded.empty());
    EXPECT_TRUE(decoded.empty());
}

// Тест для некорректного ввода
TEST(ASCII85Test, InvalidInputTest) {
    std::string invalidInput = "Invalid!@#";

    EXPECT_THROW({
        ASCII85::decode(invalidInput);
    }, std::invalid_argument);
}
