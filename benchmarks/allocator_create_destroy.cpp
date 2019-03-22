//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2018-2019, Lawrence Livermore National Security, LLC.
// Produced at the Lawrence Livermore National Laboratory
//
// Created by David Beckingsale, david@llnl.gov
// LLNL-CODE-747640
//
// All rights reserved.
//
// This file is part of Umpire.
//
// For details, see https://github.com/LLNL/Umpire
// Please also see the LICENSE file for MIT license.
//////////////////////////////////////////////////////////////////////////////
#include "benchmark/benchmark.h"

#include "umpire/config.hpp"
#include "umpire/ResourceManager.hpp"
#include "umpire/Allocator.hpp"

static void benchmark_allocator_create(benchmark::State& state) {
  while (state.KeepRunning())
    umpire::Allocator alloc;
}

static void benchmark_allocator_create_destroy(benchmark::State& state) {
  while (state.KeepRunning())
  {
    {
    umpire::Allocator alloc;
    }
    benchmark::DoNotOptimize(10+10);
  }
}

static void benchmark_allocator_get(benchmark::State& state) {
  auto& rm = umpire::ResourceManager::getInstance();

  while (state.KeepRunning())
  {
    umpire::Allocator alloc(rm.getAllocator("HOST"));
  }
}

BENCHMARK(benchmark_allocator_create);
BENCHMARK(benchmark_allocator_create_destroy);
BENCHMARK(benchmark_allocator_get);

BENCHMARK_MAIN();
