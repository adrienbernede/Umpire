//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016-21, Lawrence Livermore National Security, LLC and Umpire
// project contributors. See the COPYRIGHT file for details.
//
// SPDX-License-Identifier: (MIT)
//////////////////////////////////////////////////////////////////////////////
#ifndef UMPIRE_DeviceAllocator_HPP
#define UMPIRE_DeviceAllocator_HPP

#include "umpire/Allocator.hpp"
#include <string.h>

namespace umpire {

/*!
 * \brief Lightweight allocator for use in GPU code
 */
class DeviceAllocator {
 public:
  /*!
   * \brief Construct a new DeviceAllocator that will use allocator to allocate
   * data. This constructor will only be called by the ResourceManager.
   *
   * \param allocator Allocator to use for allocating memory.
   */
  __host__ DeviceAllocator(Allocator allocator, size_t size, const char* name, size_t id);

  __host__ __device__ ~DeviceAllocator();

  __host__ __device__ DeviceAllocator(const DeviceAllocator& other);

  /*
   * \brief Allocate size objects of type T.
   *
   * \param size The number of objects to allocate.
   *
   * \return Pointer to the start of the allocated memory.
   */
  __device__ void* allocate(size_t size);

  /*
   * \brief Get the id associated with the
   *  current DeviceAllocator object.
   *
   * \return Returns the id.
   */
  __host__ __device__ size_t getID();

  /*
   * \brief Get the name associated with the
   *  current DeviceAllocator object.
   *
   * \return Returns the name.
   */
  __host__ __device__ const char* getName();

  /*
   * \brief Deallocate memory associated with Device Allocator object.
   */
  __host__ void destroy();

  /*
   * \brief Determine if this object has been initialized or not.
   */
  __host__ __device__ bool isInitialized();

 private:
  umpire::Allocator m_allocator;

  char* m_ptr;
  char m_name[64];
  unsigned int* m_counter;

  size_t m_id;
  size_t m_size;
  bool m_child;
};

} // end of namespace umpire

#endif // UMPIRE_DeviceAllocator_HPP
