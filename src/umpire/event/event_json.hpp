//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016-20, Lawrence Livermore National Security, LLC and Umpire
// project contributors. See the COPYRIGHT file for details.
//
// SPDX-License-Identifier: (MIT)
//////////////////////////////////////////////////////////////////////////////
#ifndef UMPIRE_event_json_HPP
#define UMPIRE_event_json_HPP

#include "umpire/event/event.hpp"
#include "umpire/tpl/json/json.hpp"

namespace umpire {
namespace event {

NLOHMANN_JSON_SERIALIZE_ENUM( category, {
    {category::operation, "operation"},
    {category::statistic, "statistic"},
    {category::metadata, "metadata" },
})

inline void to_json(nlohmann::json& j, const event& e) {
  j = nlohmann::json{
    { "name", e.name },
    { "category", e.cat },
    { "int_args", e.int_args },
    { "str_args", e.string_args },
    { "tags", e.tags },
    {"timestamp", std::to_string(static_cast<long>(std::chrono::time_point_cast<std::chrono::nanoseconds>(e.timestamp).time_since_epoch().count()))}
  };
}

inline void from_json(const nlohmann::json& j, event& e) {
  j.at("name").get_to(e.name);
  j.at("category").get_to(e.cat);
  if (j.find("int_args") != j.end()) {
    j.at("int_args").get_to(e.int_args);
  }
  if (j.find("str_args") != j.end()) {
    j.at("str_args").get_to(e.string_args);
  }
  j.at("tags").get_to(e.tags);
}

}
}

#endif // UMPIRE_event_json_HPP