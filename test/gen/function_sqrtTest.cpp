#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class function_sqrtTest : public JsonataTest {
};

// 
TEST_F(function_sqrtTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-sqrt/case000.json"));
}

// 
TEST_F(function_sqrtTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-sqrt/case001.json"));
}

// 
TEST_F(function_sqrtTest, case002) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-sqrt/case002.json"));
}

// 
TEST_F(function_sqrtTest, case003) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-sqrt/case003.json"));
}

