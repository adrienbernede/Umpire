//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016-21, Lawrence Livermore National Security, LLC and Umpire
// project contributors. See the COPYRIGHT file for details.
//
// SPDX-License-Identifier: (MIT)
//////////////////////////////////////////////////////////////////////////////
#ifndef UMPIRE_TypedAllocator_INL
#define UMPIRE_TypedAllocator_INL

#include "umpire/util/Macros.hpp"

namespace umpire {

template <typename T>
TypedAllocator<T>::TypedAllocator(Allocator allocator) : m_allocator(allocator)
{
}

template <typename T>
template <typename U>
TypedAllocator<T>::TypedAllocator(const TypedAllocator<U>& other) : m_allocator(other.m_allocator)
{
}

template <typename T>
T* TypedAllocator<T>::allocate(std::size_t size)
{
  return static_cast<T*>(m_allocator.allocate(sizeof(T) * size));
}

template <typename T>
void TypedAllocator<T>::deallocate(T* ptr, std::size_t UMPIRE_UNUSED_ARG(size))
{
  m_allocator.deallocate(ptr);
}

} // end of namespace umpire

template <typename U, typename V>
bool operator==(const umpire::TypedAllocator<U>& lhs, const umpire::TypedAllocator<V>& rhs)
{
  return lhs.m_allocator.getId() == rhs.m_allocator.getId();
}

template <typename U, typename V>
bool operator!=(const umpire::TypedAllocator<U>& lhs, const umpire::TypedAllocator<V>& rhs)
{
  return !(lhs == rhs);
}

#endif // UMPIRE_TypedAllocator_INL
