#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class multiple_array_selectorsTest : public JsonataTest {
};

// 
TEST_F(multiple_array_selectorsTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/multiple-array-selectors/case000.json"));
}

// 
TEST_F(multiple_array_selectorsTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/multiple-array-selectors/case001.json"));
}

// 
TEST_F(multiple_array_selectorsTest, case002) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/multiple-array-selectors/case002.json"));
}

