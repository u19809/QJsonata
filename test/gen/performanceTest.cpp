#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class performanceTest : public JsonataTest {
};

// 
TEST_F(performanceTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/performance/case000.json"));
}

// 
TEST_F(performanceTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/performance/case001.json"));
}

