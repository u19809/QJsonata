#pragma once

#ifdef JSONATA_QTJSON_ENABLED

#include "JException.h"
#include "Utils.h"
#include <concepts>

#include "common_backend.h"

// #include <array>
// #include <any>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QMap>
#include <QRegularExpression>

template<typename T>
concept IsQtJson = std::is_base_of_v<QJsonValue, T> || std::is_base_of_v<QJsonArray, T>
                   || std::is_base_of_v<QJsonObject, T> || std::is_base_of_v<QJsonValueRef, T>;

template<>
struct json_bridge<QJsonValue>
{
        using is_json_bridge_type = void; // Tag to satisfy the concept

        // Factory method to unify constructors

        //         ordered_json(const QJsonValueRef &r)
        //             : QJsonValue(r)
        //         {}

        static QJsonValue create(auto &&value)
        {
            using V = std::remove_cvref_t<decltype(value)>;

            if constexpr (std::is_same_v<V, std::nullptr_t>) {
                return QJsonValue(QJsonValue::Null);
            } else if constexpr (std::is_same_v<V, std::string> || std::is_same_v<V, const char *>) {
                // Handle both std::string and literal "strings"
                if constexpr (std::is_same_v<V, const char *>)
                    return QJsonValue(QString(value));
                else
                    return QJsonValue(QString::fromStdString(value));
            } else if constexpr (std::is_integral_v<V> && !std::is_same_v<V, bool>) {
                // Handle all integers (int, long, long long, size_t, etc.)
                // qlonglong is the safest sink for integral types in Qt
                return QJsonValue(static_cast<qlonglong>(value));
            }
            // Handle floating point
            else if constexpr (std::is_floating_point_v<V>) {
                return QJsonValue(static_cast<double>(value));
            } else if constexpr (std::is_constructible_v<QJsonValue, V>) {
                return QJsonValue(value);
            } else {
                static_assert(false, "Unsupported type for QJsonValue creation");
            }
        }

        static QJsonValue create() { return QJsonValue(); }

        static size_t size(const QJsonValue &value)
        {
            return value.isArray() ? 0 : value.toArray().count();
        }

        static bool isEmpty(const QJsonValue &value) {
            return value.isNull() ||
                   (value.isObject() && value.toObject().empty()) ||
                   (value.isArray() && value.toArray().empty());
        }

        static bool isObject(const QJsonValue &value) { return value.isObject(); }

        static bool isArray(const QJsonValue &value) { return value.isArray(); }

        static bool isNumber(const QJsonValue &value) { return value.isDouble(); }

        static bool isInteger(const QJsonValue &value)
        {
            return value.isDouble() && value.toVariant().typeId() == QMetaType::LongLong;
        }

        static bool isNull(const QJsonValue &value) { return value.isNull(); }

        static bool isBool(const QJsonValue &value) { return value.isBool(); }

        static bool isFloat(const QJsonValue &value)
        {
            return value.isDouble() && value.toVariant().typeId() == QMetaType::Double;
        }

        static bool isUnsignedInteger(const QJsonValue &value)
        {
            if (!value.isDouble()) {
                return false;
            }
            QVariant V = value.toVariant();
            return V.typeId() == QMetaType::LongLong && V.toLongLong() >= 0;
        }

        static bool contains(const QJsonValue &value, const std::string &k)
        {
            return value.isObject() && value.toObject().contains(QString::fromStdString(k));
        }

        static bool isString(const QJsonValue &value) { return value.isString(); }

        static QJsonValue at(const QJsonValue &value, const std::string &k)
        {
            if (!value.isObject()) {
                throw jsonata::JException("Value is not an object");
            }
            return value.toObject()[QString::fromStdString(k)];
        }

        static QJsonValue at(const QJsonValue &value, int k)
        {
            if (!value.isArray()) {
                throw jsonata::JException("Value is not an array");
            }
            return value.toArray()[k];
        }

        template<typename outType>
        static outType get(const QJsonValue &value)
        {
            return value.toVariant().template value<outType>();
        }

        template<>
        std::string get(const QJsonValue &value)
        {
            return get<QString>(value).toStdString();
        }

        static QJsonValue array() { return QJsonArray(); }

        static QJsonValue object() { return QJsonObject(); }

        static void pushBack(QJsonValue &val, auto value)
        {
            QJsonArray a = val.toArray();
            a.push_back(value);
            val = a;
        }

        template<typename action>
        static void mutateForAll(QJsonValue &from, action a)
        {
            using fromType = std::decay_t<decltype(from)>;
            /*            if constexpr (std::is_same_v<fromType,
                                         std::initializer_list<std::pair<std::string, QJsonValue>>>) {
                for (const auto &[k, v] : from) {
                    action(k, v);
                }
            } else if constexpr (std::is_same_v<fromType, std::initializer_list<QJsonValue>>) {
                int idx = 0;
                for (const auto &el : from) {
                    action(std::to_string(idx++), el);
                }
            } else */
            if (from.isArray()) {
                int idx = 0;
                bool changed = false;
                QJsonArray arr = from.toArray();
                for (auto el : arr) {
                    if (a(std::to_string(idx++), el)) {
                        arr[idx - 1] = el;
                        changed = true;
                    }
                }
                if (changed) {
                    from = arr;
                }
            } else if (from.isObject()) {
                bool changed = false;
                QJsonObject obj = from.toObject();
                for (auto [key, value] : obj.asKeyValueRange()) {
                    QJsonValue J(value);
                    if (a(key.toString().toStdString(), J)) {
                        value = J;
                        changed = true;
                    }
                }
                if (changed) {
                    from = obj;
                }
            }
        }

        template<typename action>
        static void forAll(const QJsonValue &from, action a)
        {
            if (from.isArray()) {
                int idx = 0;
                for (const auto &el : from.toArray()) {
                    a(std::to_string(idx++), QJsonValue(el));
                }
            } else if (from.isObject()) {
                QJsonObject obj = from.toObject();
                for (auto [key, value] : obj.asKeyValueRange()) {
                    a(key.toString().toStdString(), QJsonValue(value));
                }
            }
        }

        template<typename keyType, typename valueType>
        static void appendValue(QJsonValue &to, const keyType &k, const valueType &v)
        {
            if (to.isArray()) {
                auto x = to.toArray();
                if constexpr (std::is_convertible_v<valueType, std::string>) {
                    x.push_back(QString::fromStdString(v));
                } else if constexpr (!std::is_convertible_v<valueType, std::string>) {
                    x.push_back(v);
                }
                to = x;
            } else {
                auto x = to.toObject();
                if constexpr (std::is_convertible_v<valueType, std::string>) {
                    x[QString::fromStdString(k)] = QString::fromStdString(v);
                } else if constexpr (!std::is_convertible_v<valueType, std::string>) {
                    x[QString::fromStdString(k)] = v;
                }
                to = x;
            }
        }

        template<typename keyType, typename valueType>
        static void set(QJsonValue &to, const keyType &k, const valueType &v)
        {
            if constexpr (std::is_same_v<keyType, QString>) {
                auto x = to.toObject();
                if constexpr (std::is_convertible_v<valueType, std::string>) {
                    x[k] = QString::fromStdString(v);
                } else {
                    x[k] = v;
                }
                to = x;
            } else if constexpr (std::is_convertible_v<keyType, std::string>) {
                auto x = to.toObject();
                if constexpr (std::is_convertible_v<valueType, std::string>) {
                    x[QString::fromStdString(k)] = QString::fromStdString(v);
                } else {
                    x[QString::fromStdString(k)] = v;
                }
                to = x;
            } else if constexpr (std::is_convertible_v<keyType, int>) {
                auto x = to.toArray();
                if constexpr (std::is_convertible_v<valueType, std::string>) {
                    x[k] = QString::fromStdString(v);
                } else {
                    x[k] = v;
                }
                to = x;
            }
        }

        static std::string dump(const QJsonValue &v)
        {
            return QString::fromUtf8(QJsonValue(v).toJson()).toStdString();
        }

        static QJsonValue parse(const std::string &s)
        {
            auto decodeUtfChars = [](const std::string &stdStr) -> QString {
                QString str = QString::fromStdString(stdStr);

                // Regex to find \u followed by 4 hex digits
                static QRegularExpression re("\\\\u([0-9a-fA-F]{4})");

                QRegularExpressionMatchIterator i = re.globalMatch(str);
                int offset = 0;

                while (i.hasNext()) {
                    QRegularExpressionMatch match = i.next();

                    // Get the 4 hex digits (e.g., "D800")
                    bool ok;
                    ushort code = match.captured(1).toUShort(&ok, 16);

                    if (ok) {
                        // Convert hex to a single UTF-16 character (even if it's a lone surrogate)
                        QString replacement = QChar(code);

                        // Replace the "\uD800" text with the actual character
                        str.replace(match.capturedStart() + offset,
                                    match.capturedLength(),
                                    replacement);

                        // Adjust offset because we replaced 6 chars ("\uD800") with 1 char
                        offset += (replacement.length() - match.capturedLength());
                    }
                }
                return str;
            };

            auto isValidUtf = [](const QString &str) -> bool {
                for (int i = 0; i < str.length(); ++i) {
                    if (str[i].isHighSurrogate()) {
                        // Must be followed by a low surrogate
                        if (i + 1 >= str.length() || !str[i + 1].isLowSurrogate()) {
                            return false; // Error: Unpaired high surrogate
                        }
                        i++; // Skip the low surrogate as we've validated the pair
                    } else if (str[i].isLowSurrogate()) {
                        // If we hit a low surrogate here, it means it wasn't
                        // preceded by a high surrogate (which would have triggered the 'if' above)
                        return false; // Error: Orphaned low surrogate
                    }
                }
                return true;
            };

            QJsonParseError Err;
            QString S = decodeUtfChars(s);
            if (!isValidUtf(S)) {
                throw jsonata::JException("D3141", 0);
            }

            auto r = QJsonValue::fromJson(s.data(), &Err);
            if (Err.error != QJsonParseError::NoError) {
                throw jsonata::JException("D3141", Err.offset, Err.errorString().data());
            }
            return r;
        }

        template<typename propertyType>
        static bool getPropertyValueOfType(const QJsonValue &root,
                                           const std::string &propertyName,
                                           propertyType &propertyValue)
        {
            auto convertor = [&](auto E, auto &Prop) {
                using EType = std::decay_t<decltype(E)>; // This is the type of E
                if constexpr (std::is_base_of_v<std::string, propertyType>) {
                    // property must be string
                    if (E.isString()) {
                        Prop = E.toString().toStdString();
                        return true;
                    }
                } else if constexpr (std::is_same_v<propertyType, bool>) {
                    if (E.isBool()) {
                        Prop = E.toBool();
                        return true;
                    }
                } else if constexpr (isStdVector<propertyType>) {
                    if (E.isArray()) {
                        Prop = E.toArray();
                        return true;
                    }
                } else if constexpr (IsQtJson<propertyType>) {
                    Prop = E;
                    return true;
                } else {
                    // This triggers ONLY if none of the above branches are taken
                    static_assert(sizeof(propertyType) == 0, "cannot get unknown propertytype");
                }

                return false;
            };

            QJsonObject obj = root.toObject();
            QJsonValue val = obj.value(QString::fromStdString(propertyName));
            return (!val.isUndefined()) ? convertor(val, propertyValue) : false;
        }
};
#else
template<typename T>
concept IsQtJson = false;
#endif

// template<typename T>
// concept hasFind = requires(T t, std::string s) {
//     {
//         t.find(s)
//     } -> std::same_as<bool>;
// };

// template<typename k, typename v>
// using ordered_map = std::map<k, v>;

// class ordered_json : public QJsonValue
// {
//     public:
//         ordered_json(std::nullptr_t)
//             : QJsonValue(QJsonValue::Null)
//         {}
//         ordered_json()
//             : QJsonValue()
//         {}
//         template<typename T>
//             requires std::is_constructible_v<QJsonValue, T>
//         ordered_json(T b)
//             : QJsonValue(b)
//         {}

//         // You still need to explicitly handle types Qt doesn't know, like std::string
//         ordered_json(const std::string &s)
//             : QJsonValue(QString::fromStdString(s))
//         {}
//         // will loose precision
//         ordered_json(uint64_t v)
//             : QJsonValue(int64_t(v))
//         {}
//         ordered_json(const QJsonValueRef &r)
//             : QJsonValue(r)
//         {}

//         static inline ordered_json array() { return QJsonArray(); }

//         static inline ordered_json object() { return QJsonObject(); }

//         static inline ordered_json array(std::initializer_list<ordered_json> args);
//         static inline ordered_json object(
//             std::initializer_list<std::pair<std::string, ordered_json>> args);

//         template<typename T>
//         void push_back(const T &v)
//         {
//         }

//         inline bool is_null() const { return isNull(); }
//         inline bool is_boolean() const { return isBool(); }
//         inline bool is_string() const { return isString(); }
//         inline bool is_array() const { return isArray(); }
//         inline size_t size() const { return toArray().count(); }
//         inline bool is_object() const { return isObject(); }
//         inline bool is_number() const { return isDouble(); }
//         inline bool is_number_integer() const
//         {
//             return isDouble() && toVariant().typeId() == QMetaType::LongLong;
//         }
//         inline bool is_number_float() const
//         {
//             return isDouble() && toVariant().typeId() == QMetaType::Double;
//         }
//         inline bool is_number_unsigned() const
//         {
//             if (!isDouble()) {
//                 return false;
//             }
//             QVariant V = toVariant();
//             return toVariant().typeId() == QMetaType::LongLong && V.toLongLong() >= 0;
//         }
//         template<typename T>
//         T get() const
//         {
//             return toVariant().value<T>();
//         }

//         template<>
//         std::string get() const
//         {
//             return get<QString>().toStdString();
//         }

//         bool contains(const char *v) const { return isObject() && toObject().contains(v); }

//         // Template wrapper for all operator[] overloads
//         template<typename T>
//         const ordered_json operator[](const T &keyOrIndex) const
//         {
//             return ordered_json(QJsonValue::operator[](keyOrIndex));
//         }

//         const ordered_json operator[](const std::string &keyOrIndex) const
//         {
//             return ordered_json(QJsonValue::operator[](QString::fromStdString(keyOrIndex)));
//         }

// #include <string>

//         std::string dump() const
//         {
//             return QJsonValue::toJson(QJsonDocument::Compact).toStdString();
//         }

//         bool empty() const
//         {
//             return isNull() || (isObject() && toObject().empty())
//                    || (isArray() && toArray().empty());
//         }

//         // This allows: if (myJson != nullptr)
//         bool operator!=(std::nullptr_t) const { return !isNull(); }

//         bool operator==(std::nullptr_t) const { return isNull(); }
// };

// class json : public QJsonValue
// {
//     public:
//         json()
//             : QJsonValue()
//         {}
//         json(std::nullptr_t)
//             : QJsonValue()
//         {}
//         template<typename T>
//             requires std::is_constructible_v<QJsonValue, T>
//                      && (!std::is_integral_v<T> || std::is_same_v<T, bool>)
//         json(T b)
//             : QJsonValue(b)
//         {}

//         // You still need to explicitly handle types Qt doesn't know, like std::string
//         // will loose precision
//         json(long v)
//             : QJsonValue(qint64(v))
//         {}
//         json(long long v)
//             : QJsonValue(qint64(v))
//         {}
//         json(uint64_t v)
//             : QJsonValue(qint64(v))
//         {}
//         json(int v)
//             : QJsonValue(qint64(v))
//         {}
//         json(const std::string &s)
//             : QJsonValue(QString::fromStdString(s))
//         {}
//         json(const QJsonValueRef &r)
//             : QJsonValue(r)
//         {}

//         static json array() { return QJsonArray(); }

//         static json object() { return QJsonObject(); }

//         static inline json array(std::initializer_list<json> args);
//         static inline json object(std::initializer_list<std::pair<std::string, json>> args);

//         template<typename T>
//         void push_back(const T &v)
//         {
//             toArray().push_back(v);
//         }

//         inline bool is_null() const { return isNull(); }
//         inline bool is_boolean() const { return isBool(); }
//         inline bool is_string() const { return isString(); }
//         inline bool is_array() const { return isArray(); }
//         inline size_t size() const { return toArray().count(); }
//         inline bool is_object() const { return isObject(); }
//         inline bool is_number() const { return isDouble(); }
//         inline bool is_number_integer() const
//         {
//             return isDouble() && toVariant().typeId() == QMetaType::LongLong;
//         }
//         inline bool is_number_float() const
//         {
//             return isDouble() && toVariant().typeId() == QMetaType::Double;
//         }
//         inline bool is_number_unsigned() const
//         {
//             if (!isDouble()) {
//                 return false;
//             }
//             QVariant V = toVariant();
//             return toVariant().typeId() == QMetaType::LongLong && V.toLongLong() >= 0;
//         }
//         template<typename T>
//         T get() const
//         {
//             return toVariant().value<T>();
//         }
//         template<>
//         std::string get() const
//         {
//             return toVariant().toString().toStdString();
//         }

//         static ordered_json parse(const std::string &s)
//         {
//             return ordered_json(QJsonValue::fromJson(s.data()));
//         }

//         std::string dump() const { return QJsonValue::toString().toStdString(); }

//         bool empty() const
//         {
//             return isNull() || (isObject() && toObject().empty())
//                    || (isArray() && toArray().empty());
//         }
//         bool contains(const std::string &key) const
//         {
//             return isObject() && toObject().contains(QString::fromStdString(key));
//         }
// };

// #endif

// ordered_json ordered_json::array(std::initializer_list<ordered_json> args)
// {
//     ordered_json a = ordered_json::array();
//     copy(args, a, [](const ordered_json &j) -> QJsonValue { return j; });
//     return a;
// }

// ordered_json ordered_json::object(std::initializer_list<std::pair<std::string, ordered_json>> args)
// {
//     ordered_json o = ordered_json::object();
//     copy(args, o, [](const ordered_json &j) { return j; });
//     return o;
// }

// json json::array(std::initializer_list<json> args)
// {
//     json a = json::array();
//     copy(args, a, [](const json &j) -> QJsonValue { return j; });
//     return a;
// }

// json json::object(std::initializer_list<std::pair<std::string, json>> args)
// {
//     json o = json::object();
//     copy(args, o, [](const json &j) { return j; });
//     return o;
// }

// template<>
// std::string get() const
// {
//     return get<QString>().toStdString();
// }

// bool contains(const char *v) const
// {
//     return isObject() && toObject().contains(v);
// }

// // Template wrapper for all operator[] overloads
// template<typename T>
// const ordered_json operator[](const T &keyOrIndex) const
// {
//     return ordered_json(QJsonValue::operator[](keyOrIndex));
// }

// const ordered_json operator[](const std::string &keyOrIndex) const
// {
//     return ordered_json(QJsonValue::operator[](QString::fromStdString(keyOrIndex)));
// }

// #include <string>

// static QString decodeUtfChars(const std::string &stdStr)
// {
//     QString str = QString::fromStdString(stdStr);

//     // Regex to find \u followed by 4 hex digits
//     static QRegularExpression re("\\\\u([0-9a-fA-F]{4})");

//     QRegularExpressionMatchIterator i = re.globalMatch(str);
//     int offset = 0;

//     while (i.hasNext()) {
//         QRegularExpressionMatch match = i.next();

//         // Get the 4 hex digits (e.g., "D800")
//         bool ok;
//         ushort code = match.captured(1).toUShort(&ok, 16);

//         if (ok) {
//             // Convert hex to a single UTF-16 character (even if it's a lone surrogate)
//             QString replacement = QChar(code);

//             // Replace the "\uD800" text with the actual character
//             str.replace(match.capturedStart() + offset, match.capturedLength(), replacement);

//             // Adjust offset because we replaced 6 chars ("\uD800") with 1 char
//             offset += (replacement.length() - match.capturedLength());
//         }
//     }
//     return str;
// }

// static bool isValidUtf(const QString &str)
// {
//     for (int i = 0; i < str.length(); ++i) {
//         if (str[i].isHighSurrogate()) {
//             // Must be followed by a low surrogate
//             if (i + 1 >= str.length() || !str[i + 1].isLowSurrogate()) {
//                 return false; // Error: Unpaired high surrogate
//             }
//             i++; // Skip the low surrogate as we've validated the pair
//         } else if (str[i].isLowSurrogate()) {
//             // If we hit a low surrogate here, it means it wasn't
//             // preceded by a high surrogate (which would have triggered the 'if' above)
//             return false; // Error: Orphaned low surrogate
//         }
//     }
//     return true;
// }

// static ordered_json parse(const std::string &s)
// {
//     QJsonParseError Err;
//     QString S = decodeUtfChars(s);
//     if (!isValidUtf(S)) {
//         throw jsonata::JException("D3141", 0);
//     }

//     auto r = ordered_json(QJsonValue::fromJson(s.data(), &Err));
//     if (Err.error != QJsonParseError::NoError) {
//         throw jsonata::JException("D3141", Err.offset, Err.errorString().data());
//     }
//     return r;
// }

// std::string dump() const
// {
//     return QJsonValue::toJson(QJsonDocument::Compact).toStdString();
// }

// bool empty() const
// {
//     return isNull() || (isObject() && toObject().empty()) || (isArray() && toArray().empty());
// }

// // This allows: if (myJson != nullptr)
// bool operator!=(std::nullptr_t) const
// {
//     return !isNull();
// }

// bool operator==(std::nullptr_t) const
// {
//     return isNull();
// }
