# ft_printf

> A from-scratch reimplementation of the C standard `printf`, built as part of the 42 school curriculum.

---

## Table of Contents

- [Overview](#overview)
- [How `printf` Works — The Logical Idea](#how-printf-works--the-logical-idea)
- [Implementation from Zero](#implementation-from-zero)
  - [Step 1 — Variadic Functions](#step-1--variadic-functions)
  - [Step 2 — Format String Parsing](#step-2--format-string-parsing)
  - [Step 3 — Type Dispatch and Conversion](#step-3--type-dispatch-and-conversion)
  - [Step 4 — Writing Output and Counting Bytes](#step-4--writing-output-and-counting-bytes)
  - [Step 5 — Bonus: Flags, Width, and Precision](#step-5--bonus-flags-width-and-precision)
- [Project Structure](#project-structure)
- [Supported Conversions](#supported-conversions)
  - [Mandatory](#mandatory)
  - [Bonus Flags](#bonus-flags)
- [Architecture and Design Decisions](#architecture-and-design-decisions)
- [Building](#building)
- [Usage](#usage)
- [Testing](#testing)

---

## Overview

`ft_printf` is a reimplementation of the standard C library function `printf(3)`. It outputs a formatted string to standard output and returns the total number of characters written, exactly as the original does.

The goals of this project are:

- Understand **variadic functions** (`stdarg.h`) in C.
- Learn how to **parse a format string** character by character.
- Practice writing **modular, maintainable C code** split across multiple source files.
- Produce a **static library** (`libftprintf.a`) that can be linked into any project.

---

## How `printf` Works — The Logical Idea

At its core, `printf` takes a **format string** and a variable number of arguments:

```c
printf("Hello, %s! You are %d years old.\n", name, age);
```

The function walks through the format string one character at a time:

1. **Ordinary character** → write it directly to stdout.
2. **`%` character** → a conversion specification begins. Read what follows to determine:
   - Optional **flags** (`-`, `0`, `#`, ` `)
   - Optional **minimum field width** (e.g., `10`)
   - Optional **precision** (e.g., `.5`)
   - A **conversion specifier** (`c`, `s`, `d`, `x`, `p`, …)

   Then fetch the next variadic argument, format it according to the specification, and write the result.

This simple contract — *walk the string, act on `%`* — is the entire logical idea behind `printf`.

---

## Implementation from Zero

### Step 1 — Variadic Functions

C does not intrinsically know how many arguments a function receives beyond those declared in its prototype. The `<stdarg.h>` header provides three macros to iterate over the extra arguments safely:

| Macro | Purpose |
|---|---|
| `va_start(args, last)` | Initialize the `va_list`, anchored after the last named parameter. |
| `va_arg(args, type)` | Fetch the next argument, cast to `type`. |
| `va_end(args)` | Clean up the `va_list`. |

```c
int ft_printf(const char *format, ...)
{
    va_list args;
    int     count;

    count = 0;
    va_start(args, format);   // initialize after 'format'
    // ... parse and dispatch ...
    va_end(args);
    return (count);
}
```

**Important:** Every call to `va_start` must be paired with `va_end`. Forgetting `va_end` is undefined behavior on some ABIs.

---

### Step 2 — Format String Parsing

The parsing loop iterates over every byte of `format`:

```
while (*fmt)
    if current char == '%'
        read flags / width / precision / specifier
        dispatch to the right converter
    else
        write current char as-is
```

For the **mandatory** part, the only tokens needed after `%` are the single conversion letter. For the **bonus** part, the parser must also handle flags, width, and precision — so it becomes a small state machine:

```
% → [flags]* → [width]? → ['.' precision]? → specifier
```

This is implemented in `bonus/ft_printf_parse_bonus.c` using three focused helper functions (`ft_parse_flags`, `ft_parse_width`, `ft_parse_prec`), each advancing the format pointer before handing off to the next stage.

---

### Step 3 — Type Dispatch and Conversion

Once the specifier is known, a dispatcher function selects the correct handler:

```c
if      (spec == 'c') → print a character
else if (spec == 's') → print a string
else if (spec == 'd' || spec == 'i') → print a signed integer
else if (spec == 'u') → print an unsigned integer
else if (spec == 'x') → print hex lowercase
else if (spec == 'X') → print hex uppercase
else if (spec == 'p') → print a pointer address
else if (spec == '%') → print a literal '%'
```

Each handler fetches its argument via `va_arg` with the **correct type** — this is critical, because passing the wrong type to `va_arg` is undefined behavior.

Key conversion helpers:

- **Integers** (`ft_putnbr`): handle `INT_MIN` safely by casting to `unsigned long` before negating.
- **Hex / unsigned** (`ft_putunbr`): a single recursive function parameterised by base (10 or 16) and case flag covers `%u`, `%x`, and `%X`.
- **Pointers** (`ft_putptr`): cast `void *` to `unsigned long`, emit the `0x` prefix, then recurse into the hex printer. A `NULL` pointer prints `(nil)`.

---

### Step 4 — Writing Output and Counting Bytes

Rather than building the output in a heap-allocated buffer (which requires `malloc`/`free`), every character is written **immediately** to file descriptor 1 via the `write(2)` syscall. A pointer to an integer counter is threaded through all functions:

```c
void ft_putchar_count(char c, int *count)
{
    write(1, &c, 1);
    (*count)++;
}
```

Threading `count` as a pointer avoids global state and keeps the code thread-friendly. The final value of `count` is returned by `ft_printf` as the total number of bytes written.

---

### Step 5 — Bonus: Flags, Width, and Precision

The bonus part stores all modifiers in a struct before converting:

```c
typedef struct s_format
{
    int  left_align;   // '-' flag
    int  zero_pad;     // '0' flag
    int  hash;         // '#' flag
    int  space;        // ' ' flag
    int  width;        // minimum field width
    int  precision;    // -1 means "not set"
    char specifier;    // the conversion letter
}   t_format;
```

A generic `ft_print_num` function in `ft_printf_utils_bonus.c` applies all numeric formatting rules in one place:

1. Compute `prec_zeros`: extra leading zeros demanded by `.precision`.
2. Compute `wpad`: space padding demanded by `width`.
3. If right-aligned (`-` absent): emit space padding → prefix → zero padding → digits.
4. If left-aligned (`-` present): emit prefix → zero padding → digits → space padding.

Isolating this logic in one function means `%d`, `%u`, `%x`, `%X`, and `%p` all share the same padding path with no duplication.

---

## Project Structure

```
.
├── Makefile
├── includes/
│   ├── ft_printf.h           # Mandatory prototypes
│   └── ft_printf_bonus.h     # Bonus prototypes + t_format struct
├── src/                      # Mandatory sources
│   ├── ft_printf.c           # Entry point, format loop, dispatcher
│   ├── ft_printf_chars.c     # %c and %s handlers
│   ├── ft_printf_nbr.c       # %d/%i handler
│   └── ft_printf_hex.c       # %u, %x, %X, %p handlers
├── bonus/                    # Bonus sources (flags / width / precision)
│   ├── ft_printf_bonus.c     # Entry point, format loop, dispatcher
│   ├── ft_printf_parse_bonus.c  # Format spec parser
│   ├── ft_printf_utils_bonus.c  # Padding, number-to-string, ft_print_num
│   ├── ft_printf_chars_bonus.c  # %c and %s with width/precision
│   ├── ft_printf_nbr_bonus.c    # %d/%i with all flags
│   └── ft_printf_hex_bonus.c    # %u, %x, %X, %p with all flags
└── tests/
    └── main.c                # Manual test harness
```

---

## Supported Conversions

### Mandatory

| Specifier | Argument type | Output |
|---|---|---|
| `%c` | `int` (char) | Single character |
| `%s` | `char *` | Null-terminated string (`(null)` if pointer is NULL) |
| `%d` / `%i` | `int` | Signed decimal integer |
| `%u` | `unsigned int` | Unsigned decimal integer |
| `%x` | `unsigned int` | Lowercase hexadecimal |
| `%X` | `unsigned int` | Uppercase hexadecimal |
| `%p` | `void *` | Pointer address as `0x…` (`(nil)` if NULL) |
| `%%` | — | Literal `%` |

### Bonus Flags

| Flag / Field | Syntax | Effect |
|---|---|---|
| Left-align | `%-10d` | Pad with spaces on the right instead of the left |
| Zero-pad | `%010d` | Pad with `0` instead of spaces (ignored when `-` is set or precision is given) |
| Alternate form | `%#x` | Prepend `0x` / `0X` for non-zero hex values |
| Space prefix | `% d` | Prepend a space before positive numbers |
| Width | `%10s` | Minimum field width |
| Precision | `%.5s` / `%.3d` | Max string length / minimum digit count |

---

## Architecture and Design Decisions

| Decision | Rationale |
|---|---|
| **Static library (`libftprintf.a`)** | Allows the library to be linked into any project without distributing a shared object. |
| **No `malloc` in the output path** | Avoids allocation failures mid-format and simplifies cleanup — all output goes directly to `write(2)`. |
| **`unsigned long` for all pointer and large-unsigned arithmetic** | Avoids undefined behavior when negating `INT_MIN` and when casting pointer values for hex printing. |
| **Separate mandatory / bonus directories** | Keeps the mandatory submission clean; the Makefile builds one or the other cleanly. |
| **`t_format` struct for bonus** | Encapsulates all format modifiers in one place, eliminating long parameter lists and making the dispatch logic easy to read. |
| **Single `ft_print_num` helper** | All numeric specifiers share one padding/prefix routine, ensuring consistent behaviour and a single point of maintenance. |
| **`-Wall -Wextra -Werror`** | Any warning is treated as an error, enforcing clean code at compile time. |

---

## Building

```bash
# Build mandatory library
make

# Build bonus library (flags, width, precision)
make bonus

# Remove object files
make clean

# Remove object files and library
make fclean

# Full rebuild
make re
```

The output is `libftprintf.a` in the project root.

---

## Usage

Link the library against your program:

```bash
cc -Wall -Wextra -Werror -I./includes main.c -L. -lftprintf -o my_program
```

Include the header:

```c
#include "ft_printf.h"

int main(void)
{
    int n;

    n = ft_printf("%-10s | %05d | %#010x\n", "hello", 42, 255);
    ft_printf("Total chars written: %d\n", n);
    return (0);
}
```

---

## Testing

A minimal test harness is provided:

```bash
make test        # build with mandatory library
make test_bonus  # build with bonus library
./test_printf
```

For rigorous comparison against the system `printf`, pipe both outputs through `diff` or use a dedicated tester such as [pft](https://github.com/gavinfielder/pft) or [printf-unit-test](https://github.com/Tripouille/printfTester).

---

## License

This project is released under the [MIT License](LICENSE).
