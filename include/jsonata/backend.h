#pragma once

#include "jsonata/common_backend.h"
#include <string>
#include <type_traits>
#include <optional>
// test for existence of methods
struct Anything
{
        // Implicit conversion to absolutely anything
        template<typename T>
        operator T() const;
        // This allows the mock to stay 'active' when passed by reference
        template<typename T>
        operator T &() const;

        // Also handle const references just in case
        template<typename T>
        operator const T &() const;
};

template<typename T>
concept isBasicallyReadCompatible = requires(const T &ConstObj) {
    json_bridge<T>::forAll(ConstObj, [](const std::string &, auto &) {});
    json_bridge<T>::array();
    json_bridge<T>::object();
    json_bridge<T>::at(ConstObj, 1);
    json_bridge<T>::dump(ConstObj);
    json_bridge<T>::parse(std::string());
    { json_bridge<T>::size(ConstObj) } -> std::same_as<size_t>;
    { json_bridge<T>::isEmpty(ConstObj) } -> std::same_as<bool>;
    { json_bridge<T>::isObject(ConstObj) } -> std::same_as<bool>;
    { json_bridge<T>::isArray(ConstObj) } -> std::same_as<bool>;
    { json_bridge<T>::contains(ConstObj, std::string()) } -> std::same_as<bool>;
    { json_bridge<T>::isNull(ConstObj) } -> std::same_as<bool>;
    { json_bridge<T>::isBool(ConstObj) } -> std::same_as<bool>;
    { json_bridge<T>::isString(ConstObj) } -> std::same_as<bool>;
    { json_bridge<T>::isNumber(ConstObj) } -> std::same_as<bool>;
    { json_bridge<T>::isInteger(ConstObj) } -> std::same_as<bool>;
    { json_bridge<T>::isUnsignedInteger(ConstObj) } -> std::same_as<bool>;
    { json_bridge<T>::isFloat(ConstObj) } -> std::same_as<bool>;
    requires requires(Anything &property) {
        { json_bridge<T>::getPropertyValueOfType(ConstObj, std::string(), property) } -> std::same_as<bool>;
    };
    { json_bridge<T>::template get<Anything>(ConstObj) } -> std::same_as<Anything>;
};

template<typename T>
concept isBasicallyWriteCompatible = isBasicallyReadCompatible<T> && requires(T &Obj ) {
    json_bridge<T>::mutateForAll(Obj, [](const std::string &, auto &) {});
    json_bridge<T>::appendValue(Obj, std::string(), Anything{} );
    json_bridge<T>::set(Obj, std::string(), Anything{});
    json_bridge<T>::pushBack(Obj, Anything{} );
    { json_bridge<T>::create(std::string()) } -> std::same_as<T>;
    { json_bridge<T>::create(1) } -> std::same_as<T>;
    { json_bridge<T>::create(nullptr) } -> std::same_as<T>;
    { json_bridge<T>::create() } -> std::same_as<T>;
};

// test for proper signalture of methods
template<typename T>
concept isReadCompatible = isBasicallyReadCompatible<T> && requires(const T &ConstObj) {
    requires requires(std::string s, T &innerVal) {
        json_bridge<T>::forAll(ConstObj, [](const std::string & key, auto & value) {
            // This is the CRITICAL part:
            // We force a compile-time check on the nested value
            static_assert(isBasicallyWriteCompatible<std::remove_reference_t<decltype(value)>>);
        });
    };
    isBasicallyWriteCompatible<std::remove_cvref_t<decltype(json_bridge<T>::parse(std::string()))>>;
    isBasicallyWriteCompatible<std::remove_cvref_t<decltype(json_bridge<T>::at(ConstObj, std::string()))>>;
    isBasicallyWriteCompatible<std::remove_cvref_t<decltype(json_bridge<T>::at(ConstObj, 1))>>;
    isBasicallyWriteCompatible<std::remove_cvref_t<decltype(json_bridge<T>::array())>>;
    isBasicallyWriteCompatible<std::remove_cvref_t<decltype(json_bridge<T>::object())>>;

    // To check recursive compatibility without crashing the compiler:
    requires requires {
        typename json_bridge<T>::is_json_bridge_type; // A simple tag
    };
};

// test for proper signalture of methods
template<typename T>
concept isCompatible = isReadCompatible<T> &&
                       isBasicallyWriteCompatible<T> && requires(T & Obj ) {
    requires requires(std::string s, T &innerVal) {
        json_bridge<T>::mutateForAll(Obj, [](const std::string & key, auto & value) {
            // This is the CRITICAL part:
            // We force a compile-time check on the nested value
            static_assert(isBasicallyWriteCompatible<std::remove_reference_t<decltype(value)>>);
        });
    };
};

namespace jsonata
{
    template<typename T>
    struct backend;
}

// test to see of type T is of the form backend<X>
template<typename T>
struct extractBackendType {
        using type = void;
        static constexpr bool isBackend = false;
};

// Specialization for your backend
template<typename X>
struct extractBackendType<jsonata::backend<X>> {
        using type = std::remove_cvref_t<X>;
        static constexpr bool isBackend = true;
};

// test to see if T is of form backend<X> with isReadCompatible<X> (i.e X is const)
template<typename T>
concept isReadCompatibleBackend = [] {
    using Extract = extractBackendType<std::remove_cvref_t<T>>;
    if constexpr (Extract::isBackend) {
        // Check if the inner type X is compatible
        return isReadCompatible<typename Extract::type>;
    }
    return false;
}();

// test to see if T is of form backend<X> with isCompatible<X>
template<typename T>
concept isCompatibleBackend = [] {
    using Extract = extractBackendType<std::remove_cvref_t<T>>;
    if constexpr (Extract::isBackend) {
        // Check if the inner type X is compatible
        return isCompatible<typename Extract::type>;
    }
    return false;
}();

namespace jsonata
{
    template<typename T>
    struct backend
    {

            // Use the base type for bridge lookups
            using BaseT = std::remove_cvref_t<T>;

            // Use a conditional concept check
            static constexpr bool mutatable_T = isCompatible<BaseT> && !std::is_const_v<T>;
            static constexpr bool compatible_T = isReadCompatible<BaseT>;

            backend() : val(nullptr) {}
            backend(std::nullptr_t) : val(nullptr) {}

            backend(const backend&) = default;
            backend(backend&&) noexcept = default;

            template<typename U>
            // Ensure U is compatible with T to avoid greedy matching
                requires std::is_convertible_v<std::remove_reference_t<U>*, T*>
            explicit backend(U&& v) noexcept : val(&v) {}

            template<typename U>
            // Ensure U is compatible with T to avoid greedy matching
                requires isCompatibleBackend<U>
            explicit backend(U& v) noexcept : val(v.val) {}

            template<typename U>
                requires (!std::is_convertible_v<std::remove_reference_t<U>*, T*>)
            backend(U&& value) {
                std::optional<T> owned; // To handle temporaries like 'create' results
                // Use the bridge to turn the literal into a real JSON object
                owned.emplace(json_bridge<BaseT>::create(std::forward<U>(value)));
                val = &(*owned);
            }

            operator T&() { return *val; }
            operator const T&() const { return *val; }

            // to unwrap explicitely
            template<typename Self>
            auto&& operator*(this Self&& self) {
                return *self.val;
            }

            static auto create( auto && value ) {
                return wrap(json_bridge<BaseT>::create(std::forward<decltype(value)>(value)));
            }

            static auto create() {
                return wrap(json_bridge<BaseT>::create());
            }

            backend<T> & operator=( backend<T> && other ) {
                val = other.val;
                other.val = nullptr;
                return *this;
            }

            backend<T> & operator=( const backend<T> & other ) {
                val = other.val;
                return *this;
            }

            bool isEmpty() const requires compatible_T
            {
                return json_bridge<BaseT>::isEmpty(*val);
            }

            bool isObject() const requires compatible_T
            {
                return json_bridge<BaseT>::isObject(*val);
            }

            size_t size() const requires compatible_T
            {
                return json_bridge<BaseT>::size(*val);
            }

            bool isArray() const requires compatible_T
            {
                return json_bridge<BaseT>::isArray(*val);
            }

            bool contains(const std::string &k) const requires compatible_T
            {
                return json_bridge<BaseT>::contains(*val, k);
            }

            bool isString() const requires compatible_T
            {
                return json_bridge<BaseT>::isString(*val);
            }

            bool isNull() const requires compatible_T
            {
                return json_bridge<BaseT>::isNull(*val);
            }

            bool isBool() const requires compatible_T
            {
                return json_bridge<BaseT>::isBool(*val);
            }

            bool isNumber() const requires compatible_T
            {
                return json_bridge<BaseT>::isNumber(*val);
            }

            bool isInteger() const requires compatible_T
            {
                return json_bridge<BaseT>::isInteger(*val);
            }

            bool isFloat() const requires compatible_T
            {
                return json_bridge<BaseT>::isFloat(*val);
            }

            bool isUnsignedInteger() const requires compatible_T
            {
                return json_bridge<BaseT>::isUnsignedInteger(*val);
            }

            // Transparently forward the size call to your static bridge
            auto at(auto key) requires compatible_T {
                return wrap(json_bridge<BaseT>::at(*val, key));
            }

            auto operator[](const std::string &k) const requires compatible_T
            {
                return wrap(json_bridge<BaseT>::at(*val, k));
            }

            auto operator[](int k) const requires compatible_T
            {
                return wrap(json_bridge<BaseT>::at(*val, k));
            }

            template<typename outType>
            outType get() const requires compatible_T
            {
                return json_bridge<BaseT>::template get<outType>(*val);
            }

            static auto parse(const std::string &s) requires compatible_T
            {
                return wrap(json_bridge<BaseT>::parse(s));
            }

            // apply action to all items in any type of collection allow mutation of value
            void mutateForAll(auto action) requires mutatable_T
            {
                json_bridge<BaseT>::mutateForAll(*val, action);
            }

            // apply action to all items in any type of collection
            void forAll(auto action) const requires compatible_T
            {
                json_bridge<BaseT>::forAll(*val, action);
            }

            void set(const auto &key, auto value) requires mutatable_T
            {
                json_bridge<BaseT>::set(*val, key, value);
            }

            std::string dump() const requires compatible_T
            {
                return json_bridge<BaseT>::dump(*val);
            }

            bool getPropertyValueOfType(const std::string &propertyName,
                                        auto &propertyValue) const requires compatible_T
            {
                using PType = std::decay_t<decltype(propertyValue)>;
                return json_bridge<BaseT>::template getPropertyValueOfType<PType>(*val, propertyName, propertyValue);
            }

            void push_back( auto value ) requires mutatable_T {
                return json_bridge<BaseT>::pushBack( *val, value);
            }

            void appendValue( const std::string & K, auto value ) requires mutatable_T {
                return json_bridge<BaseT>::appendValue( *val, K, value);
            }

            static auto array() requires compatible_T {
                return wrap(json_bridge<BaseT>::array() );
            }

            static auto object() requires compatible_T {
                return wrap(json_bridge<BaseT>::object() );
            }

            static auto array(std::initializer_list<backend<T>> args);

            static auto object(std::initializer_list<std::pair<std::string, backend<T>>> args);

            // This allows: if (myJson != nullptr)
            bool operator!=(std::nullptr_t) const
            {
                return !isNull();
            }

            bool operator==(std::nullptr_t) const
            {
                return isNull();
            }
        private :

            T * val;

            // Helper to wrap the result of doAt
            static auto wrap(auto&& result) {
                // We use remove_cvref_t to get the base type for the template
                using RawType = std::remove_cvref_t<decltype(result)>;
                // C++23 way to ensure we preserve the 'const' and 'reference' nature
                // of the result exactly as it came out of the bridge
                return backend<std::remove_reference_t<RawType>>(std::forward<decltype(result)>(result));            }
    };

    // Deduction guide to make it easy to use
    template<typename T>
    backend(T &) -> backend<T>;

    template<typename T>
    backend(T*) -> backend<T>;

    template<typename T>
    concept isPairLike = requires(T t) {
        typename T::first_type;
        typename T::second_type;
        t.first;
        t.second;
    };

    template<typename Container>
    concept isMappedContainer = requires {
        typename std::remove_cvref_t<Container>::value_type;
    } && isPairLike<typename std::remove_cvref_t<Container>::value_type>;

    template<typename List>
    concept isListContainer = !isMappedContainer<List>;

    // apply action to all items in any type of collection
    static void forAll(const auto &from, auto action)
    {
        using fromCollection = std::decay_t<decltype(from)>;
        using actionType = std::decay_t<decltype(action)>;

        if constexpr ( isReadCompatible<fromCollection> ) {
            jsonata::backend(from).forAll( action );
        } else if constexpr ( isReadCompatibleBackend<fromCollection> ) {
            from.forAll( action );
        } else if constexpr ( isMappedContainer<fromCollection> ) {
            for (const auto &[k, v] : from) {
                action(k, v);
            }
        } else if constexpr ( isListContainer<fromCollection>) {
            int idx = 0;
            for (const auto &el : from) {
                action(std::to_string(idx++), el);
            }
        } else {
            // This triggers ONLY if none of the above branches are taken
            static_assert(sizeof(fromCollection) == 0, "Unsupported outCollection type.");
        }
    }

    static void copy(const auto &from, auto &out)
    {

        forAll(from, [&out](auto k, auto v) {
            using outType = std::decay_t<decltype(out)>;
            using VType = std::decay_t<decltype(v)>;
            using KType = std::decay_t<decltype(k)>;

            if constexpr (isCompatible<outType>) {
                backend(out).appendValue(k, v);
            } else if constexpr (isCompatibleBackend<outType>) {
                out.appendValue(k, v);
            } else if constexpr (isMappedContainer<outType> ) {
                out[k] = v;
            } else if constexpr (isListContainer<outType> ) {
                out.push_back(v);
            } else {
                // This triggers ONLY if none of the above branches are taken
                static_assert(sizeof(outType) == 0,
                              "Unsupported outCollection type: Must be initializer, Qt "
                              "JSON, "
                              "nlohmann JSON, a "
                              "Map, or must "
                              "support "
                              "push"
                              "_bac"
                              "k.");
            }
        });
    }

    static void copy(const auto &from, auto &out, auto convert)
    {
        using outType = std::decay_t<decltype(out)>;

        forAll(from, [&out, convert](const std::string &k, auto v) {
            auto cv = convert(v);
            using VType = std::decay_t<decltype(cv)>;
            using KType = std::decay_t<decltype(k)>;

            if constexpr (isCompatible<outType>) {
                backend(out).appendValue(k, cv);
            } else if constexpr (isCompatibleBackend<outType>) {
                out.appendValue(k, cv);
            } else if constexpr ( isMappedContainer<outType> ) {
                out[k] = convert(v);
            } else if constexpr (isListContainer<outType> ) {
                out.push_back(convert(v));
            } else {
                // This triggers ONLY if none of the above branches are taken
                static_assert(sizeof(outType) == 0,
                              "Unsupported outCollection type: Must be Qt JSON, nlohmann "
                              "JSON, "
                              "a Map, or must "
                              "support "
                              "push_back.");
            }
        });
    }

    template<typename T>
    auto backend<T>::array(std::initializer_list<backend<T>> args)
    {
        auto a = array();
        copy(args, *a);
        return a;
    }

    template<typename T>
    auto backend<T>::object(std::initializer_list<std::pair<std::string, backend<T>>> args)
    {
        auto o = object();
        copy(args, *o);
        return o;
    }
} // namespace jsonata

#include "nlohmann_backend.h"
#include "qtjson_backend.h"
#include "qtvariant_backend.h"


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
