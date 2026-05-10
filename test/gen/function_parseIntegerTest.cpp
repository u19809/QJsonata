#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class function_parseIntegerTest : public JsonataTest {
};

// 
TEST_F(function_parseIntegerTest, parseInteger) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-parseInteger/parseInteger.json"));
}

