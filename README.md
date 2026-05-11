# POS System (C++)

A console‑based Point of Sale system written in C++.  
Evolved from a simple cart/receipt prototype into a fully‑featured retail terminal with discount handling and admin controls.

## Versions

| File | Tag | Description |
|------|-----|-------------|
| `basic-pos.cpp` | `v1.0-basic` | Stock entry, add to cart, receipt generation |
| `full-pos.cpp` | `v2.0-full` | Discount codes, admin menu, stock alerts, item removal, polished output |

## How to Compile & Run

Each file is self‑contained. Use any C++ compiler (e.g., g++, clang++, or Visual Studio).

```bash
# Basic version
g++ -std=c++17 basic-pos.cpp -o basic-pos
./basic-pos

# Full version
g++ -std=c++17 full-pos.cpp -o full-pos
./full-pos