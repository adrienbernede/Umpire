//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016-20, Lawrence Livermore National Security, LLC and Umpire
// project contributors. See the COPYRIGHT file for details.
//
// SPDX-License-Identifier: (MIT)
//////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>

#include "umpire/Allocator.hpp"
#include "umpire/ResourceManager.hpp"
#include "umpire/strategy/DynamicPoolMap.hpp"
#include "umpire/util/MemoryResourceTraits.hpp"

#include "umpire/Umpire.cpp"
#include "umpire/config.hpp"
#include "umpire/util/Platform.hpp"

using myResource = umpire::MemoryResourceTraits::resource_type;
using cPlatform = camp::resources::Platform;

int main()
{
  auto& rm = umpire::ResourceManager::getInstance();
  auto host_alloc = rm.makeAllocator<umpire::strategy::DynamicPoolMap>(
      "host_dynamicpool", rm.getAllocator("HOST"));

  double* data = static_cast<double*>(host_alloc.allocate(1024*sizeof(double)));

  std::cout << "Testing the host platform..." << std::endl;
  if(is_accessible(cPlatform::host, host_alloc)) {
    std::cout << "The allocator, " << host_alloc.getName() << 
                 " is accessible." << std::endl << std::endl;
  }
  
  std::cout << "Testing another platform..." << std::endl;
  if(is_accessible(cPlatform::cuda, host_alloc)) {
    std::cout << "This would be weird..." <<std::endl;
  } 
  
  host_alloc.deallocate(data);

  return 0;
}
