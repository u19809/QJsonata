#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class function_distinctTest : public JsonataTest {
};

// 
TEST_F(function_distinctTest, distinct) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-distinct/distinct.json"));
}

