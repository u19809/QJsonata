#pragma once

#include <type_traits>
#include <vector>

// for jlIST
template<typename T>
struct is_vector : std::false_type
{};

template<typename T, typename A>
struct is_vector<std::vector<T, A>> : std::true_type
{};

template<typename T>
concept isStdVector = is_vector<T>::value;

// This is the "Contract" class which we will specify based on actual json classes (see qjson_backend e.a.)
template<typename T>
struct json_bridge {
        // We leave this empty.
        // Specializations will provide the actual logic.
};

