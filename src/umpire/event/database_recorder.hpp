//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016-20, Lawrence Livermore National Security, LLC and Umpire
// project contributors. See the COPYRIGHT file for details.
//
// SPDX-License-Identifier: (MIT)
//////////////////////////////////////////////////////////////////////////////
#ifndef UMPIRE_quest_db_recorder_HPP
#define UMPIRE_quest_db_recorder_HPP

#include "umpire/event/event_database.hpp"

namespace umpire {
namespace event {

class event;

class database_recorder {
  public:
  database_recorder(event_database* db);

  void record(event e);

  private:
   event_database* m_database;
};

}
}
#endif // UMPIRE_quest_db_recorder_HPP