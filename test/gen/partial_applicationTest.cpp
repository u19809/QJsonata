#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class partial_applicationTest : public JsonataTest {
};

// 
TEST_F(partial_applicationTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/partial-application/case000.json"));
}

// 
TEST_F(partial_applicationTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/partial-application/case001.json"));
}

// 
TEST_F(partial_applicationTest, case002) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/partial-application/case002.json"));
}

// 
TEST_F(partial_applicationTest, case003) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/partial-application/case003.json"));
}

// 
TEST_F(partial_applicationTest, case004) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/partial-application/case004.json"));
}

