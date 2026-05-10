#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class function_siftTest : public JsonataTest {
};

// 
TEST_F(function_siftTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-sift/case000.json"));
}

// 
TEST_F(function_siftTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-sift/case001.json"));
}

// 
TEST_F(function_siftTest, case002) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-sift/case002.json"));
}

// 
TEST_F(function_siftTest, case003) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-sift/case003.json"));
}

// 
TEST_F(function_siftTest, case004) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-sift/case004.json"));
}

