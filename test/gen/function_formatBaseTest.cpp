#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class function_formatBaseTest : public JsonataTest {
};

// 
TEST_F(function_formatBaseTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-formatBase/case000.json"));
}

// 
TEST_F(function_formatBaseTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-formatBase/case001.json"));
}

// 
TEST_F(function_formatBaseTest, case002) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-formatBase/case002.json"));
}

// 
TEST_F(function_formatBaseTest, case003) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-formatBase/case003.json"));
}

// 
TEST_F(function_formatBaseTest, case004) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-formatBase/case004.json"));
}

// 
TEST_F(function_formatBaseTest, case005) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-formatBase/case005.json"));
}

// 
TEST_F(function_formatBaseTest, case006) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-formatBase/case006.json"));
}

// 
TEST_F(function_formatBaseTest, case007) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-formatBase/case007.json"));
}

