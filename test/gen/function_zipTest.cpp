#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class function_zipTest : public JsonataTest {
};

// 
TEST_F(function_zipTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-zip/case000.json"));
}

// 
TEST_F(function_zipTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-zip/case001.json"));
}

// 
TEST_F(function_zipTest, case002) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-zip/case002.json"));
}

// 
TEST_F(function_zipTest, case003) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-zip/case003.json"));
}

// 
TEST_F(function_zipTest, case004) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-zip/case004.json"));
}

// 
TEST_F(function_zipTest, case005) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-zip/case005.json"));
}

