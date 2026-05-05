#include <gtest/gtest.h>
#include <jsonata/Jsonata.h>
#include "jsonata/backends.h"
#include <jsonata/JException.h>
#include <vector>
#include <memory>

namespace jsonata {

class NullSafetyTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}

    static JSONATA_TEST_BACKEND makeArray(const std::vector<JSONATA_TEST_BACKEND>& values) {
        JSONATA_TEST_BACKEND arr = JSONATA_TEST_BACKEND::array();
        for (const auto& v : values) arr.push_back(v);
        return arr;
    }
};

TEST_F(NullSafetyTest, testNullSafety) {
    auto r = Jsonata("$sift(undefined, $uppercase)").evaluate<JSONATA_TEST_BACKEND>(nullptr);
    EXPECT_TRUE(r.is_null());

    r = Jsonata("$each(undefined, $uppercase)").evaluate<JSONATA_TEST_BACKEND>(nullptr);
    EXPECT_TRUE(r.is_null());

    r = Jsonata("$keys(null)").evaluate<JSONATA_TEST_BACKEND>(nullptr);
    EXPECT_TRUE(r.is_null());

    r = Jsonata("$map(null, $uppercase)").evaluate<JSONATA_TEST_BACKEND>(nullptr);
    EXPECT_TRUE(r.is_null());

    r = Jsonata("$filter(null, $uppercase)").evaluate<JSONATA_TEST_BACKEND>(nullptr);
    EXPECT_TRUE(r.is_null());

    r = Jsonata("$single(null, $uppercase)").evaluate<JSONATA_TEST_BACKEND>(nullptr);
    EXPECT_TRUE(r.is_null());

    r = Jsonata("$reduce(null, $uppercase)").evaluate<JSONATA_TEST_BACKEND>(nullptr);
    EXPECT_TRUE(r.is_null());

    r = Jsonata("$lookup(null, 'anykey')").evaluate<JSONATA_TEST_BACKEND>(nullptr);
    EXPECT_TRUE(r.is_null());

    r = Jsonata("$spread(null)").evaluate<JSONATA_TEST_BACKEND>(nullptr);
    EXPECT_TRUE(r.is_null());
}

TEST_F(NullSafetyTest, testFilterNull) {
    auto arrayData = makeArray({1, nullptr});
    Jsonata expr("$filter($, function($v, $i, $a){$v})");
    auto result = expr.evaluate(arrayData);
    ASSERT_TRUE(result.is_number());
    EXPECT_EQ(result.get<int>(), 1);
}

TEST_F(NullSafetyTest, testNotNull) {
    auto result = Jsonata("$not($)").evaluate<JSONATA_TEST_BACKEND>(nullptr);
    EXPECT_TRUE(result.is_null());
}

TEST_F(NullSafetyTest, testSingleNull) {
    auto arrayData = makeArray({nullptr, 1});
    Jsonata expr("$single($, function($v, $i, $a){ $v })");
    auto result = expr.evaluate(arrayData);
    ASSERT_TRUE(result.is_number());
    EXPECT_EQ(result.get<int>(), 1);
}

TEST_F(NullSafetyTest, testFilterNullLookup) {
    JSONATA_TEST_BACKEND arrayData = JSONATA_TEST_BACKEND::array({
        JSONATA_TEST_BACKEND::object({{"content", "some"}}),
        JSONATA_TEST_BACKEND::object()
    });
    Jsonata expr("$filter($, function($v, $i, $a){$lookup($v, 'content')})");
    auto result = expr.evaluate(arrayData);
    ASSERT_TRUE(result.is_object());
    ASSERT_TRUE(result.contains("content"));
    EXPECT_EQ(result["content"].get<std::string>(), "some");
}

} // namespace jsonata
