#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class wildcardsTest : public JsonataTest {
};

// 
TEST_F(wildcardsTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/wildcards/case000.json"));
}

// 
TEST_F(wildcardsTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/wildcards/case001.json"));
}

// 
TEST_F(wildcardsTest, case002) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/wildcards/case002.json"));
}

// 
TEST_F(wildcardsTest, case003) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/wildcards/case003.json"));
}

// 
TEST_F(wildcardsTest, case004) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/wildcards/case004.json"));
}

// 
TEST_F(wildcardsTest, case005) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/wildcards/case005.json"));
}

// 
TEST_F(wildcardsTest, case006) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/wildcards/case006.json"));
}

// 
TEST_F(wildcardsTest, case007) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/wildcards/case007.json"));
}

// 
TEST_F(wildcardsTest, case008) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/wildcards/case008.json"));
}

// 
TEST_F(wildcardsTest, case009) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/wildcards/case009.json"));
}

