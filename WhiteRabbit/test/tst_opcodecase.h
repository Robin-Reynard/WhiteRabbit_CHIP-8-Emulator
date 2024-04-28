#ifndef TST_OPCODECASE_H
#define TST_OPCODECASE_H

#include "opcode.h"
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <ctime>
#include <cstdlib>
#include<tuple>

using namespace testing;
using namespace Opcode;

TEST(OpcodeSuite, ExtractNNN) {
    // Arrange
    u_short opcode {0xAC56};

    // Act
    u_short nnn {Opcode::extract_NNN(opcode)};

    //Assert
    EXPECT_EQ(nnn, 0x0C56);
}

TEST(OpcodeSuite, ExtractX) {
    // Arrange
    u_short opcode {0xA598};

    // Act
    u_short x = Opcode::extract_X(opcode);

    // Assert
    EXPECT_EQ(x, 0x0005);
}

TEST(OpcodeSuite, ExtractY) {
    // Arrange
    u_short opcode {0xCB95};

    // Act
    u_short y = Opcode::extract_Y(opcode);

    // Assert
    EXPECT_EQ(y, 0x0009);
}

TEST(OpcodeSuite, Execute0x1NNN){
    // Arrange
    u_short opcode {0x1ABC};
    u_short pc {0xA349};

    // Act
    Opcode::execute_1NNN(opcode, pc);

    // Assert
    EXPECT_EQ(pc, 0x0ABC);
}

TEST(OpcodeSuite, Execute0x2NNN) {
    // Arrange
    u_short opcode {0x24B9};
    u_short pc {0xF5C2};
    u_short sp {3};
    u_short stack[16] {0x0345, 0x58A6, 0xFFAC, 0x1298};

    // Act
    Opcode::execute_2NNN(opcode, stack, sp, pc);

    // Assert
    EXPECT_EQ(sp, 4);
    EXPECT_EQ(stack[3], 0xF5C2);
    EXPECT_EQ(pc, 0x04B9);
}

TEST(OpcodeSuite, Execute0x3XKK_Skip) {
    // Arrange
    u_short opcode {0x30A5};
    u_short pc {0xA592};
    u_short V[16] {0x00A5};

    // Act
    Opcode::execute_3XNN(opcode, V, pc);

    // Assert
    EXPECT_EQ(pc, 0xA594);
}

TEST(OpcodeSuite, Execute0x3XKK_NoSkip) {
    // Arrange
    u_short opcode {0x30B3};
    u_short pc {0xA592};
    u_short V[16] {0x00A5};

    // Act
    Opcode::execute_3XNN(opcode, V, pc);

    // Assert
    EXPECT_EQ(pc, 0xA592);
}

TEST(OpcodeSuite, Execute0x4XKK_Skip) {
    // Arrange
    u_short opcode {0x3089};
    u_short pc {0xA592};
    u_short V[16] {0x00A5};

    // Act
    Opcode::execute_4XNN(opcode, V, pc);

    // Assert
    EXPECT_EQ(pc, 0xA594);
}

TEST(OpcodeSuite, Execute0x4XKK_NoSkip) {
    // Arrange
    u_short opcode {0x30A5};
    u_short pc {0xA592};
    u_short V[16] {0x00A5};

    // Act
    Opcode::execute_4XNN(opcode, V, pc);

    // Assert
    EXPECT_EQ(pc, 0xA592);
}

TEST(OpcodeSuite, Execute0x5XY0_Skip) {
    // Arrange
    u_short opcode {0x5100};
    u_short V[16] {0x3289, 0x3289};
    u_short pc {0xAABC};

    // Act
    Opcode::execute_5XY0(opcode, V, pc);

    // Assert
    EXPECT_EQ(pc, 0xAABE);
}

TEST(OpcodeSuite, Execute0x5XY0_NoSkip) {
    // Arrange
    u_short opcode {0x5100};
    u_short V[16] {0x3AC9, 0x3289};
    u_short pc {0xAABC};

    // Act
    Opcode::execute_5XY0(opcode, V, pc);

    // Assert
    EXPECT_EQ(pc, 0xAABC);
}

TEST(OpcodeSuite, Execute0x6XKK){
    // Arrange
    u_short opcode {0x609A};
    u_short V[16] {0x0082};

    // Act
    Opcode::execute_6XKK(opcode, V);

    // Assert
    EXPECT_EQ(V[0], 0x009A);
}

TEST(OpcodeSuite, Execute0x7XKK) {
    // Arrange
    u_short opcode {0x7065};
    u_short V[16] {0x0235};

    // Act
    Opcode::execute_7XKK(opcode, V);

    // Assert
    EXPECT_EQ(V[0], 0x029A);
}

TEST(OpcodeSuite, Execute0x8XY0){
    // Arrange
    u_short opcode {0x8100};
    u_short V[16] {0x2359, 0x8510};

    // Act
    Opcode::execute_8XY0(opcode, V);

    // Assert
    EXPECT_EQ(V[0], 0x2359);
    EXPECT_EQ(V[0], V[1]);
}

TEST(OpcodeSuite, Execute0x8XY1){
    // Arrange
    u_short opcode {0x8011};
    u_short V[16] {0x2580, 0xACF6};

    // Act
    Opcode::execute_8XY1(opcode, V);

    // Assert
    EXPECT_EQ(V[0], 0xADF6);
}

#endif // TST_OPCODECASE_H
