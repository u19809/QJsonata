#include <gtest/gtest.h>
#include <jsonata/Jsonata.h>
#include <jsonata/JException.h>
#include <vector>
#include <memory>

namespace jsonata {

class NullSafetyTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}

    static jsonata::backend<JSONATA_TEST_BACKEND> makeArray(const std::vector<jsonata::backend<JSONATA_TEST_BACKEND>>& values) {
        auto arr = jsonata::backend<JSONATA_TEST_BACKEND>::array();
        for (const auto& v : values)
            arr.push_back(*v);
        return arr;
    }
};

TEST_F(NullSafetyTest, testNullSafety) {
    auto r = Jsonata("$sift(undefined, $uppercase)").evaluate<JSONATA_TEST_BACKEND>(nullptr);
    EXPECT_TRUE(r.isNull());

    r = Jsonata("$each(undefined, $uppercase)").evaluate<JSONATA_TEST_BACKEND>(nullptr);
    EXPECT_TRUE(r.isNull());

    r = Jsonata("$keys(null)").evaluate<JSONATA_TEST_BACKEND>(nullptr);
    EXPECT_TRUE(r.isNull());

    r = Jsonata("$map(null, $uppercase)").evaluate<JSONATA_TEST_BACKEND>(nullptr);
    EXPECT_TRUE(r.isNull());

    r = Jsonata("$filter(null, $uppercase)").evaluate<JSONATA_TEST_BACKEND>(nullptr);
    EXPECT_TRUE(r.isNull());

    r = Jsonata("$single(null, $uppercase)").evaluate<JSONATA_TEST_BACKEND>(nullptr);
    EXPECT_TRUE(r.isNull());

    r = Jsonata("$reduce(null, $uppercase)").evaluate<JSONATA_TEST_BACKEND>(nullptr);
    EXPECT_TRUE(r.isNull());

    r = Jsonata("$lookup(null, 'anykey')").evaluate<JSONATA_TEST_BACKEND>(nullptr);
    EXPECT_TRUE(r.isNull());

    r = Jsonata("$spread(null)").evaluate<JSONATA_TEST_BACKEND>(nullptr);
    EXPECT_TRUE(r.isNull());
}

TEST_F(NullSafetyTest, testFilterNull) {
    auto arrayData = makeArray({1, nullptr});
    Jsonata expr("$filter($, function($v, $i, $a){$v})");
    auto result = expr.evaluate(arrayData);
    ASSERT_TRUE(result.isNumber());
    EXPECT_EQ(result.get<int>(), 1);
}

TEST_F(NullSafetyTest, testNotNull) {
    auto result = Jsonata("$not($)").evaluate<JSONATA_TEST_BACKEND>(nullptr);
    EXPECT_TRUE(result.isNull());
}

TEST_F(NullSafetyTest, testSingleNull) {
    auto arrayData = makeArray({nullptr, 1});
    Jsonata expr("$single($, function($v, $i, $a){ $v })");
    auto result = expr.evaluate(arrayData);
    ASSERT_TRUE(result.isNumber());
    EXPECT_EQ(result.get<int>(), 1);
}

TEST_F(NullSafetyTest, testFilterNullLookup) {
    auto arrayData = jsonata::backend<JSONATA_TEST_BACKEND>::array({
        jsonata::backend<JSONATA_TEST_BACKEND>::object({{"content", "some"}}),
        jsonata::backend<JSONATA_TEST_BACKEND>::object()
    });
    Jsonata expr("$filter($, function($v, $i, $a){$lookup($v, 'content')})");
    auto result = expr.evaluate(arrayData);
    ASSERT_TRUE(result.isObject());
    ASSERT_TRUE(result.contains("content"));
    EXPECT_EQ(result["content"].get<std::string>(), "some");
}

} // namespace jsonata
