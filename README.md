# kvstore

A miniature Redis-like in-memory key-value store, built from scratch in C++
as a learning project. The goal is C++ itself — syntax, RAII, pointers and
memory management — not necessarily full Redis-protocol compatibility.

## Layout

```
include/kvstore/   Public headers, one subdirectory per module
  core/             Command parsing/dispatch, shared types
  net/              Networking (sockets, event loop, client connections)
  storage/          The key-value store itself (data structures, expiry, ...)
src/                Implementation (.cpp) files, mirrors include/kvstore/
  main.cpp          Server entry point
tests/
  unit/             Unit tests (GoogleTest)
  integration/      End-to-end tests (e.g. spin up the server, hit it over a socket)
docs/               Design notes
```

Public headers live under `include/kvstore/<module>/` and implementation
files live under `src/<module>/`, so anything a consumer is meant to `#include`
is separated from internal details. Drop new `.cpp` files into `src/core`,
`src/net`, or `src/storage` and re-running CMake will pick them up
automatically — no need to edit `CMakeLists.txt`.

## Prerequisites

- A C++20 compiler (developed against GCC 13)
- CMake >= 3.16 (`sudo apt install cmake` on Debian/Ubuntu — not installed
  on this machine yet)
- Internet access on first configure, to fetch GoogleTest via CMake's
  `FetchContent`

## Build & run

```sh
cmake -S . -B build
cmake --build build
./build/kvstore_server
```

## Test

```sh
cmake --build build
ctest --test-dir build
```

A single smoke test (`tests/unit/sanity_test.cpp`) confirms the CMake +
GoogleTest wiring works; replace it with real tests as `core`, `net`, and
`storage` get implemented.

Set `-DKVSTORE_BUILD_TESTS=OFF` when configuring to skip building tests
(and avoid the GoogleTest download).
