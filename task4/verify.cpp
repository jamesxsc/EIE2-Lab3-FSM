// Only help it with tb contents if it really needs them

#include "gtest/gtest.h"
#include "Vtop.h"
#include "verilated.h"


class TestF1 : public ::testing::Test {
public:
    void SetUp() override {
    }

    void TearDown() override {
    }

    void step() {
        top.eval();
        top.clk = !top.clk;
    }

    Vtop top;

};

TEST_F(TestF1, TestFirstTwoInSequence) {
    top.rst = 1;
    step();
    top.rst = 0;

    // Check output after reset is 0
    ASSERT_EQ(top.data_out, 0b00000000);

    top.trigger = 1;
    step();
    top.trigger = 0;

    // Check output after trigger is 1
    ASSERT_EQ(top.data_out, 0b00000001);

    for (int i = 0; i < 32; i++) {
        step();
    }
    // Check output after 32 more cycles is 3
    ASSERT_EQ(top.data_out, 0b00000011);
}
