#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class function_decodeUrlTest : public JsonataTest {
};

// 
TEST_F(function_decodeUrlTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-decodeUrl/case000.json"));
}

// 
TEST_F(function_decodeUrlTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-decodeUrl/case001.json"));
}

// 
TEST_F(function_decodeUrlTest, case002) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-decodeUrl/case002.json"));
}

