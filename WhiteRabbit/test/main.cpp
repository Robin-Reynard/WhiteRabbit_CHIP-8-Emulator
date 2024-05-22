#include "tst_whiterabbitcase.h"
#include "tst_opcodecase.h"
#include "tst_chip8case.h"

#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
