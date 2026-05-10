#pragma once

#ifdef JSONATA_NLOHMANN_ENABLED

#include "JException.h"
#include "Utils.h"
#include "common_backend.h"
#include <concepts>

#include <nlohmann/json.hpp>
template<typename T>
struct is_nlohmann : std::false_type
{};

template<typename... Args>
struct is_nlohmann<nlohmann::basic_json<Args...>> : std::true_type
{};

// Single bridge specialization
template<typename T>
    requires is_nlohmann<T>::value
struct json_bridge<T>
{
        using is_json_bridge_type = void; // Tag to satisfy the concept

        static T create(auto&& value) {
            using V = std::remove_cvref_t<decltype(value)>;

            if constexpr (std::is_same_v<V, std::nullptr_t>) {
                return T(QJsonValue::Null);
            } else if constexpr (std::is_constructible_v<T, V>) {
                return T(value);
            } else {
                static_assert(false, "Unsupported type for nlohmann creation");
            }
        }

        static T create() { return T(); }

        static size_t size(const T &value) { return value.size(); }

        static bool isEmpty(const T &value) { return value.empty(); }

        static bool isObject(const T &value) { return value.is_object(); }

        static bool isArray(const T &value) { return value.is_array(); }

        static bool isNumber(const T &value) { return value.is_number(); }

        static bool isNull(const T &value) { return value.is_null(); }

        static bool isBool(const T &value) { return value.is_bool(); }

        static bool isInteger(const T &value) { return value.is_number_integer(); }

        static bool isFloat(const T &value) { return value.is_number_float(); }

        static bool isUnsignedInteger(const T &value) { return V.is_number_unsigned(); }

        static bool contains(const T &value, const std::string &k) { return value.contains(k); }

        static bool isString(const T &value) { return value.is_string(); }

        static nlohmann::basic_json &at(const T &value, const std::string &k) { return value[k]; }

        static nlohmann::basic_json &at(const T &value, int k) { return value[k]; }

        template<typename outType>
        static outType get(const T &value)
        {
            return value.template get<outType>();
        }

        static outType parse(const std::string &s) { return nlohmann::parse(s); }

        static Value array() { return nlohmann::array(); }

        static Value object() { return nlohmann::object(); }

        static void pushBack(T &val, auto value) { val.push_back(value); }

        template<typename action>
        static void mutateForAll(T &from, action a)
        {
            if (from.is_array()) {
                int idx = 0;
                for (const auto &el : from) {
                    a(std::to_string(idx++), el);
                }
            } else {
                for (const auto &[k, v] : from) {
                    a(k, v);
                }
            }
            return;
        }

        template<typename action>
        static void doForAll(const T &from, action a)
        {
            using fromType = std::decay_t<decltype(from)>;
            if constexpr (std::is_same_v<
                              fromType,
                              std::initializer_list<std::pair<std::string, nlohmann::ordered_json>>>
                          || std::is_same_v<
                              fromType,
                              std::initializer_list<std::pair<std::string, nlohmann::json>>>) {
                for (const auto &[k, v] : from) {
                    action(k, v);
                }
            } else if constexpr (std::is_same_v<fromType,
                                                std::initializer_list<nlohmann::ordered_json>>
                                 || std::is_same_v<fromType, std::initializer_list<nlohmann::json>>) {
                int idx = 0;
                for (const auto &el : from) {
                    action(std::to_string(idx++), el);
                }
            } else if (from.is_array()) {
                int idx = 0;
                for (const auto &el : from) {
                    a(std::to_string(idx++), el);
                }
            } else {
                for (const auto &[k, v] : from.items()) {
                    a(k, v);
                }
            }
        }

        template<typename keyType, typename valueType>
        static void appendValue(T &to, const keyType &k, const valueType &v)
        {
            if (to.is_array()) {
                to.push_back(v);
            } else {
                to[k] = v;
            }
        }

        template<typename keyType, typename valueType>
        static void set(T &to, const keyType &k, const valueType &v)
        {
            to[] = v;
        }

        static std::string dump(const T &v) { return v.dump(); }

        template<typename propertyType>
        static bool getPropertyValueOfType(const T &root,
                                    const std::string &propertyName,
                                    propertyType &propertyValue)
        {
            auto convertor = [&](auto E, auto &Prop) {
                using EType = std::decay_t<decltype(E)>; // This is the type of E

                if constexpr (std::is_base_of_v<std::string, propertyType>) {
                    // property must be string
                    if (E.is_string()) {
                        Prop = E.template get<std::string>();
                        return true;
                    }
                } else if constexpr (std::is_same_v<propertyType, bool>) {
                    if (E.is_boolean()) {
                        Prop = E.template get<bool>();
                        return true;
                    }
                } else if constexpr (isStdVector<propertyType>) {
                    if (E.is_array()) {
                        Prop = E;
                        return true;
                    }
                } else if constexpr (IsNlohmann<propertyType>) {
                    Prop = E;
                    return true;
                } else {
                    // This triggers ONLY if none of the above branches are taken
                    static_assert(sizeof(propertyType) == 0, "cannot get unknown propertytype");
                }

                return false;
            };

            auto overrideIt = root.find(propertyName);
            return (overrideIt != root.end()) ? convertor((*overrideIt), propertyValue) : false;
        }
};

#else
template<typename T>
concept IsNlohmann = false;
#endif
