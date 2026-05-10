#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class function_lengthTest : public JsonataTest {
};

// 
TEST_F(function_lengthTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-length/case000.json"));
}

// 
TEST_F(function_lengthTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-length/case001.json"));
}

// 
TEST_F(function_lengthTest, case002) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-length/case002.json"));
}

// 
TEST_F(function_lengthTest, case003) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-length/case003.json"));
}

// $length(\\\"\\\\uD834\\\\uDD1E\\\")
TEST_F(function_lengthTest, case004) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-length/case004.json"));
}

// 
TEST_F(function_lengthTest, case005) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-length/case005.json"));
}

// 
TEST_F(function_lengthTest, case006) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-length/case006.json"));
}

// 
TEST_F(function_lengthTest, case007) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-length/case007.json"));
}

// 
TEST_F(function_lengthTest, case008) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-length/case008.json"));
}

// 
TEST_F(function_lengthTest, case009) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-length/case009.json"));
}

// 
TEST_F(function_lengthTest, case010) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-length/case010.json"));
}

// 
TEST_F(function_lengthTest, case011) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-length/case011.json"));
}

// 
TEST_F(function_lengthTest, case012) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-length/case012.json"));
}

// 
TEST_F(function_lengthTest, case013) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-length/case013.json"));
}

// 
TEST_F(function_lengthTest, case014) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-length/case014.json"));
}

// 
TEST_F(function_lengthTest, case015) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-length/case015.json"));
}

// 
TEST_F(function_lengthTest, case016) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/function-length/case016.json"));
}

