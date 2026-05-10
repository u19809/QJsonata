#pragma once

#ifdef JSONATA_QTVARIANT_ENABLED

#include "JException.h"
#include "Utils.h"
#include <concepts>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QRegularExpression>
#include <QMap>
#include <map>

template<typename T>
concept IsQtVariant = std::is_base_of_v<QVariant, T> ||
                   std::is_base_of_v<QVariantMap, T> ||
                   std::is_base_of_v<QVariantList, T>;

template<typename collection, typename action>
void qtvariant_mutateForAll(collection &from, action a)
{
    // if (from.isArray()) {
    //     int idx = 0;
    //     for (const auto &el : from) {
    //         a(std::to_string(idx++), el);
    //     }
    // } else {
    //     for (const auto &[k, v] : from) {
    //         a(k, v);
    //     }
    // }
    // return;
}

#else
template<typename T>
concept IsQtVariant = false;
#endif
