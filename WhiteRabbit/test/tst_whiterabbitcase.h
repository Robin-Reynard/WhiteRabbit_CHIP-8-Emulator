#ifndef TST_WHITERABBITCASE_H
#define TST_WHITERABBITCASE_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;
TEST(WhiteRabbitSuite, WhiteRabbitCase2)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}

#endif // TST_WHITERABBITCASE_H
