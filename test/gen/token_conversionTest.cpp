#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class token_conversionTest : public JsonataTest {
};

// 
TEST_F(token_conversionTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/token-conversion/case000.json"));
}

// 
TEST_F(token_conversionTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/token-conversion/case001.json"));
}

// 
TEST_F(token_conversionTest, case002) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/token-conversion/case002.json"));
}

// 
TEST_F(token_conversionTest, case003) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/token-conversion/case003.json"));
}

