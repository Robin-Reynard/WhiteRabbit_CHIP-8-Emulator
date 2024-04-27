#ifndef TST_OPCODECASE_H
#define TST_OPCODECASE_H

#include "opcode.h"
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <ctime>
#include <cstdlib>

using namespace testing;
using namespace Opcode;

TEST(OpcodeSuite, Execute0x1NNN){
    srand(time(0));
    u_short opcode {(u_short)(0x1000 + (rand() % 0x2FFF))};
    u_short original_pc, pc;
    original_pc = pc = (u_short)rand();
    Opcode::execute_1NNN(opcode, pc);

    EXPECT_THAT(original_pc, Not(pc));
    EXPECT_EQ(opcode & 0x0FFF, pc);
}

TEST(OpcodeSuite, Test_0x2NNN)
{
    srand(time(0));


    u_short original_sp, sp;
    original_sp = sp = (u_short)(rand() % 15);
    u_short original_pc, pc;
    original_pc = pc = (u_short)rand();
    u_short opcode {(u_short)(0x2000 + (rand() % 0x2FFF))};
    u_short stack[16] {};

    Opcode::execute_2NNN(opcode, stack, sp, pc);
    EXPECT_EQ(stack[original_sp], original_pc);
    EXPECT_EQ(original_sp + 1, sp);
    EXPECT_EQ(opcode & 0x0FFF, pc);
}

#endif // TST_OPCODECASE_H
