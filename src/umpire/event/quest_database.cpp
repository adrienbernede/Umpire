//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016-20, Lawrence Livermore National Security, LLC and Umpire
// project contributors. See the COPYRIGHT file for details.
//
// SPDX-License-Identifier: (MIT)
//////////////////////////////////////////////////////////////////////////////

#include "umpire/event/quest_database.hpp"
#include "umpire/event/event.hpp"

#include <iostream>

namespace umpire {
namespace event {

quest_database::quest_database(const std::string& url, const std::string& port, const std::string& name) :
  event_database(),
  m_url(url),
  m_port(port),
  m_name(name),
  m_socket_desc{-1}
{
  addrinfo hints;
  std::memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  getaddrinfo(m_url.c_str(), m_port.c_str() ,&hints, &m_db_server);
  m_socket_desc = socket(m_db_server->ai_family, m_db_server->ai_socktype, m_db_server->ai_protocol);
  connect(m_socket_desc, m_db_server->ai_addr, m_db_server->ai_addrlen);
}

void 
quest_database::insert(event e)
{
  std::stringstream data;

  data << e.m_name;

  for (const auto& it : e.m_string_args ) {
    std::string name;
    std::string value;
    std::tie(name, value) = it;
    data << "," << name << "=" << value;
  }  

  for (const auto& it : e.m_tags ) {
    std::string name;
    std::string value;
    std::tie(name, value) = it;
    data << "," << name << "=" << value;
  }  

  data << " ";

  const std::string sep = (e.m_int_args.size()) > 1 ? "," : "";
  for (const auto& it : e.m_int_args ) {
    std::string name;
    int value;
    std::tie(name, value) = it;
    data << name << "=" << value << sep;
  }

  data << " " << std::to_string(static_cast<long>(
      std::chrono::time_point_cast<std::chrono::nanoseconds>(e.m_timestamp).time_since_epoch().count()));
  data << "\n";
  const std::string packet_string = data.str();
  const char* packet = packet_string.c_str();

  std::cout << packet_string << std::endl;

  auto bytes_sent = send(m_socket_desc , packet , strlen(packet) , 0);

  std::cout << "bytes sent: " << bytes_sent << std::endl;
}


}
}