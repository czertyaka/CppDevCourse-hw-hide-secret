#include <gtest/gtest.h>

#include <string>

#include "hide-secret.hpp"

TEST(HideSecretTest, BasicTest)
{
    std::string text{"My silly password is '12345678'"};
    ASSERT_NO_THROW(hide_secret(text.data(), "12345678"));
    EXPECT_EQ(text, "My silly password is 'xxxxxxxx'");
}

TEST(HideSecretTest, SecretNotFound)
{
    std::string text{"My silly password is '12345678'"};
    ASSERT_NO_THROW(hide_secret(text.data(), "12345679"));
    EXPECT_EQ(text, "My silly password is '12345678'");
}

TEST(HideSecretTest, PossibleOutOfBounds)
{
    std::string text{"My silly password is 12345678"};
    ASSERT_NO_THROW(hide_secret(text.data(), "123456789"));
    EXPECT_EQ(text, "My silly password is 12345678");
}

TEST(HideSecretTest, EmptyText)
{
    std::string text{};
    ASSERT_NO_THROW(hide_secret(text.data(), "123456789"));
    EXPECT_EQ(text, "");
}

TEST(HideSecretTest, EmptySecret)
{
    std::string text{"My silly password is 12345678"};
    ASSERT_NO_THROW(hide_secret(text.data(), ""));
    EXPECT_EQ(text, "My silly password is 12345678");
}

TEST(HideSecretTest, NullptrText)
{
    ASSERT_NO_THROW(hide_secret(nullptr, "12345678"));
}

TEST(HideSecretTest, NullptrSecret)
{
    std::string text{"My silly password is 12345678"};
    ASSERT_NO_THROW(hide_secret(text.data(), nullptr));
    EXPECT_EQ(text, "My silly password is 12345678");
}

TEST(HideSecretTest, TextMatchesSecret)
{
    std::string text{"12345678"};
    ASSERT_NO_THROW(hide_secret(text.data(), "12345678"));
    EXPECT_EQ(text, "xxxxxxxx");
}

TEST(HideSecretTest, TextStartsWithSecret)
{
    std::string text{"12345678 is my password"};
    ASSERT_NO_THROW(hide_secret(text.data(), "12345678"));
    EXPECT_EQ(text, "xxxxxxxx is my password");
}

TEST(HideSecretTest, TextEndsWithSecret)
{
    std::string text{"12345678 is my password"};
    ASSERT_NO_THROW(hide_secret(text.data(), "password"));
    EXPECT_EQ(text, "12345678 is my xxxxxxxx");
}

TEST(HideSecretTest, SecretInTheMiddleOfText)
{
    std::string text{"12345678 is my password"};
    ASSERT_NO_THROW(hide_secret(text.data(), "is my "));
    EXPECT_EQ(text, "12345678 xxxxxxpassword");
}

TEST(HideSecret, SeveralMatches)
{
    std::string text{"123 is my password, yes, 123, and nothing else"};
    ASSERT_NO_THROW(hide_secret(text.data(), "123"));
    EXPECT_EQ(text, "xxx is my password, yes, xxx, and nothing else");
}
