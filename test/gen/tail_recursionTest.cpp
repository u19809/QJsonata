#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class tail_recursionTest : public JsonataTest {
};

// 
TEST_F(tail_recursionTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/tail-recursion/case000.json"));
}

// 
TEST_F(tail_recursionTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/tail-recursion/case001.json"));
}

// 
TEST_F(tail_recursionTest, case002) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/tail-recursion/case002.json"));
}

// 
TEST_F(tail_recursionTest, case003) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/tail-recursion/case003.json"));
}

// 
TEST_F(tail_recursionTest, case004) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/tail-recursion/case004.json"));
}

// 
TEST_F(tail_recursionTest, case005) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/tail-recursion/case005.json"));
}

// 
TEST_F(tail_recursionTest, case006) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/tail-recursion/case006.json"));
}

// 
TEST_F(tail_recursionTest, case007) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/tail-recursion/case007.json"));
}

// 
TEST_F(tail_recursionTest, case008) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/tail-recursion/case008.json"));
}

// 
TEST_F(tail_recursionTest, case009) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/tail-recursion/case009.json"));
}

