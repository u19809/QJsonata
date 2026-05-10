#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class function_substringBeforeTest : public JsonataTest {
};

// 
TEST_F(function_substringBeforeTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-substringBefore/case000.json"));
}

// 
TEST_F(function_substringBeforeTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-substringBefore/case001.json"));
}

// 
TEST_F(function_substringBeforeTest, case002) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-substringBefore/case002.json"));
}

// 
TEST_F(function_substringBeforeTest, case003) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-substringBefore/case003.json"));
}

// 
TEST_F(function_substringBeforeTest, case004) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-substringBefore/case004.json"));
}

