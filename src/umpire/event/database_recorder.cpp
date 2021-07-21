//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016-20, Lawrence Livermore National Security, LLC and Umpire
// project contributors. See the COPYRIGHT file for details.
//
// SPDX-License-Identifier: (MIT)
//////////////////////////////////////////////////////////////////////////////

#include "umpire/event/database_recorder.hpp"
#include "umpire/event/event.hpp"

namespace umpire {
namespace event {

database_recorder::database_recorder(event_database* db) :
  m_database(db)
{
}

void
database_recorder::record(event e)
{
  m_database->insert(e);
}

}
}