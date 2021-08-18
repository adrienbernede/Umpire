//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016-20, Lawrence Livermore National Security, LLC and Umpire
// project contributors. See the COPYRIGHT file for details.
//
// SPDX-License-Identifier: (MIT)
//////////////////////////////////////////////////////////////////////////////
#ifndef UMPIRE_json_file_store_HPP
#define UMPIRE_json_file_store_HPP

#include "umpire/event/event_store.hpp"

#include <vector>
#include <fstream>

namespace umpire {
namespace event {

class event;

class json_file_store : event_store {
  public:
  
  json_file_store(const std::string& filename);

  virtual void insert(event e);

  virtual std::vector<event> get_events();

  private:
  std::ofstream m_fstream;
};

}
}
#endif // UMPIRE_json_file_store_HPP
