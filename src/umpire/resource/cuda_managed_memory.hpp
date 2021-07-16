//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016-20, Lawrence Livermore National Security, LLC and Umpire
// project contributors. See the COPYRIGHT file for details.
//
// SPDX-License-Identifier: (MIT)
//////////////////////////////////////////////////////////////////////////////
#pragma once

#include "umpire/resource/memory_resource.hpp"
#include "umpire/alloc/cuda_malloc_managed_allocator.hpp"

namespace umpire {
namespace resource {

  /*!
   * \brief Concrete MemoryResource object that uses the template _allocator to
   * allocate and deallocate memory.
   */
template<bool Tracking=true>
class cuda_managed_memory :
  public memory_resource<umpire::resources::cuda_platform>
{
  public: 

  static cuda_managed_memory* get() {
    static cuda_managed_memory self;
    return &self;
  }

  void* allocate(std::size_t n) {
    void* ret = umpire::alloc::cuda_malloc_managed_allocator::allocate(n);
    if constexpr(Tracking) {
      return this->track_allocation(this, ret, n);
    } else {
      return ret;
    }
  }

  void deallocate(void* ptr) {
    if constexpr(Tracking) {
      this->untrack_allocation(ptr);
    }
    umpire::alloc::cuda_malloc_managed_allocator::deallocate(ptr);
  }

  camp::resources::Platform get_platform() override
  {
    return camp::resources::Platform::cuda;
  }

  private:
    cuda_managed_memory() :
      memory_resource<umpire::resource::cuda_platform>{"UM"}
    {}
};

} // end of namespace resource
} // end of namespace umpire