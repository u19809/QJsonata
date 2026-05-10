#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class function_assertTest : public JsonataTest {
};

// 
TEST_F(function_assertTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-assert/case000.json"));
}

// 
TEST_F(function_assertTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-assert/case001.json"));
}

// 
TEST_F(function_assertTest, case002) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-assert/case002.json"));
}

// 
TEST_F(function_assertTest, case003) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-assert/case003.json"));
}

// 
TEST_F(function_assertTest, case004) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-assert/case004.json"));
}

// 
TEST_F(function_assertTest, case005) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-assert/case005.json"));
}

// 
TEST_F(function_assertTest, case006) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-assert/case006.json"));
}

// 
TEST_F(function_assertTest, case007) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-assert/case007.json"));
}

