#include <iostream>
#include <gtest/gtest.h>
#include "lab2.h"
#include "tst_lab2test.h"

using namespace std;

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
