#include "tst_squaretestset.h"
#include "tst_rectangletestset.h"
#include "tst_ellipsetestset.h"

#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
