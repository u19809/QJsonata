#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class higher_order_functionsTest : public JsonataTest {
};

// 
TEST_F(higher_order_functionsTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/higher-order-functions/case000.json"));
}

// 
TEST_F(higher_order_functionsTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/higher-order-functions/case001.json"));
}

// 
TEST_F(higher_order_functionsTest, case002) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/higher-order-functions/case002.json"));
}

