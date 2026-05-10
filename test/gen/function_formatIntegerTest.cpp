#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class function_formatIntegerTest : public JsonataTest {
};

// 
TEST_F(function_formatIntegerTest, formatInteger) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-formatInteger/formatInteger.json"));
}

