#ifndef TST_CHIP8CASE_H
#define TST_CHIP8CASE_H
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "chip8.h"

using namespace testing;
TEST(Chip8Suite, LoadFile_Valid){
    // Arrange
    CHIP8 test_chip = CHIP8();

    // Act& Assert
    EXPECT_NO_THROW(test_chip.load_program("../../white_rabbit.ch8"));
}
TEST(Chip8Suite, LoadFile_Invalid){
    // Arrange
    CHIP8 test_chip = CHIP8();

    // Act& Assert
    EXPECT_ANY_THROW(test_chip.load_program("../../not_a_file.ch8"));
}
#endif // TST_CHIP8CASE_H
