#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class function_floorTest : public JsonataTest {
};

// 
TEST_F(function_floorTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-floor/case000.json"));
}

// 
TEST_F(function_floorTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-floor/case001.json"));
}

// 
TEST_F(function_floorTest, case002) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-floor/case002.json"));
}

// 
TEST_F(function_floorTest, case003) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-floor/case003.json"));
}

