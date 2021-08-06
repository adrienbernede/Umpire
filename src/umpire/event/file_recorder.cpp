//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016-20, Lawrence Livermore National Security, LLC and Umpire
// project contributors. See the COPYRIGHT file for details.
//
// SPDX-License-Identifier: (MIT)
//////////////////////////////////////////////////////////////////////////////

#include "umpire/event/file_recorder.hpp"
#include "umpire/event/event.hpp"
#include "umpire/event/event_json.hpp"

#include "umpire/tpl/json/json.hpp"

namespace umpire {
namespace event {

file_recorder::file_recorder(const std::string& filename) :
  m_fstream{filename}
{}

void 
file_recorder::record(event e) {
  nlohmann::json json_event = e;
  m_fstream << json_event << std::endl;
}

}
}