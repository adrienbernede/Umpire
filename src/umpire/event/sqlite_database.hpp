//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016-20, Lawrence Livermore National Security, LLC and Umpire
// project contributors. See the COPYRIGHT file for details.
//
// SPDX-License-Identifier: (MIT)
//////////////////////////////////////////////////////////////////////////////
#ifndef UMPIRE_sqlite_database_HPP
#define UMPIRE_sqlite_database_HPP

#include "umpire/event/event_database.hpp"

#include <string>
#include <sqlite3.h>

namespace umpire {
namespace event {

class event;

class sqlite_database : public event_database {
  public:
  sqlite_database(const std::string& name);
  void insert(event e) override final;
  std::vector<event> get_events() override final;

  private:
  sqlite3* m_database;
};

}
}

#endif // UMPIRE_sqlite_database_HPP
