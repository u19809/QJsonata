#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class function_fromMillisTest : public JsonataTest {
};

// 
TEST_F(function_fromMillisTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-fromMillis/case000.json"));
}

// 
TEST_F(function_fromMillisTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-fromMillis/case001.json"));
}

// 
TEST_F(function_fromMillisTest, case002) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-fromMillis/case002.json"));
}

// 
TEST_F(function_fromMillisTest, formatDateTime) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-fromMillis/formatDateTime.json"));
}

// 
TEST_F(function_fromMillisTest, isoWeekDate) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-fromMillis/isoWeekDate.json"));
}

