#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class function_decodeUrlComponentTest : public JsonataTest {
};

// 
TEST_F(function_decodeUrlComponentTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-decodeUrlComponent/case000.json"));
}

// 
TEST_F(function_decodeUrlComponentTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-decodeUrlComponent/case001.json"));
}

// 
TEST_F(function_decodeUrlComponentTest, case002) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-decodeUrlComponent/case002.json"));
}

