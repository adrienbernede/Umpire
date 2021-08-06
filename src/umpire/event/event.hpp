//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016-20, Lawrence Livermore National Security, LLC and Umpire
// project contributors. See the COPYRIGHT file for details.
//
// SPDX-License-Identifier: (MIT)
//////////////////////////////////////////////////////////////////////////////
#ifndef UMPIRE_event_HPP
#define UMPIRE_event_HPP

#include "umpire/event/recorder_factory.hpp"

#include <sstream>
#include <string>
#include <type_traits>
#include <vector>


namespace umpire {
namespace event {

enum class category {operation, statistic};

class event
{
public:
  class builder;

  event() :
    timestamp{std::chrono::system_clock::now()}
  {}

  std::string name{"anon"};
  category cat{category::statistic};
  std::vector<std::pair<std::string, std::string>> tags{};
  std::vector<std::pair<std::string, int>> int_args{};
  std::vector<std::pair<std::string, std::string>> string_args{};
  const std::chrono::time_point<std::chrono::system_clock> timestamp{};
};

class event::builder
{
public:
  builder() : e{}
  {}

  builder& name(const std::string& n) {
    e.name = n;
    return *this;
  }

  builder& category(category c) {
    e.cat = c;
    return *this;
  }

  builder& arg(const std::string& k, int v) {
    e.int_args.push_back(
      std::make_pair(k, v)
    );
    return *this;
  }

  builder& arg(const std::string& k, const std::string& v) {
    e.string_args.push_back(
      std::make_pair(k, v)
    );
    return *this;
  }

  builder& arg(const std::string& k, void* p) {
    std::stringstream ss;
    ss << p;  
    std::string pointer{ss.str()}; 
    e.string_args.push_back(
      std::make_pair(k, pointer)
    );
    return *this;
  }

  builder& tag(const std::string& t, const std::string& v) {
    e.tags.push_back(
      std::make_pair(t, v)
    );
    return *this;
  }

  template<typename Recorder = decltype(recorder_factory::get_recorder())>
  void record(Recorder r = recorder_factory::get_recorder())
  {
    r.record(e);
  }

private:
  event e;
};

}
}
#endif