#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class closuresTest : public JsonataTest {
};

// 
TEST_F(closuresTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/closures/case000.json"));
}

// 
TEST_F(closuresTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/closures/case001.json"));
}

