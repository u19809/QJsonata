#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class function_mergeTest : public JsonataTest {
};

// 
TEST_F(function_mergeTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-merge/case000.json"));
}

// 
TEST_F(function_mergeTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-merge/case001.json"));
}

// 
TEST_F(function_mergeTest, case002) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-merge/case002.json"));
}

// 
TEST_F(function_mergeTest, case003) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-merge/case003.json"));
}

// 
TEST_F(function_mergeTest, case004) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-merge/case004.json"));
}

