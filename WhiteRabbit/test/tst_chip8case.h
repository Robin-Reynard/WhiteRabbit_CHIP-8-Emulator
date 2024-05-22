#ifndef TST_CHIP8CASE_H
#define TST_CHIP8CASE_H
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "chip8.h"

using namespace testing;
/*
TEST(Chip8Suite, SetOpcode){
    // Arrange
    CHIP8 mychip = CHIP8();

    // Act
    mychip.set_opcode();

    // Assert
    EXPECT_TRUE(true);
    CHIP8 mychip = CHIP8();
    mychip.emulate_cycle();

    std::cout << mychip.opcode << std::endl;
    EXPECT_TRUE(false);
}
*/
#endif // TST_CHIP8CASE_H
