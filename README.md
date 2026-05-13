# ft_printf

> A from-scratch reimplementation of the C standard `printf`, built as part of the 42 school curriculum.
>
> C 标准库 `printf` 的从零实现，作为 42 学校课程项目完成。
>
> Reimplementación desde cero de `printf` de la biblioteca estándar de C, creada como parte del currículo de 42.

---

## Language / 语言 / Idioma

- [English](#english)
- [中文（普通话）](#中文普通话)
- [Español](#español)

---

## English

### Table of Contents

- [Overview](#overview-en)
- [How `printf` Works](#how-printf-works-en)
- [Implementation from Zero](#implementation-from-zero-en)
- [Project Structure](#project-structure-en)
- [Supported Conversions](#supported-conversions-en)
- [Architecture and Design Decisions](#architecture-and-design-decisions-en)
- [Building](#building-en)
- [Usage](#usage-en)
- [Testing](#testing-en)
- [License](#license-en)

### Overview {#overview-en}

`ft_printf` is a reimplementation of `printf(3)`. It writes formatted output to standard output and returns the total number of characters written.

Main goals:

- Learn **variadic functions** (`stdarg.h`).
- Parse a format string character by character.
- Build modular, maintainable C code.
- Deliver a static library: `libftprintf.a`.

### How `printf` Works {#how-printf-works-en}

`printf` reads a format string from left to right:

1. Normal character → write directly.
2. `%` → parse format specification (specifier, and in bonus: flags/width/precision), fetch one variadic argument, format it, and write it.

### Implementation from Zero {#implementation-from-zero-en}

1. **Variadic handling**: `va_start`, `va_arg`, `va_end`.
2. **Parsing**: detect `%` and parse specifier (plus flags/width/precision in bonus).
3. **Dispatch**: route to handlers for `%c`, `%s`, `%d`, `%i`, `%u`, `%x`, `%X`, `%p`, `%%`.
4. **Output counting**: write with `write(2)` and increment a shared counter.
5. **Bonus formatting**: apply `-`, `0`, `#`, space, width, precision via a `t_format` struct and shared numeric formatting path.

### Project Structure {#project-structure-en}

```text
.
├── Makefile
├── includes/
│   ├── ft_printf.h
│   └── ft_printf_bonus.h
├── src/
│   ├── ft_printf.c
│   ├── ft_printf_chars.c
│   ├── ft_printf_nbr.c
│   └── ft_printf_hex.c
├── bonus/
│   ├── ft_printf_bonus.c
│   ├── ft_printf_parse_bonus.c
│   ├── ft_printf_utils_bonus.c
│   ├── ft_printf_chars_bonus.c
│   ├── ft_printf_nbr_bonus.c
│   └── ft_printf_hex_bonus.c
└── tests/
    └── main.c
```

### Supported Conversions {#supported-conversions-en}

#### Mandatory

| Specifier | Argument type | Output |
|---|---|---|
| `%c` | `int` (char) | Single character |
| `%s` | `char *` | String (`(null)` if NULL) |
| `%d` / `%i` | `int` | Signed decimal |
| `%u` | `unsigned int` | Unsigned decimal |
| `%x` | `unsigned int` | Lowercase hexadecimal |
| `%X` | `unsigned int` | Uppercase hexadecimal |
| `%p` | `void *` | Pointer as `0x...` (`(nil)` if NULL) |
| `%%` | — | Literal `%` |

#### Bonus flags

| Flag / Field | Syntax | Effect |
|---|---|---|
| Left-align | `%-10d` | Pad spaces on the right |
| Zero-pad | `%010d` | Pad with `0` (if valid) |
| Alternate form | `%#x` | Prefix `0x` / `0X` for non-zero hex |
| Space prefix | `% d` | Leading space for positive numbers |
| Width | `%10s` | Minimum field width |
| Precision | `%.5s` / `%.3d` | Max string len / min digits |

### Architecture and Design Decisions {#architecture-and-design-decisions-en}

- Static library output: `libftprintf.a`.
- Direct `write(2)` path (no `malloc` in output path).
- `unsigned long` used for pointer and wide unsigned arithmetic safety.
- Mandatory and bonus kept in separate directories.
- Bonus parsing state kept in `t_format`.
- Shared numeric formatting logic avoids duplication.
- Compiled with `-Wall -Wextra -Werror`.

### Building {#building-en}

```bash
make         # mandatory library
make bonus   # bonus library
make clean   # remove object files
make fclean  # remove object files + library
make re      # full rebuild
```

Output: `libftprintf.a`.

### Usage {#usage-en}

```bash
cc -Wall -Wextra -Werror -I./includes main.c -L. -lftprintf -o my_program
```

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

### Testing {#testing-en}

```bash
make test
make test_bonus
./test_printf
```

For strict comparison with system `printf`, compare outputs using `diff` or external testers such as `pft` / `printfTester`.

### License {#license-en}

MIT License. See [LICENSE](LICENSE).

---

## 中文（普通话）

### 目录

- [概览](#概览-zh)
- [`printf` 的工作原理](#printf-的工作原理-zh)
- [从零实现思路](#从零实现思路-zh)
- [项目结构](#项目结构-zh)
- [支持的转换说明符](#支持的转换说明符-zh)
- [架构与设计决策](#架构与设计决策-zh)
- [构建](#构建-zh)
- [使用](#使用-zh)
- [测试](#测试-zh)
- [许可证](#许可证-zh)

### 概览 {#概览-zh}

`ft_printf` 是对标准库 `printf(3)` 的重写。它将格式化后的内容输出到标准输出，并返回写入的总字符数。

主要目标：

- 学习 **可变参数函数**（`stdarg.h`）。
- 学习逐字符解析格式字符串。
- 练习模块化、可维护的 C 代码组织。
- 产出静态库 `libftprintf.a`。

### `printf` 的工作原理 {#printf-的工作原理-zh}

`printf` 从左到右扫描格式字符串：

1. 普通字符：直接输出。
2. 遇到 `%`：开始解析格式（基础部分只需说明符，bonus 还包含 flag/width/precision），读取下一个参数并按规则格式化后输出。

### 从零实现思路 {#从零实现思路-zh}

1. **可变参数处理**：`va_start`、`va_arg`、`va_end`。
2. **解析器**：识别 `%` 并解析说明符（bonus 还需解析 flag/宽度/精度）。
3. **分发层**：按说明符调用对应处理函数（`%c`、`%s`、`%d`、`%i`、`%u`、`%x`、`%X`、`%p`、`%%`）。
4. **输出计数**：通过 `write(2)` 立即输出，并统一累加字符计数。
5. **bonus 格式化**：使用 `t_format` 保存解析结果，统一应用 `-`、`0`、`#`、空格、宽度、精度规则。

### 项目结构 {#项目结构-zh}

```text
.
├── Makefile
├── includes/
│   ├── ft_printf.h
│   └── ft_printf_bonus.h
├── src/
│   ├── ft_printf.c
│   ├── ft_printf_chars.c
│   ├── ft_printf_nbr.c
│   └── ft_printf_hex.c
├── bonus/
│   ├── ft_printf_bonus.c
│   ├── ft_printf_parse_bonus.c
│   ├── ft_printf_utils_bonus.c
│   ├── ft_printf_chars_bonus.c
│   ├── ft_printf_nbr_bonus.c
│   └── ft_printf_hex_bonus.c
└── tests/
    └── main.c
```

### 支持的转换说明符 {#支持的转换说明符-zh}

#### 基础（Mandatory）

| 说明符 | 参数类型 | 输出 |
|---|---|---|
| `%c` | `int`（字符） | 单个字符 |
| `%s` | `char *` | 字符串（NULL 时输出 `(null)`） |
| `%d` / `%i` | `int` | 有符号十进制 |
| `%u` | `unsigned int` | 无符号十进制 |
| `%x` | `unsigned int` | 小写十六进制 |
| `%X` | `unsigned int` | 大写十六进制 |
| `%p` | `void *` | 指针地址 `0x...`（NULL 时 `(nil)`） |
| `%%` | — | 字面量 `%` |

#### Bonus 标志

| 标志 / 字段 | 示例 | 作用 |
|---|---|---|
| 左对齐 | `%-10d` | 右侧补空格 |
| 零填充 | `%010d` | 用 `0` 填充（满足规则时生效） |
| 替代形式 | `%#x` | 非零十六进制前缀 `0x` / `0X` |
| 空格前缀 | `% d` | 正数前补一个空格 |
| 宽度 | `%10s` | 最小字段宽度 |
| 精度 | `%.5s` / `%.3d` | 字符串最大长度 / 数字最小位数 |

### 架构与设计决策 {#架构与设计决策-zh}

- 输出为静态库 `libftprintf.a`。
- 输出路径不使用 `malloc`，直接 `write(2)`。
- 指针与较大无符号运算统一使用 `unsigned long`。
- mandatory 与 bonus 目录分离，职责清晰。
- bonus 通过 `t_format` 聚合格式信息。
- 数字格式化路径复用，减少重复逻辑。
- 编译参数为 `-Wall -Wextra -Werror`。

### 构建 {#构建-zh}

```bash
make         # 构建 mandatory
make bonus   # 构建 bonus
make clean   # 删除目标文件
make fclean  # 删除目标文件和库
make re      # 全量重建
```

产物：`libftprintf.a`。

### 使用 {#使用-zh}

```bash
cc -Wall -Wextra -Werror -I./includes main.c -L. -lftprintf -o my_program
```

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

### 测试 {#测试-zh}

```bash
make test
make test_bonus
./test_printf
```

如需严格对比系统 `printf`，可将输出通过 `diff` 比较，或使用 `pft` / `printfTester` 等测试器。

### 许可证 {#许可证-zh}

MIT 许可证，详见 [LICENSE](LICENSE)。

---

## Español

### Índice

- [Resumen](#resumen-es)
- [Cómo funciona `printf`](#cómo-funciona-printf-es)
- [Implementación desde cero](#implementación-desde-cero-es)
- [Estructura del proyecto](#estructura-del-proyecto-es)
- [Conversiones soportadas](#conversiones-soportadas-es)
- [Arquitectura y decisiones de diseño](#arquitectura-y-decisiones-de-diseño-es)
- [Compilación](#compilación-es)
- [Uso](#uso-es)
- [Pruebas](#pruebas-es)
- [Licencia](#licencia-es)

### Resumen {#resumen-es}

`ft_printf` es una reimplementación de `printf(3)`. Escribe salida formateada en stdout y devuelve el número total de caracteres escritos.

Objetivos principales:

- Entender **funciones variádicas** (`stdarg.h`).
- Aprender a parsear una cadena de formato carácter por carácter.
- Escribir C modular y mantenible.
- Generar una biblioteca estática: `libftprintf.a`.

### Cómo funciona `printf` {#cómo-funciona-printf-es}

`printf` recorre la cadena de formato de izquierda a derecha:

1. Carácter normal → se escribe directamente.
2. `%` → empieza una especificación de formato (en bonus: flags/ancho/precisión), se toma el siguiente argumento variádico, se formatea y se escribe.

### Implementación desde cero {#implementación-desde-cero-es}

1. **Variádicas**: `va_start`, `va_arg`, `va_end`.
2. **Parser**: detectar `%` y leer especificadores (más flags/ancho/precisión en bonus).
3. **Despacho**: elegir handler según `%c`, `%s`, `%d`, `%i`, `%u`, `%x`, `%X`, `%p`, `%%`.
4. **Conteo de salida**: escribir con `write(2)` y acumular el contador compartido.
5. **Bonus**: guardar metadatos en `t_format` y aplicar reglas de padding/formato de forma uniforme.

### Estructura del proyecto {#estructura-del-proyecto-es}

```text
.
├── Makefile
├── includes/
│   ├── ft_printf.h
│   └── ft_printf_bonus.h
├── src/
│   ├── ft_printf.c
│   ├── ft_printf_chars.c
│   ├── ft_printf_nbr.c
│   └── ft_printf_hex.c
├── bonus/
│   ├── ft_printf_bonus.c
│   ├── ft_printf_parse_bonus.c
│   ├── ft_printf_utils_bonus.c
│   ├── ft_printf_chars_bonus.c
│   ├── ft_printf_nbr_bonus.c
│   └── ft_printf_hex_bonus.c
└── tests/
    └── main.c
```

### Conversiones soportadas {#conversiones-soportadas-es}

#### Mandatory

| Especificador | Tipo de argumento | Salida |
|---|---|---|
| `%c` | `int` (char) | Carácter único |
| `%s` | `char *` | Cadena (`(null)` si es NULL) |
| `%d` / `%i` | `int` | Entero decimal con signo |
| `%u` | `unsigned int` | Entero decimal sin signo |
| `%x` | `unsigned int` | Hexadecimal en minúsculas |
| `%X` | `unsigned int` | Hexadecimal en mayúsculas |
| `%p` | `void *` | Dirección `0x...` (`(nil)` si es NULL) |
| `%%` | — | `%` literal |

#### Flags bonus

| Flag / Campo | Sintaxis | Efecto |
|---|---|---|
| Alineación izquierda | `%-10d` | Espacios a la derecha |
| Relleno con ceros | `%010d` | Relleno con `0` (si aplica) |
| Forma alternativa | `%#x` | Prefijo `0x` / `0X` para hex no cero |
| Prefijo espacio | `% d` | Espacio inicial en positivos |
| Ancho | `%10s` | Ancho mínimo de campo |
| Precisión | `%.5s` / `%.3d` | Máx. longitud / mín. dígitos |

### Arquitectura y decisiones de diseño {#arquitectura-y-decisiones-de-diseño-es}

- Biblioteca estática de salida: `libftprintf.a`.
- Ruta de salida directa con `write(2)` (sin `malloc` en esa ruta).
- Uso de `unsigned long` para punteros y aritmética grande sin signo.
- Separación clara entre mandatory y bonus.
- Estado de formato bonus agrupado en `t_format`.
- Lógica numérica compartida para evitar duplicación.
- Compilación estricta con `-Wall -Wextra -Werror`.

### Compilación {#compilación-es}

```bash
make         # biblioteca mandatory
make bonus   # biblioteca bonus
make clean   # limpia objetos
make fclean  # limpia objetos + biblioteca
make re      # recompilación completa
```

Salida: `libftprintf.a`.

### Uso {#uso-es}

```bash
cc -Wall -Wextra -Werror -I./includes main.c -L. -lftprintf -o my_program
```

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

### Pruebas {#pruebas-es}

```bash
make test
make test_bonus
./test_printf
```

Para comparar estrictamente con `printf` del sistema, usa `diff` sobre ambas salidas o testers externos como `pft` / `printfTester`.

### Licencia {#licencia-es}

Licencia MIT. Ver [LICENSE](LICENSE).
