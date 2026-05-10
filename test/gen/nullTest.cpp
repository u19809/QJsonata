#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class nullTest : public JsonataTest {
};

// 
TEST_F(nullTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/null/case000.json"));
}

// 
TEST_F(nullTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/null/case001.json"));
}

// 
TEST_F(nullTest, case002) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/null/case002.json"));
}

// 
TEST_F(nullTest, case003) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/null/case003.json"));
}

// 
TEST_F(nullTest, case004) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/null/case004.json"));
}

// 
TEST_F(nullTest, case005) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/null/case005.json"));
}

// 
TEST_F(nullTest, case006) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/null/case006.json"));
}

