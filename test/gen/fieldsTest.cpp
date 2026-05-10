#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class fieldsTest : public JsonataTest {
};

// 
TEST_F(fieldsTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/fields/case000.json"));
}

// 
TEST_F(fieldsTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/fields/case001.json"));
}

// 
TEST_F(fieldsTest, case002) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/fields/case002.json"));
}

// 
TEST_F(fieldsTest, case003) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/fields/case003.json"));
}

// 
TEST_F(fieldsTest, case004) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/fields/case004.json"));
}

// 
TEST_F(fieldsTest, case005) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/fields/case005.json"));
}

// 
TEST_F(fieldsTest, case006) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/fields/case006.json"));
}

// 
TEST_F(fieldsTest, case007) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/fields/case007.json"));
}

