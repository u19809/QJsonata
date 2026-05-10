#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class function_powerTest : public JsonataTest {
};

// 
TEST_F(function_powerTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-power/case000.json"));
}

// 
TEST_F(function_powerTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-power/case001.json"));
}

// 
TEST_F(function_powerTest, case002) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-power/case002.json"));
}

// 
TEST_F(function_powerTest, case003) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-power/case003.json"));
}

// 
TEST_F(function_powerTest, case004) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-power/case004.json"));
}

// 
TEST_F(function_powerTest, case005) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-power/case005.json"));
}

// 
TEST_F(function_powerTest, case006) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-power/case006.json"));
}

