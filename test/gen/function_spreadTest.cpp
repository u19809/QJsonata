#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class function_spreadTest : public JsonataTest {
};

// 
TEST_F(function_spreadTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-spread/case000.json"));
}

// 
TEST_F(function_spreadTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-spread/case001.json"));
}

// 
TEST_F(function_spreadTest, case002) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-spread/case002.json"));
}

// 
TEST_F(function_spreadTest, case003) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-spread/case003.json"));
}

