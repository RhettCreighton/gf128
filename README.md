<!-- README.md for GF128 Arithmetic Library -->
# GF128 C99 Library

[![CI](https://github.com/RhettCreighton/gf128/actions/workflows/ci.yml/badge.svg)](https://github.com/RhettCreighton/gf128/actions)

A high-performance finite field GF(2^128) arithmetic library in C99, featuring multiple optimized multiplication implementations and automatic runtime dispatch.

## Features
- Bitwise reference implementation (gf128_mul_base)
- Table-driven multiplication (gf128_mul_table)
- Hardware-accelerated PCLMUL intrinsic path (gf128_mul_pclmul)
- Karatsuba optimization (3 CLMULs)
- AVX2 2-way batched PCLMUL
- AVX-512 4-way and 8-way super-batched PCLMUL
- GFNI-accelerated reduction
- Runtime dispatch (`gf128_mul`) and hardware checks
- CMake package export for easy integration
- Unit tests and benchmarks

## Installation
```sh
git clone https://github.com/RhettCreighton/gf128.git
cd gf128
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release \
      -DUSE_AVX2=ON \
      -DUSE_AVX512=ON \
      -DUSE_GFNI=ON \
      -DENABLE_MICROTUNE=ON \
      ..
make
sudo make install
```

## CMake Integration
Use the installed package in your CMake project:
```cmake
cmake_minimum_required(VERSION 3.5)
project(myapp C)

find_package(gf128 0.1.0 REQUIRED)

add_executable(myapp main.c)
target_link_libraries(myapp PRIVATE gf128::gf128)
```

## pkg-config Integration

If you prefer pkg-config, the library also installs a `.pc` file. To compile:

```sh
gcc $(pkg-config --cflags --libs gf128) myapp.c -o myapp
```

Control performance variants at configure time:
```sh
cmake -DUSE_AVX2=ON -DUSE_AVX512=ON -DUSE_GFNI=ON -DENABLE_MICROTUNE=ON ..
```

## API Usage
Include the public header:
```c
#include <gf128.h>
```
Basic operations:
```c
gf128_t a = gf128_one();
gf128_t b = gf128_from_be(bytes);
gf128_t c = gf128_mul(a, b); // automatic dispatch to fastest variant
```
Other functions:
- `gf128_add(a, b)` – field addition (XOR)
- `gf128_mul_table(a, b)` – table-driven multiply
- `gf128_mul_pclmul(a, b)` – PCLMUL intrinsic path (or fallback)
- `gf128_mul_pclmul_avx2(a, b)` – AVX2 variant
- `gf128_mul_pclmul_avx512(a, b)` – AVX-512 variant
- Runtime checks: `gf128_has_pclmul()`, `gf128_has_avx2()`, `gf128_has_avx512()`, `gf128_has_gfni()`

## Examples
See `examples/example.c` for usage examples.

## Benchmarks
Use `benchmarks/bench_mul` to measure performance; see `codex.md` for detailed instructions.

## Release Notes

See the [CHANGELOG](CHANGELOG.md) for detailed release notes and version history.

## License
Licensed under the Apache License, Version 2.0. See [LICENSE](LICENSE) for details.