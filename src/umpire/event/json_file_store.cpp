//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016-20, Lawrence Livermore National Security, LLC and Umpire
// project contributors. See the COPYRIGHT file for details.
//
// SPDX-License-Identifier: (MIT)
//////////////////////////////////////////////////////////////////////////////

#include "umpire/event/event_json.hpp"
#include "umpire/event/json_file_store.hpp"
#include "umpire/tpl/json/json.hpp"
#include "umpire/util/Macros.hpp"

#include <fstream>
#include <vector>

namespace umpire {
namespace event {

json_file_store::json_file_store(const std::string& filename, bool read_only)
{
  std::fstream::openmode mode{read_only ? std::fstream::in : std::fstream::out | std::fstream::trunc};

  m_fstream.open(filename, mode);

  if (m_fstream.fail()) {
    UMPIRE_ERROR("Failed to open " << filename);
  }
}

void 
json_file_store::insert(event e) {
  nlohmann::json json_event = e;
  m_fstream << json_event << std::endl;
}

std::vector<event>
json_file_store::get_events() {
  std::string line;
  std::vector<event> events;
  std::size_t line_number{1};

  while (std::getline(m_fstream, line)) {
    nlohmann::json json_event;
    event e;

    try {
      json_event = nlohmann::json::parse(line);
      e = json_event;
    }
    catch (...) {
      UMPIRE_ERROR("json_file_store::get_events: Error parsing Line #" << line_number);
    }

    events.push_back(e);

    line_number++;
  }

  return events;
}

}
}
