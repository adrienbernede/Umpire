FROM axom/compilers:gcc-5 AS gcc5
ENV GTEST_COLOR=1
COPY --chown=axom:axom . /home/axom/workspace
WORKDIR /home/axom/workspace
RUN mkdir build && cd build && cmake -DUMPIRE_ENABLE_DEVELOPER_DEFAULTS=On -DCMAKE_CXX_COMPILER=g++ ..
RUN cd build && make -j 16
RUN cd build && ctest -T test --output-on-failure

FROM axom/compilers:gcc-6 AS gcc6
ENV GTEST_COLOR=1
COPY --chown=axom:axom . /home/axom/workspace
WORKDIR /home/axom/workspace
RUN mkdir build && cd build && cmake -DUMPIRE_ENABLE_DEVELOPER_DEFAULTS=On -DCMAKE_CXX_COMPILER=g++  ..
RUN cd build && make -j 16
RUN cd build && ctest -T test --output-on-failure

FROM axom/compilers:gcc-7 AS gcc7
ENV GTEST_COLOR=1
COPY --chown=axom:axom . /home/axom/workspace
WORKDIR /home/axom/workspace
RUN mkdir build && cd build && cmake -DUMPIRE_ENABLE_DEVELOPER_DEFAULTS=On -DCMAKE_CXX_COMPILER=g++  ..
RUN cd build && make -j 16
RUN cd build && ctest -T test --output-on-failure

FROM axom/compilers:gcc-8 AS gcc
ENV GTEST_COLOR=1
COPY --chown=axom:axom . /home/axom/workspace
WORKDIR /home/axom/workspace
RUN mkdir build && cd build && cmake -DUMPIRE_ENABLE_C=On -DENABLE_COVERAGE=On -DCMAKE_BUILD_TYPE=Debug -DUMPIRE_ENABLE_DEVELOPER_DEFAULTS=On -DCMAKE_CXX_COMPILER=g++  ..
RUN cd build && make -j 16
RUN cd build && ctest -T test --output-on-failure

FROM axom/compilers:clang-4 AS clang4
ENV GTEST_COLOR=1
COPY --chown=axom:axom . /home/axom/workspace
WORKDIR /home/axom/workspace
RUN mkdir build && cd build && cmake -DUMPIRE_ENABLE_DEVELOPER_DEFAULTS=On -DCMAKE_CXX_COMPILER=clang++ ..
RUN cd build && make -j 16
RUN cd build && ctest -T test --output-on-failure

FROM axom/compilers:clang-5 AS clang5
ENV GTEST_COLOR=1
COPY --chown=axom:axom . /home/axom/workspace
WORKDIR /home/axom/workspace
RUN mkdir build && cd build && cmake -DUMPIRE_ENABLE_DEVELOPER_DEFAULTS=On -DCMAKE_CXX_COMPILER=clang++ ..
RUN cd build && make -j 16
RUN cd build && ctest -T test --output-on-failure

FROM axom/compilers:clang-6 AS clang
ENV GTEST_COLOR=1
COPY --chown=axom:axom . /home/axom/workspace
WORKDIR /home/axom/workspace
RUN mkdir build && cd build && cmake -DUMPIRE_ENABLE_DEVELOPER_DEFAULTS=On -DCMAKE_CXX_COMPILER=clang++ ..
RUN cd build && make -j 16
RUN cd build && ctest -T test --output-on-failure

FROM axom/compilers:nvcc-10 AS nvcc
ENV GTEST_COLOR=1
COPY --chown=axom:axom . /home/axom/workspace
WORKDIR /home/axom/workspace
RUN mkdir build && cd build && cmake -DUMPIRE_ENABLE_DEVELOPER_DEFAULTS=On -DCMAKE_CXX_COMPILER=g++ -DENABLE_CUDA=On ..
RUN cd build && make -j 16

FROM axom/compilers:rocm AS hip
ENV GTEST_COLOR=1
COPY --chown=axom:axom . /home/axom/workspace
WORKDIR /home/axom/workspace
ENV HCC_AMDGPU_TARGET=gfx900
RUN mkdir build && cd build && cmake -DROCM_ROOT_DIR=/opt/rocm/include -DHIP_RUNTIME_INCLUDE_DIRS="/opt/rocm/include;/opt/rocm/hip/include" -DUMPIRE_ENABLE_DEVELOPER_DEFAULTS=On -DENABLE_HIP=On ..
RUN cd build && make -j 16

FROM axom/compilers:oneapi-2021.2.0 AS sycl
ENV GTEST_COLOR=1
COPY --chown=axom:axom . /home/axom/workspace
WORKDIR /home/axom/workspace
RUN /bin/bash -c "source /opt/intel/oneapi/setvars.sh && mkdir build && cd build && cmake -DCMAKE_CXX_COMPILER=dpcpp -DENABLE_WARNINGS_AS_ERRORS=Off -DUMPIRE_ENABLE_DEVELOPER_DEFAULTS=On -DUMPIRE_ENABLE_SYCL=On .."
RUN /bin/bash -c "source /opt/intel/oneapi/setvars.sh && cd build && make -j 16"

FROM axom/compilers:clang-10 AS check
ENV GTEST_COLOR=1
COPY --chown=axom:axom . /home/axom/workspace
WORKDIR /home/axom/workspace
RUN mkdir build && cd build && cmake -DENABLE_DEVELOPER_DEFAULTS=On -DENABLE_CLANGQUERY=Off -DENABLE_CLANGTIDY=Off -DENABLE_CPPCHECK=Off -DCMAKE_CXX_COMPILER=clang++ ..
RUN cd build && make check