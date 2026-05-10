#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class inclusion_operatorTest : public JsonataTest {
};

// 
TEST_F(inclusion_operatorTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/inclusion-operator/case000.json"));
}

// 
TEST_F(inclusion_operatorTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/inclusion-operator/case001.json"));
}

// 
TEST_F(inclusion_operatorTest, case002) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/inclusion-operator/case002.json"));
}

// 
TEST_F(inclusion_operatorTest, case003) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/inclusion-operator/case003.json"));
}

// 
TEST_F(inclusion_operatorTest, case004) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/inclusion-operator/case004.json"));
}

// 
TEST_F(inclusion_operatorTest, case005) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/inclusion-operator/case005.json"));
}

// 
TEST_F(inclusion_operatorTest, case006) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/inclusion-operator/case006.json"));
}

// 
TEST_F(inclusion_operatorTest, case007) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/inclusion-operator/case007.json"));
}

// 
TEST_F(inclusion_operatorTest, case008) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/inclusion-operator/case008.json"));
}

