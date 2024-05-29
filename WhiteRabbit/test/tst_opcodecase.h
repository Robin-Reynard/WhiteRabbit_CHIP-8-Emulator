#ifndef TST_OPCODECASE_H
#define TST_OPCODECASE_H

#include "opcode.h"
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <ctime>
#include <cstdlib>
#include <tuple>

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

TEST(OpcodeSuite, ExtractKK) {
    // Arrange
    u_short opcode {0xF82A};

    // Act
    u_short kk {Opcode::extract_KK(opcode)};

    // Assert
    EXPECT_EQ(kk, 0x2A);
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

TEST(OpcodeSuite, Execute0x00E0){
    // Arrange
    bool graphics[32*64] {1,1,1,0,1,1,0,1};

    // Act
    Opcode::execute_00E0(graphics);

    // Assert
    for(int i {0}; i < 32*64; i++){
        EXPECT_EQ(graphics[i], 0);
    }
}

TEST(OpcodeSuite, Execute0x00EE_StackPointerNotZero){
    // Arrange
    u_short pc {0x2153};
    byte sp {0x02};
    u_short stack[16] {0x1850, 0xABCD, 0xAD56};

    // Act
    Opcode::execute_00EE(pc, sp, stack);

    // Assert
    EXPECT_EQ(sp, 0x01);
    EXPECT_EQ(stack[2], 0);
    EXPECT_EQ(pc, 0xAD56);
}

TEST(OpcodeSuite, Execute0x00EE_StackPointerZero){
    // Arrange
    u_short pc {0x2153};
    byte sp {0x00};
    u_short stack[16] {0x1850};

    // Act
    Opcode::execute_00EE(pc, sp, stack);

    // Assert
    EXPECT_EQ(sp, 0x00);
    EXPECT_EQ(stack[0], 0);
    EXPECT_EQ(pc, 0x1850);
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

TEST(OpcodeSuite, Execute0x2NNN_NoException) {
    // Arrange
    u_short opcode {0x24B9};
    u_short pc {0xF5C2};
    byte sp {3};
    u_short stack[16] {0x0345, 0x58A6, 0xFFAC, 0x1298};

    // Act
    Opcode::execute_2NNN(opcode, pc, stack, sp);

    // Assert
    EXPECT_EQ(sp, 4);
    EXPECT_EQ(stack[4], 0xF5C2);
    EXPECT_EQ(pc, 0x04B9);
}

TEST(OpcodeSuite, Execute0x2NNN_Exception) {
    // Arrange
    u_short opcode {0x24B9};
    u_short pc {0xF5C2};
    byte sp {15};
    u_short stack[16] {};

    // Act & Assert
    EXPECT_ANY_THROW(Opcode::execute_2NNN(opcode, pc, stack, sp));
}

TEST(OpcodeSuite, Execute0x3XKK_Skip) {
    // Arrange
    u_short opcode {0x30A5};
    u_short pc {0xA592};
    byte V[16] {0xA5};

    // Act
    Opcode::execute_3XNN(opcode, pc, V);

    // Assert
    EXPECT_EQ(pc, 0xA594);
}

TEST(OpcodeSuite, Execute0x3XKK_NoSkip) {
    // Arrange
    u_short opcode {0x30B3};
    u_short pc {0xA592};
    byte V[16] {0xA5};

    // Act
    Opcode::execute_3XNN(opcode, pc, V);

    // Assert
    EXPECT_EQ(pc, 0xA592);
}

TEST(OpcodeSuite, Execute0x4XKK_Skip) {
    // Arrange
    u_short opcode {0x3089};
    u_short pc {0xA592};
    byte V[16] {0xA5};

    // Act
    Opcode::execute_4XNN(opcode, pc, V);

    // Assert
    EXPECT_EQ(pc, 0xA594);
}

TEST(OpcodeSuite, Execute0x4XKK_NoSkip) {
    // Arrange
    u_short opcode {0x30A5};
    u_short pc {0xA592};
    byte V[16] {0xA5};

    // Act
    Opcode::execute_4XNN(opcode, pc, V);

    // Assert
    EXPECT_EQ(pc, 0xA592);
}

TEST(OpcodeSuite, Execute0x5XY0_Skip) {
    // Arrange
    u_short opcode {0x5100};
    byte V[16] {0x89, 0x89};
    u_short pc {0xAAB2};

    // Act
    Opcode::execute_5XY0(opcode, pc, V);

    // Assert
    EXPECT_EQ(pc, 0xAAB4);
}

TEST(OpcodeSuite, Execute0x5XY0_NoSkip) {
    // Arrange
    u_short opcode {0x5100};
    byte V[16] {0xC9, 0x89};
    u_short pc {0xAAB2};

    // Act
    Opcode::execute_5XY0(opcode, pc, V);

    // Assert
    EXPECT_EQ(pc, 0xAAB2);
}

TEST(OpcodeSuite, Execute0x6XKK){
    // Arrange
    u_short opcode {0x609A};
    byte V[16] {0x82};

    // Act
    Opcode::execute_6XKK(opcode, V);

    // Assert
    EXPECT_EQ(V[0], 0x9A);
}

TEST(OpcodeSuite, Execute0x7XKK) {
    // Arrange
    u_short opcode {0x7065};
    byte V[16] {0xFF};

    // Act
    Opcode::execute_7XKK(opcode, V);

    // Assert
    EXPECT_EQ(V[0], 0x64);
}

TEST(OpcodeSuite, Execute0x8XY0){
    // Arrange
    u_short opcode {0x8100};
    byte V[16] {0x59, 0x10};

    // Act
    Opcode::execute_8XY0(opcode, V);

    // Assert
    EXPECT_EQ(V[0], 0x59);
    EXPECT_EQ(V[0], V[1]);
}

TEST(OpcodeSuite, Execute0x8XY1){
    // Arrange
    u_short opcode {0x8011};
    byte V[16] {0x80, 0xF6};

    // Act
    Opcode::execute_8XY1(opcode, V);

    // Assert
    EXPECT_EQ(V[0], 0xF6);
}

TEST(OpcodeSuite, Execute0x8XY2){
    // Arrange
    u_short opcode {0x8012};
    byte V[16] {0x80, 0xF6};

    // Act
    Opcode::execute_8XY2(opcode, V);

    // Assert
    EXPECT_EQ(V[0], 0x80);
}

TEST(OpcodeSuite, Execute0x8XY3){
    // Arrange
    u_short opcode {0x8013};
    byte V[16] {0x80, 0xF6};

    // Act
    Opcode::execute_8XY3(opcode, V);

    // Arrange
    EXPECT_EQ(V[0], 0x76);
}

TEST(OpcodeSuite, Execute0x8XY4_NoCarry){
    // Arrange
    u_short opcode {0x8014};
    byte V[16] {0x23, 0x56};

    // Act
    Opcode::execute_8XY4(opcode, V);

    // Arrange
    EXPECT_EQ(V[0], 0x79);
    EXPECT_EQ(V[0xF], 0);
}

TEST(OpcodeSuite, Execute0x8XY4_Carry){
    // Arrange
    u_short opcode {0x8014};
    byte V[16] {0xF3, 0x56};

    // Act
    Opcode::execute_8XY4(opcode, V);

    // Arrange
    EXPECT_EQ(V[0], 0x49);
    EXPECT_EQ(V[0xF], 1);
}

TEST(OpcodeSuite, Execute0x8XY5_NoBorrow) {
    // Arrange
    u_short opcode {0x8015};
    byte V[16] {0xF3, 0x56};

    // Act
    Opcode::execute_8XY5(opcode, V);

    // Assert
    EXPECT_EQ(V[0], 0x9D);
    EXPECT_EQ(V[0xF], 1);
}

TEST(OpcodeSuite, Execute0x8XY5_Borrow) {
    // Arrange
    u_short opcode {0x8015};
    byte V[16] {0x56, 0xF6};

    // Act
    Opcode::execute_8XY5(opcode, V);

    // Assert
    EXPECT_EQ(V[0], 0x60);
    EXPECT_EQ(V[0xF], 0);
}

TEST(OpcodeSuite, Execute0x8XY6_LsbIsOne) {
    // Arrange
    u_short opcode {0x8016};
    byte V[16] {0x57};

    // Act
    Opcode::execute_8XY6(opcode, V);

    // Assert
    EXPECT_EQ(V[0], 0x2B);
    EXPECT_EQ(V[0xF], 1);
}

TEST(OpcodeSuite, Execute0x8XY6_LsbIsZero) {
    // Arrange
    u_short opcode {0x8016};
    byte V[16] {0x56};

    // Act
    Opcode::execute_8XY6(opcode, V);

    // Assert
    EXPECT_EQ(V[0], 0x2B);
    EXPECT_EQ(V[0xF], 0);
}

TEST(OpcodeSuite, Execute0x8XY7_NoBorrow) {
    // Arrange
    u_short opcode {0x8017};
    byte V[16] {0x56, 0xF6};

    // Act
    Opcode::execute_8XY7(opcode, V);

    // Assert
    EXPECT_EQ(V[0], 0xA0);
    EXPECT_EQ(V[0xF], 1);
}

TEST(OpcodeSuite, Execute0x8XY7_Borrow) {
    // Arrange
    u_short opcode {0x8017};
    byte V[16] {0xF6, 0x56};

    // Act
    Opcode::execute_8XY7(opcode, V);

    // Assert
    EXPECT_EQ(V[0], 0x60);
    EXPECT_EQ(V[0xF], 0);
}

TEST(OpcodeSuite, Execute0x8XYE_LsbIsOne) {
    // Arrange
    u_short opcode {0x801E};
    byte V[16] {0x57};

    // Act
    Opcode::execute_8XYE(opcode, V);

    // Assert
    EXPECT_EQ(V[0], 0xAE);
    EXPECT_EQ(V[0xF], 1);
}

TEST(OpcodeSuite, Execute0x8XYE_LsbIsZero) {
    // Arrange
    u_short opcode {0x801E};
    byte V[16] {0x56};

    // Act
    Opcode::execute_8XYE(opcode, V);

    // Assert
    EXPECT_EQ(V[0], 0xAC);
    EXPECT_EQ(V[0xF], 0);
}

TEST(OpcodeSuite, Execute0x9XY0_Skip){
    // Arrange
    u_short opcode {0x9010};
    u_short pc {0x0A12};
    byte V[16] {0xAB, 0x15};

    // Act
    Opcode::execute_9XY0(opcode, pc, V);

    // Assert
    EXPECT_EQ(pc, 0x0A14);
}

TEST(OpcodeSuite, Execute0x9XY0_NoSkip){
    // Arrange
    u_short opcode {0x9010};
    u_short pc {0x0A12};
    byte V[16] {0xAB, 0xAB};

    // Act
    Opcode::execute_9XY0(opcode, pc, V);

    // Assert
    EXPECT_EQ(pc, 0x0A12);
}

TEST(OpcodeSuite, Execute0xANNN){
    // Arrange
    u_short opcode {0xA183};
    u_short I {0xA5F5};

    // Act
    Opcode::execute_ANNN(opcode, I);

    // Assert
    EXPECT_EQ(I, 0x0183);
}

TEST(OpcodeSuite, Execute0xBNNN){
    // Arrange
    u_short opcode {0xB853};
    u_short pc {0x1111};
    byte V[16] {0x14};

    // Act
    Opcode::execute_BNNN(opcode, pc, V[0]);

    // Assert
    EXPECT_EQ(pc, 0x867);
}

TEST(OpcodeSuite, Execute0xCXKK){
    // Arrange
    u_short opcode {0xC044};
    u_short pc {0x8453};
    byte V[16] {0x58};

    // Act
    Opcode::execute_CXKK(opcode, V);

    // Assert
    EXPECT_EQ(pc, 0x8453);
}

TEST(OpcodeSuite, Execute0xDXYN_NoCollision){
    // Arrange
    u_short opcode {0xD003};
    byte memory[4096] {0x3C, 0xC3, 0xFF};
    byte V[16] {0x0, 0x1};
    u_short I {0};
    bool graphics [64*32] {};

    // Act
    Opcode::execute_DXYN(opcode, memory, V, I, graphics);

    // Assert
    byte first_row[] {0,0,1,1,1,1,0,0};
    byte second_row[] {1,1,0,0,0,0,1,1};
    byte third_row[] {1,1,1,1,1,1,1,1};

    EXPECT_EQ(V[0xF], 0);
    for(int i {0}; i < 8; i++) {
        EXPECT_EQ(graphics[i], first_row[i]);
    }
    for(int i {0}; i < 8; i++) {
        EXPECT_EQ(graphics[i + 64], second_row[i]);
    }
    for(int i {0}; i < 8; i++) {
        EXPECT_EQ(graphics[i + 128], third_row[i]);
    }
}

TEST(OpcodeSuite, Execute0xDXYN_Collision){
    // Arrange
    u_short opcode {0xD003};
    byte memory[4096] {0x3C, 0xC3, 0xFF};
    byte V[16] {0x0, 0x1};
    u_short I {0};
    bool graphics [64*32] {1,1,1,1,1,1,1,1};

    // Act
    Opcode::execute_DXYN(opcode, memory, V, I, graphics);

    // Assert
    byte first_row[] {1,1,0,0,0,0,1,1};
    byte second_row[] {1,1,0,0,0,0,1,1};
    byte third_row[] {1,1,1,1,1,1,1,1};

    EXPECT_EQ(V[0xF], 1);
    for(int i {0}; i < 8; i++) {
        EXPECT_EQ(graphics[i], first_row[i]);
    }
    for(int i {0}; i < 8; i++) {
        EXPECT_EQ(graphics[i + 64], second_row[i]);
    }
    for(int i {0}; i < 8; i++) {
        EXPECT_EQ(graphics[i + 128], third_row[i]);
    }
}

TEST(OpcodeSuite, Execute0xEX9E_NoKeyPressed){
    // Arrange
    u_short opcode {0xE09E};
    u_short pc {0x5128};
    byte V[16] {0};
    bool keys[16] {0};

    // Act
    Opcode::execute_EX9E(opcode, pc, V, keys);

    // Assert
    EXPECT_EQ(pc, 0x5128);
    EXPECT_EQ(V[0], 0);
}

TEST(OpcodeSuite, Execute0xEX9E_KeyPressed){
    // Arrange
    u_short opcode {0xE09E};
    u_short pc {0x5128};
    byte V[16] {1};
    bool keys[16] {0, 1};

    // Act
    Opcode::execute_EX9E(opcode, pc, V, keys);

    // Assert
    EXPECT_EQ(pc, 0x512A);
    EXPECT_EQ(V[1], 0);
}

TEST(OpcodeSuite, Execute0xEXA1_NoKeyPressed){
    // Arrange
    u_short opcode {0xE0A1};
    u_short pc {0x5128};
    byte V[16] {0};
    bool keys[16] {0, 1};

    // Act
    Opcode::execute_EXA1(opcode, pc, V, keys);

    // Assert
    EXPECT_EQ(pc, 0x512A);
}

TEST(OpcodeSuite, Execute0xEXA1_KeyPressed){
    // Arrange
    u_short opcode {0xE0A1};
    u_short pc {0x5128};
    byte V[16] {1};
    bool keys[16] {0, 1};

    // Act
    Opcode::execute_EXA1(opcode, pc, V, keys);

    // Assert
    EXPECT_EQ(pc, 0x5128);
}

TEST(OpcodeSuite, Execute0xFX07){
    // Arrange
    u_short opcode {0xF107};
    byte V[16] {};
    byte delay_timer {0xAC};

    // Act
    Opcode::execute_FX07(opcode, V, delay_timer);

    // Assert
    EXPECT_EQ(V[1], 0xAC);
}

TEST(OpcodeSuite, Execute0xFX0A){
    // Arrange
    u_short opcode {0xF10A};
    u_short pc {0x2135};
    byte V[16] {};
    bool keys[16] {};

    // Act - No key pressed
    Opcode::execute_FX0A(opcode, pc, V, keys);

    // Assert
    EXPECT_EQ(pc, 0x2133);

    // Act
    keys[14] = true;
    Opcode::execute_FX0A(opcode, pc, V, keys);

    // Assert
    EXPECT_EQ(pc, 0x2133);
    EXPECT_EQ(V[1], 14);
}

TEST(OpcodeSuite, Execute0xFX15){
    // Arrange
    u_short opcode {0xF015};
    byte V[16] {0xA1};
    byte delay_timer {0xFF};

    // Act
    Opcode::execute_FX15(opcode, V, delay_timer);

    // Assert
    EXPECT_EQ(delay_timer, 0xA1);
}

TEST(OpcodeSuite, Execute0xFX18){
    // Arrange
    u_short opcode {0xF118};
    byte V[16] {0x12, 0xFF};
    byte sound_timer {};

    // Act
    Opcode::execute_FX18(opcode, V, sound_timer);

    // Assert
    EXPECT_EQ(sound_timer, 0xFF);
}

TEST(OpcodeSuite, Execute0xFX1E_NoOverflow){
    // Arrange
    u_short opcode {0xF11E};
    byte V[16] {0x15, 0x10};
    u_short I {0x85};

    // Act
    Opcode::execute_FX1E(opcode, V, I);

    // Assert
    EXPECT_EQ(I, 0x95);
    EXPECT_EQ(V[0xF], 0);
}

TEST(OpcodeSuite, Execute0xFX1E_Overflow){
    // Arrange
    u_short opcode {0xF11E};
    byte V[16] {0x00, 0x01};
    u_short I {0x0FFF};

    // Act
    Opcode::execute_FX1E(opcode, V, I);

    // Assert
    EXPECT_EQ(I, 0x1000);
    EXPECT_EQ(V[0xF], 1);
}

TEST(OpcodeSuite, Execute0xFX29){
    // Arrange
    u_short opcode {0xF029};
    byte V[16] {0x20};
    u_short I {};

    // Act
    Opcode::execute_FX29(opcode, V, I);

    // Assert
    EXPECT_EQ(I, 0xA0);
}

TEST(OpcodeSuite, Execute0xFX33){
    // Arrange
    u_short opcode {0xF033};
    byte V[16] {0xFE};
    u_short I {0};
    byte memory[4096] {};

    // Act
    Opcode::execute_FX33(opcode, V, I, memory);

    // Assert
    EXPECT_EQ(memory[I], 2);
    EXPECT_EQ(memory[I+1], 5);
    EXPECT_EQ(memory[I+2], 4);
}

TEST(OpcodeSuite, Execute0xFX33_Exception){
    // Arrange
    u_short opcode {0xF033};
    byte V[16] {0xFE};
    u_short I {4094};
    byte memory[4096] {};

    // Act & Assert
    EXPECT_ANY_THROW(Opcode::execute_FX33(opcode, V, I, memory));
}

TEST(OpcodeSuite, Execute0xFX55){
    // Arrange
    u_short opcode {0xF355};
    byte V[16] {0x1A, 0x2B, 0x3C, 0x4D, 0x5E};
    byte memory[4096] {};
    u_short I {0};

    // Act
    Opcode::execute_FX55(opcode, V, I, memory);

    // Assert
    EXPECT_EQ(memory[I], 0x1A);
    EXPECT_EQ(memory[I+1], 0x2B);
    EXPECT_EQ(memory[I+2], 0x3C);
    EXPECT_EQ(memory[I+3], 0x4D);
    EXPECT_EQ(memory[I+4], 0x00);
}

TEST(OpcodeSuite, Execute0xFX55_Exception){
    // Arrange
    u_short opcode {0xFF55};
    byte V[16] {0x1A, 0x2B, 0x3C, 0x4D, 0x5E};
    byte memory[4096] {};
    u_short I {4081};

    // Act & Assert
    EXPECT_ANY_THROW(Opcode::execute_FX55(opcode, V, I, memory));
}

TEST(OpcodeSuite, Execute_FX65){
    // Arrange
    u_short opcode {0xF365};
    byte V[16] {};
    byte memory[4096] {0x1A, 0x2B, 0x3C, 0x4D, 0x5E};
    u_short I {0};

    // Act
    Opcode::execute_FX65(opcode, V, I, memory);

    // Assert
    EXPECT_EQ(V[0], 0x1A);
    EXPECT_EQ(V[1], 0x2B);
    EXPECT_EQ(V[2], 0x3C);
    EXPECT_EQ(V[3], 0x4D);
    EXPECT_EQ(V[4], 0x00);
}

TEST(OpcodeSuite, Execute0xFX65_Exception){
    // Arrange
    u_short opcode {0xF165};
    byte V[16] {};
    byte memory[4096] {0x1A, 0x2B, 0x3C, 0x4D, 0x5E};
    u_short I {4095};

    // Act & Assert
    EXPECT_ANY_THROW(Opcode::execute_FX65(opcode, V, I, memory));
}

#endif // TST_OPCODECASE_H
