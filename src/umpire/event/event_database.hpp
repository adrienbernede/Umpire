//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016-20, Lawrence Livermore National Security, LLC and Umpire
// project contributors. See the COPYRIGHT file for details.
//
// SPDX-License-Identifier: (MIT)
//////////////////////////////////////////////////////////////////////////////
#ifndef UMPIRE_event_database_HPP
#define UMPIRE_event_database_HPP

namespace umpire {
namespace event {

class event;

class event_database {
  public:
  virtual void insert(event e) = 0;
};

}
}

#endif // UMPIRE_event_database_HPP
