#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class function_trimTest : public JsonataTest {
};

// 
TEST_F(function_trimTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-trim/case000.json"));
}

// 
TEST_F(function_trimTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-trim/case001.json"));
}

// 
TEST_F(function_trimTest, case002) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-trim/case002.json"));
}

