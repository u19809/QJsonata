#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class function_keysTest : public JsonataTest {
};

// 
TEST_F(function_keysTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-keys/case000.json"));
}

// 
TEST_F(function_keysTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-keys/case001.json"));
}

// 
TEST_F(function_keysTest, case002) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-keys/case002.json"));
}

// 
TEST_F(function_keysTest, case003) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-keys/case003.json"));
}

// 
TEST_F(function_keysTest, case004) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-keys/case004.json"));
}

// 
TEST_F(function_keysTest, case005) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-keys/case005.json"));
}

// 
TEST_F(function_keysTest, case006) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-keys/case006.json"));
}

