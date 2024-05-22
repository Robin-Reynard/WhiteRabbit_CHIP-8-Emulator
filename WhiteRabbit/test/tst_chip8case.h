#ifndef TST_CHIP8CASE_H
#define TST_CHIP8CASE_H
#include "chip8.h"
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>


using namespace testing;

TEST(Chip8Suite, Hello){
    EXPECT_TRUE(true);
}

#endif // TST_CHIP8CASE_H
