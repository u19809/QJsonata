#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class conditionalsTest : public JsonataTest {
};

// 
TEST_F(conditionalsTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/conditionals/case000.json"));
}

// 
TEST_F(conditionalsTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/conditionals/case001.json"));
}

// 
TEST_F(conditionalsTest, case002) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/conditionals/case002.json"));
}

// 
TEST_F(conditionalsTest, case003) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/conditionals/case003.json"));
}

// 
TEST_F(conditionalsTest, case004) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/conditionals/case004.json"));
}

// 
TEST_F(conditionalsTest, case005) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/conditionals/case005.json"));
}

// 
TEST_F(conditionalsTest, case006) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/conditionals/case006.json"));
}

// 
TEST_F(conditionalsTest, case007) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/conditionals/case007.json"));
}

// 
TEST_F(conditionalsTest, case008) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/conditionals/case008.json"));
}

