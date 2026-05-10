#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class joinsTest : public JsonataTest {
};

// 
TEST_F(joinsTest, employee_map_reduce) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/joins/employee-map-reduce.json"));
}

// 
TEST_F(joinsTest, errors) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/joins/errors.json"));
}

// 
TEST_F(joinsTest, index) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/joins/index.json"));
}

// 
TEST_F(joinsTest, library_joins) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/joins/library-joins.json"));
}

