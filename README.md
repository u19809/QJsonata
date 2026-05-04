# Qjsonata

[![Build Status][github-actions-shield]][github-actions-link]

[github-actions-shield]: https://github.com/rayokota/jsonata-cpp/actions/workflows/cmake-multi-platform.yml/badge.svg?branch=master
[github-actions-link]: https://github.com/rayokota/jsonata-cpp/actions

C++ implementation of JSONata with support for abstract backend.

This is a C++ port of the  [JSONata reference implementation](https://github.com/jsonata-js/jsonata), 
and also borrows from the [Dashjoin Java port](https://github.com/dashjoin/jsonata-java).

QJsonata it is based on the jsonata-cpp port.

This implementation supports 100% of the language features of JSONata, with the exception that the ordering of keys of objects depend on the backend used. 
When using nlohmann - which has support for unordered json objects, ordering is as read or generated.  When using a backend like QJson which only supports sorted objects, objects are sorted when readed (parsed) or printed (dumped).  This 'breaks' some tests as the expected result objects converted to string sometimes do not match the query result converted to string, although the content is compatible as a json object.

In fact QJson supports any 'backend' that supports a certain API, whether it is a json object or not (e.g. a QVariant is also valid).  The API is defined
using a c++ context (isCompatible<T>).

The JSONata documentation can be found [here](https://jsonata.org).

## Installation

Installation uses CMake as follows:

```
include(FetchContent)

FetchContent_Declare(
    qjsonata
    URL https://github.com/u19809/QJsonata/archive/refs/tags/v0.1.0.zip
    URL_HASH SHA256=3ee1798f28a29d36ebbb273853979926716a384e4d491a6bd408e1f6de51760d  # Optional
)
FetchContent_MakeAvailable(qjsonata)

# Use the library
target_link_libraries(your_target qjsonata::qjsonata)
```

## Getting Started

A very simple start (with nlohmann as backend:

```
#include <iostream>
#include <jsonata/Jsonata.h>
#include <nlohmann/json.hpp>

int main() {
    // Create the JSON data
    auto data = nlohmann::ordered_json::parse(R"({
        "example": [
            {"value": 4}, 
            {"value": 7}, 
            {"value": 13}
        ]
    })");

    // Create the JSONata expression
    jsonata::Jsonata expr("$sum(example.value)");
    
    // Evaluate the expression with the data
    auto result = expr.evaluate(data);
    
    // Print the result
    std::cout << "Result: " << result << std::endl;
    
    return 0;
}
```
the same test with QJson as backend

```
#include <iostream>
#include <jsonata/Jsonata.h>
#include <nlohmann/json.hpp>

int main() {
    // Create the JSON data
    auto data = QJsonValue::fromJson(R"({
        "example": [
            {"value": 4}, 
            {"value": 7}, 
            {"value": 13}
        ]
    })");

    // Create the JSONata expression
    jsonata::Jsonata expr("$sum(example.value)");
    
    // Evaluate the expression with the data
    auto result = expr.evaluate(data);
    
    // Print the result
    std::cout << "Result: " << result << std::endl;
    
    return 0;
}
```

## Running Tests

This project uses the repository of the reference implementation as a submodule. This allows referencing the current version of the unit tests. To clone this repository, run:

```
git clone --recurse-submodules https://github.com/rayokota/jsonata-cpp
```

To build and run the unit tests:

```
cmake -DJSONATA_BUILD_TESTS=ON -S . -B build
cmake --build build
ctest --test-dir build
```
