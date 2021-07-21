//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016-20, Lawrence Livermore National Security, LLC and Umpire
// project contributors. See the COPYRIGHT file for details.
//
// SPDX-License-Identifier: (MIT)
//////////////////////////////////////////////////////////////////////////////
#ifndef UMPIRE_quest_database_HPP
#define UMPIRE_quest_database_HPP

#include "umpire/event/event_database.hpp"

#include <string>

namespace umpire {
namespace event {

class event;

class quest_database : public event_database{
  public:
  quest_database(const std::string& url, int port, const std::string& name);

  void insert(event e) override final;

  private:
  const std::string m_url;
  const int m_port;
  const std::string m_name;
};

}
}

#endif // UMPIRE_quest_database_HPP
