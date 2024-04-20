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
    unsigned short opcode {(unsigned short)(0x1000 + (rand() % 0x2FFF))};
    unsigned short original_pc, pc;
    original_pc = pc = (unsigned short)rand();
    Opcode::execute_1NNN(opcode, pc);

    ASSERT_THAT(original_pc, Not(pc));
    ASSERT_EQ(opcode & 0x0FFF, pc);
}

TEST(OpcodeSuite, Test_0x2NNN)
{
    srand(time(0));


    unsigned short original_sp, sp;
    original_sp = sp = (unsigned short)(rand() % 15);
    unsigned short original_pc, pc;
    original_pc = pc = (unsigned short)rand();
    unsigned short opcode {(unsigned short)(0x2000 + (rand() % 0x2FFF))};
    unsigned short stack[16] {};

    Opcode::execute_2NNN(opcode, stack, sp, pc);
    ASSERT_EQ(stack[original_sp], original_pc);
    ASSERT_EQ(original_sp + 1, sp);
    ASSERT_EQ(opcode & 0x0FFF, pc);
}

#endif // TST_OPCODECASE_H
