#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class function_eachTest : public JsonataTest {
};

// 
TEST_F(function_eachTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-each/case000.json"));
}

// 
TEST_F(function_eachTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-each/case001.json"));
}

// 
TEST_F(function_eachTest, case002) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-each/case002.json"));
}

