#include <gtest/gtest.h>
#include <jsonata/Jsonata.h>
#include <jsonata/JException.h>
#include <memory>
#include <string>

namespace jsonata {

class ParseIntegerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code if needed
    }

    void TearDown() override {
        // Cleanup code if needed
    }
};

TEST_F(ParseIntegerTest, parseIntegerNoError) {
    Jsonata expr("$parseInteger('xyz','000')");
    auto res = expr.evaluate<JSONATA_TEST_BACKEND>(nullptr);
    // Should return null for invalid input
    EXPECT_TRUE(res.isNull());
}

TEST_F(ParseIntegerTest, DISABLED_parseIntegerError) {
    // The following test throws an error in the jsonata-js reference,
    // but DecimalFormat allows this format (plan is not to fix):
    // This test is disabled as in the Java version
    
    EXPECT_THROW({
        Jsonata expr("$parseInteger('000','xyz')");
        auto res = expr.evaluate<JSONATA_TEST_BACKEND>(nullptr);
        EXPECT_TRUE(res.isNull());
    }, std::exception);
}

} // namespace jsonata
