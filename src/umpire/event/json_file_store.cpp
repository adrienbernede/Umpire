//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016-20, Lawrence Livermore National Security, LLC and Umpire
// project contributors. See the COPYRIGHT file for details.
//
// SPDX-License-Identifier: (MIT)
//////////////////////////////////////////////////////////////////////////////

#include "umpire/event/json_file_store.hpp"
#include "umpire/event/event_json.hpp"

#include "umpire/tpl/json/json.hpp"

#include <vector>

namespace umpire {
namespace event {

json_file_store::json_file_store(const std::string& filename) :
  m_fstream{filename}
{}

void 
json_file_store::insert(event e) {
  nlohmann::json json_event = e;
  m_fstream << json_event << std::endl;
}

std::vector<event>
json_file_store::get_events() {
  std::vector<event> events;
  return events;
}

}
}
