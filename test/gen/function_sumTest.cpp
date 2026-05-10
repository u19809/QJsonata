#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class function_sumTest : public JsonataTest {
};

// 
TEST_F(function_sumTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-sum/case000.json"));
}

// 
TEST_F(function_sumTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-sum/case001.json"));
}

// 
TEST_F(function_sumTest, case002) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-sum/case002.json"));
}

// 
TEST_F(function_sumTest, case003) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-sum/case003.json"));
}

// 
TEST_F(function_sumTest, case004) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-sum/case004.json"));
}

// 
TEST_F(function_sumTest, case005) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-sum/case005.json"));
}

// 
TEST_F(function_sumTest, case006) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-sum/case006.json"));
}

