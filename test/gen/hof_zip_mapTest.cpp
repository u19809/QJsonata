#include <gtest/gtest.h>
#include "JsonataTest.h"

using namespace jsonata;

class hof_zip_mapTest : public JsonataTest {
};

// 
TEST_F(hof_zip_mapTest, case000) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/hof-zip-map/case000.json"));
}

// 
TEST_F(hof_zip_mapTest, case001) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/hof-zip-map/case001.json"));
}

// 
TEST_F(hof_zip_mapTest, case002) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/hof-zip-map/case002.json"));
}

// 
TEST_F(hof_zip_mapTest, case003) {
    EXPECT_NO_THROW(runCase("jsonata/test/test-suite/groups/hof-zip-map/case003.json"));
}

