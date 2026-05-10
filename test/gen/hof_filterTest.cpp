#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class hof_filterTest : public JsonataTest {
};

// 
TEST_F(hof_filterTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/hof-filter/case000.json"));
}

// 
TEST_F(hof_filterTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/hof-filter/case001.json"));
}

// 
TEST_F(hof_filterTest, case002) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/hof-filter/case002.json"));
}

// 
TEST_F(hof_filterTest, case003) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/hof-filter/case003.json"));
}

