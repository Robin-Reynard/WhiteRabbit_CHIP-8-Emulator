#ifndef TST_OPCODECASE_H
#define TST_OPCODECASE_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

TEST(OpcodeSuite, OpcodeCase2)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(1));
}

#endif // TST_OPCODECASE_H
