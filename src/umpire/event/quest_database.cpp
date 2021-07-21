//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016-20, Lawrence Livermore National Security, LLC and Umpire
// project contributors. See the COPYRIGHT file for details.
//
// SPDX-License-Identifier: (MIT)
//////////////////////////////////////////////////////////////////////////////

#include "umpire/event/quest_database.hpp"

#include "umpire/event/event.hpp"

namespace umpire {
namespace event {

quest_database::quest_database(const std::string& url, int port, const std::string& name) :
  event_database(),
  m_url(url),
  m_port(port),
  m_name(name),
{
}

void 
quest_database::insert(event e)
{
  auto builder = influxdb_cpp::builder();
  auto& tag_builder = builder.meas(e.m_name);
  auto& field_builder = (influxdb_cpp::detail::field_caller&)tag_builder;

  for (const auto& it : e.m_int_args ) {
    std::string name;
    int value;
    std::tie(name, value) = it;
    field_builder.field(name, value);
  }

  for (const auto& it : e.m_string_args ) {
    std::string name;
    std::string value;
    std::tie(name, value) = it;
    field_builder.field(name, value);
  }  

  field_builder.timestamp(
    static_cast<long>(
      std::chrono::time_point_cast<std::chrono::nanoseconds>(e.m_timestamp).time_since_epoch().count()));

  field_builder.post_http(m_server_info);
}


}
}