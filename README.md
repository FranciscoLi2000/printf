# printf (ft_printf reimplementation)

![Language](https://img.shields.io/badge/language-C-blue)
![License](https://img.shields.io/badge/License-MIT-green)

A from-scratch reimplementation of the C standard `printf` function, delivered as a static library with mandatory and bonus formatting support.

## Table of Contents

- [Project Introduction](#project-introduction)
- [Tech Stack](#tech-stack)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing Guide](#contributing-guide)
- [License](#license)

## Project Introduction

This project provides `ft_printf`, a learning-focused reimplementation of `printf(3)`. It parses format strings, handles variadic arguments, and writes formatted output to standard output while returning the number of characters written. The project ships as a static library `libftprintf.a` and includes a bonus implementation with flags, width, and precision handling.

## Tech Stack

- C (ISO C / POSIX)
- Make
- Standard library headers (`stdarg.h`, `unistd.h`, etc.)

## Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/FranciscoLi2000/printf.git
   cd printf
   ```

2. Build the mandatory library:

   ```bash
   make
   ```

3. (Optional) Build the bonus library:

   ```bash
   make bonus
   ```

The output library is `libftprintf.a` in the project root.

## Usage

Compile your program and link against `libftprintf.a`:

```bash
cc -Wall -Wextra -Werror -I./includes main.c -L. -lftprintf -o my_program
```

Example usage:

```c
#include "ft_printf.h"

int main(void)
{
    int count;

    count = ft_printf("%-10s | %05d | %#010x\n", "hello", 42, 255);
    ft_printf("Total chars written: %d\n", count);
    return (0);
}
```

To build the test binary:

```bash
make test
./test_printf
```

To build and run the bonus test binary (same output binary, linked with bonus objects):

```bash
make test_bonus
./test_printf
```

## Contributing Guide

Contributions are welcome. Please follow these steps:

1. Fork the repository and create a feature branch.
2. Make your changes with clear commit messages.
3. Run `make test` (and `make test_bonus` if you touched bonus logic).
4. Open a pull request describing the changes and rationale.

## License

MIT License. See [LICENSE](LICENSE).
