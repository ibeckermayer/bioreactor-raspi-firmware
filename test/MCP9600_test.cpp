/// @file MCP9600.cpp
/// Unit Tests for MCP9600 class
#include "MCP9600.h"
#include "gtest/gtest.h"

class MCP9600Test : public ::testing::Test {
protected:
    MCP9600 mcp = MCP9600(0x60);
};

/// @brief Test the constructor
TEST_F(MCP9600Test, constructor) {
    EXPECT_EQ("MCP9600", mcp.getName());
    EXPECT_EQ(0x60, mcp.getSlaveAddress());
}

/// @brief check that input range is valid
TEST_F(MCP9600Test, inputRangeValid) {
    EXPECT_TRUE(mcp.isInputRangeValid());
}

/// @brief check that temperature read is some sane value
/// @todo eventually there should be a known-temperature hardware setup that we test against
TEST_F(MCP9600Test, temperatureReadSane) {
    EXPECT_GE(mcp.readTemp(), 0);
    EXPECT_LE(mcp.readTemp(), 100);
}