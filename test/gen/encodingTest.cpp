#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class encodingTest : public JsonataTest {
};

// 
TEST_F(encodingTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/encoding/case000.json"));
}

// 
TEST_F(encodingTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/encoding/case001.json"));
}

// 
TEST_F(encodingTest, case002) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/encoding/case002.json"));
}

// 
TEST_F(encodingTest, case003) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/encoding/case003.json"));
}

