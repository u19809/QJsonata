#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class contextTest : public JsonataTest {
};

// 
TEST_F(contextTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/context/case000.json"));
}

// 
TEST_F(contextTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/context/case001.json"));
}

// 
TEST_F(contextTest, case002) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/context/case002.json"));
}

// 
TEST_F(contextTest, case003) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/context/case003.json"));
}

