#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class parent_operatorTest : public JsonataTest {
};

// 
TEST_F(parent_operatorTest, errors) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/parent-operator/errors.json"));
}

// 
TEST_F(parent_operatorTest, parent) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/parent-operator/parent.json"));
}

