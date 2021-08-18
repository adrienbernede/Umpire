//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016-20, Lawrence Livermore National Security, LLC and Umpire
// project contributors. See the COPYRIGHT file for details.
//
// SPDX-License-Identifier: (MIT)
//////////////////////////////////////////////////////////////////////////////
#ifndef UMPIRE_recorder_factory_HPP
#define UMPIRE_recorder_factory_HPP

#include "umpire/event/file_recorder.hpp"
#include "umpire/event/database_recorder.hpp"

using recorder_type = umpire::event::file_recorder;

namespace umpire {
namespace event {

class recorder_factory {
public:
static recorder_type& get_recorder();
};

}
}

#endif