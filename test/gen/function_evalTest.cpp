#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class function_evalTest : public JsonataTest {
};

// 
TEST_F(function_evalTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-eval/case000.json"));
}

// 
TEST_F(function_evalTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-eval/case001.json"));
}

// 
TEST_F(function_evalTest, case002) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-eval/case002.json"));
}

// 
TEST_F(function_evalTest, case003) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-eval/case003.json"));
}

// 
TEST_F(function_evalTest, case004) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-eval/case004.json"));
}

// 
TEST_F(function_evalTest, case005) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-eval/case005.json"));
}

// 
TEST_F(function_evalTest, case006) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-eval/case006.json"));
}

// 
TEST_F(function_evalTest, case007) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-eval/case007.json"));
}

// 
TEST_F(function_evalTest, case008) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-eval/case008.json"));
}

