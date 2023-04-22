/*
 * @file main.cpp the entry point for the test application
 */

#include <iostream>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
