#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class blocksTest : public JsonataTest {
};

// 
TEST_F(blocksTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/blocks/case000.json"));
}

// 
TEST_F(blocksTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/blocks/case001.json"));
}

// 
TEST_F(blocksTest, case002) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/blocks/case002.json"));
}

// 
TEST_F(blocksTest, case003) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/blocks/case003.json"));
}

// 
TEST_F(blocksTest, case004) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/blocks/case004.json"));
}

// 
TEST_F(blocksTest, case005) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/blocks/case005.json"));
}

// 
TEST_F(blocksTest, case006) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/blocks/case006.json"));
}

