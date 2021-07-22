//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016-20, Lawrence Livermore National Security, LLC and Umpire
// project contributors. See the COPYRIGHT file for details.
//
// SPDX-License-Identifier: (MIT)
//////////////////////////////////////////////////////////////////////////////

#include "umpire/event/recorder_factory.hpp"
#include "umpire/util/io.hpp"

#include "umpire/event/quest_database.hpp"

#if !defined(_MSC_VER)
#include <unistd.h> // getpid()
#else
#include <process.h>
#define getpid _getpid
#include <direct.h>
#endif


namespace umpire {
namespace event {

recorder_type&
recorder_factory::get_recorder()
{
  //static const std::string filename{util::make_unique_filename(util::get_io_output_dir(),
  //util::get_io_output_basename(), getpid(), "stats")};
  //static file_recorder recorder{filename};

  static quest_database db{"localhost", "9009", "db"};
  static database_recorder recorder(&db);

  return recorder;
}

}
}