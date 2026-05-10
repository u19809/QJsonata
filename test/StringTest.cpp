#include <gtest/gtest.h>
#include <jsonata/Jsonata.h>
#include <jsonata/JException.h>
#include <vector>
#include <memory>
#include <string>

namespace jsonata {

class StringTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}

    static auto makeObject(const std::map<std::string, std::string>& data) {
        auto obj = jsonata::backend<JSONATA_TEST_BACKEND>::object();
        jsonata::copy( data, obj );
        // for (const auto& [k, v] : data) obj[k] = v;
        return obj;
    }
    static auto makeObject(const std::map<std::string, int>& data) {
        auto obj = jsonata::backend<JSONATA_TEST_BACKEND>::object();
        jsonata::copy( data, obj );
        // for (const auto& [k, v] : data) obj[k] = v;
        return obj;
    }
};

TEST_F(StringTest, stringTest) {
    auto result1 = Jsonata("$string($)").evaluate(jsonata::backend<JSONATA_TEST_BACKEND>::create("abc"));
    ASSERT_TRUE(result1.isString());
    EXPECT_EQ(result1.get<std::string>(), "abc");

    auto result2 = Jsonata("$string(100.0)").evaluate<JSONATA_TEST_BACKEND>(nullptr);
    ASSERT_TRUE(result2.isString());
    EXPECT_EQ(result2.get<std::string>(), "100");
}

TEST_F(StringTest, DISABLED_stringExponentTest) {
    auto data1 = makeObject({{"x", 100}});
    auto result1 = Jsonata("$string(x)").evaluate(data1);
    ASSERT_TRUE(result1.isString());
    EXPECT_EQ(result1.get<std::string>(), "100");

    auto data2 = jsonata::backend<JSONATA_TEST_BACKEND>::parse("{\"x\": 100000000000000000000}");
    auto result2 = Jsonata("$string(x)").evaluate(data2);
    ASSERT_TRUE(result2.isString());
    EXPECT_EQ(result2.get<std::string>(), "100000000000000000000");

    auto data3 = jsonata::backend<JSONATA_TEST_BACKEND>::parse("{\"x\": 1000000000000000000000}");
    auto result3 = Jsonata("$string(x)").evaluate(data3);
    ASSERT_TRUE(result3.isString());
    EXPECT_EQ(result3.get<std::string>(), "1e+21");
}

TEST_F(StringTest, booleanTest) {
    auto result = Jsonata("$string($)").evaluate(jsonata::backend<JSONATA_TEST_BACKEND>(true));
    ASSERT_TRUE(result.isString());
    EXPECT_EQ(result.get<std::string>(), "true");
}

TEST_F(StringTest, numberTest) {
    auto result = Jsonata("$string(5)").evaluate<JSONATA_TEST_BACKEND>(nullptr);
    ASSERT_TRUE(result.isString());
    EXPECT_EQ(result.get<std::string>(), "5");
}

TEST_F(StringTest, arrayTest) {
    auto result = Jsonata("[1..5].$string()").evaluate<JSONATA_TEST_BACKEND>(nullptr);
    ASSERT_TRUE(result.isArray());
    std::vector<std::string> expected = {"1", "2", "3", "4", "5"};
    ASSERT_EQ(result.size(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        ASSERT_TRUE(result[i].isString());
        EXPECT_EQ(result[i].template get<std::string>(), expected[i]);
    }
}

TEST_F(StringTest, mapTest) {
    auto emptyMap = jsonata::backend<JSONATA_TEST_BACKEND>::object();
    auto result = Jsonata("$string($)").evaluate(emptyMap);
    ASSERT_TRUE(result.isString());
    EXPECT_EQ(result.get<std::string>(), "{}");
}

TEST_F(StringTest, map2Test) {
    auto data = makeObject({{"x", 1}});
    auto result = Jsonata("$string($)").evaluate(data);
    ASSERT_TRUE(result.isString());
    EXPECT_EQ(result.get<std::string>(), "{\"x\":1}");
}

TEST_F(StringTest, escapeTest) {
    auto result1 = Jsonata("$string($)").evaluate(makeObject({{"a", std::string("\"")}}));
    ASSERT_TRUE(result1.isString());
    // The result contains an escaped quote in JSON string
    EXPECT_EQ(result1.get<std::string>(), "{\"a\":\"\\\"\"}");

    auto result2 = Jsonata("$string($)").evaluate(makeObject({{"a", std::string("\\")}}));
    ASSERT_TRUE(result2.isString());
    EXPECT_EQ(result2.get<std::string>(), "{\"a\":\"\\\\\"}");

    auto result3 = Jsonata("$string($)").evaluate(makeObject({{"a", std::string("\t")}}));
    ASSERT_TRUE(result3.isString());
    EXPECT_EQ(result3.get<std::string>(), "{\"a\":\"\\t\"}");

    auto result4 = Jsonata("$string($)").evaluate(makeObject({{"a", std::string("\n")}}));
    ASSERT_TRUE(result4.isString());
    EXPECT_EQ(result4.get<std::string>(), "{\"a\":\"\\n\"}");

    auto result5 = Jsonata("$string($)").evaluate(makeObject({{"a", "</"}}));
    ASSERT_TRUE(result5.isString());
    EXPECT_EQ(result5.get<std::string>(), "{\"a\":\"</\"}");
}

TEST_F(StringTest, splitTest) {
    auto emptyMap = jsonata::backend<JSONATA_TEST_BACKEND>::object();
    auto result1 = Jsonata("$split(a, '-')").evaluate(emptyMap);
    EXPECT_TRUE(result1.isNull());

    auto result2 = Jsonata("a ~> $split('-')").evaluate(emptyMap);
    EXPECT_TRUE(result2.isNull());

    auto result3 = Jsonata("$split('', '')").evaluate<JSONATA_TEST_BACKEND>(nullptr);
    ASSERT_TRUE(result3.isArray());
    EXPECT_EQ(result3.size(), 0);

    auto result4 = Jsonata("$split('a1b2c3d4', '', 4)").evaluate<JSONATA_TEST_BACKEND>(nullptr);
    ASSERT_TRUE(result4.isArray());
    std::vector<std::string> expected = {"a", "1", "b", "2"};
    ASSERT_EQ(result4.size(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        ASSERT_TRUE(result4[i].isString());
        EXPECT_EQ(result4[i].template get<std::string>(), expected[i]);
    }

    auto result5 = Jsonata("$split('this..is.a.test', '.')").evaluate<JSONATA_TEST_BACKEND>(nullptr);
    ASSERT_TRUE(result5.isArray());
    std::vector<std::string> expected5 = {"this", "", "is", "a", "test"};
    ASSERT_EQ(result5.size(), expected5.size());
    for (size_t i = 0; i < expected5.size(); ++i) {
        ASSERT_TRUE(result5[i].isString());
        EXPECT_EQ(result5[i].template get<std::string>(), expected5[i]);
    }

    auto result6 = Jsonata("$split('this..is.a.test...', '.')").evaluate<JSONATA_TEST_BACKEND>(nullptr);
    ASSERT_TRUE(result6.isArray());
    std::vector<std::string> expected6 = {"this", "", "is", "a", "test", "", "", ""};
    ASSERT_EQ(result6.size(), expected6.size());
    for (size_t i = 0; i < expected6.size(); ++i) {
        ASSERT_TRUE(result6[i].isString());
        EXPECT_EQ(result6[i].get<std::string>(), expected6[i]);
    }
}

TEST_F(StringTest, trimTest) {
    auto result1 = Jsonata("$trim(\"\n\")").evaluate<JSONATA_TEST_BACKEND>(nullptr);
    ASSERT_TRUE(result1.isString());
    EXPECT_EQ(result1.get<std::string>(), "");

    auto result2 = Jsonata("$trim(\" \")").evaluate<JSONATA_TEST_BACKEND>(nullptr);
    ASSERT_TRUE(result2.isString());
    EXPECT_EQ(result2.get<std::string>(), "");

    auto result3 = Jsonata("$trim(\"\")").evaluate<JSONATA_TEST_BACKEND>(nullptr);
    ASSERT_TRUE(result3.isString());
    EXPECT_EQ(result3.get<std::string>(), "");

    auto result4 = Jsonata("$trim(notthere)").evaluate<JSONATA_TEST_BACKEND>(nullptr);
    EXPECT_TRUE(result4.isNull());
}

TEST_F(StringTest, evalTest) {
    auto result = Jsonata("(\n  $data := {'Wert1': 'AAA', 'Wert2': 'BBB'};\n  $eval('$data.Wert1')\n)").evaluate<JSONATA_TEST_BACKEND>(nullptr);
    ASSERT_TRUE(result.isString());
    EXPECT_EQ(result.get<std::string>(), "AAA");
}

TEST_F(StringTest, regexTest) {
    auto input = makeObject({{"foo", 1}, {"bar", 2}});
    auto result = Jsonata("($matcher := $eval('/^' & 'foo' & '/i'); $.$spread()[$.$keys() ~> $matcher])").evaluate(input);
    ASSERT_TRUE(result.isObject());
    auto expected = makeObject({{"foo", 1}});
    EXPECT_EQ(result, expected);
}

TEST_F(StringTest, fieldnameWithSpecialCharTest) {
    Jsonata expr("$ ~> |$|{}|");
    auto input = jsonata::backend<JSONATA_TEST_BACKEND>::create();
    input.set( "a\nb", "c\nd" );
    auto result = expr.evaluate(input);
    EXPECT_EQ(result, input);
}

TEST_F(StringTest, regexLiteralTest) {
    // Verify regex at end of expression doesn't crash (issue #88)
    EXPECT_NO_THROW({
        Jsonata expr("/^test.*$/");
        expr.evaluate<JSONATA_TEST_BACKEND>(nullptr);
    });
}

TEST_F(StringTest, evalRegexTest) {
    // Verify $eval of regex at end of expression doesn't crash (issue #88)
    EXPECT_NO_THROW({
        Jsonata expr("$eval('/^test.*$/')");
        expr.evaluate<JSONATA_TEST_BACKEND>(nullptr);
    });
}

TEST_F(StringTest, evalRegexCheckAnswerDataTest) {
    Jsonata expr("(\n    $matcher := $eval('/l/');\n    ('Hello World' ~> $matcher);\n)");
    auto result = expr.evaluate<JSONATA_TEST_BACKEND>(nullptr);
    ASSERT_TRUE(result.isObject());
    EXPECT_EQ(result["match"].get<std::string>(), "l");
    EXPECT_EQ(result["start"].get<long long>(), 2);
    EXPECT_EQ(result["end"].get<long long>(), 3);
    ASSERT_TRUE(result["groups"].isArray());
    EXPECT_EQ(result["groups"][0].get<std::string>(), "l");
}

TEST_F(StringTest, evalRegexCallNextTest) {
    Jsonata expr("(\n    $matcher := $eval('/l/');\n    ('Hello World' ~> $matcher).next();\n)");
    auto result = expr.evaluate<JSONATA_TEST_BACKEND>(nullptr);
    ASSERT_TRUE(result.isObject());
    EXPECT_EQ(result["match"].get<std::string>(), "l");
    EXPECT_EQ(result["start"].get<long long>(), 3);
    EXPECT_EQ(result["end"].get<long long>(), 4);
    ASSERT_TRUE(result["groups"].isArray());
    EXPECT_EQ(result["groups"][0].get<std::string>(), "l");
}

TEST_F(StringTest, DISABLED_replaceTest) {
    auto input = jsonata::backend<JSONATA_TEST_BACKEND>::create("http://example.org/test{par}");
    auto result = Jsonata("$replace($, /{par}/, '')").evaluate(input);
    ASSERT_TRUE(result.isString());
    EXPECT_EQ(result.get<std::string>(), "http://example.org/test");
}

} // namespace jsonata
