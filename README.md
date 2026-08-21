# Compiler

A simple C-based compiler project

## Build and Run

Configure the project with CMake:

```bash
cmake -S . -B compiler
```
-S -> specifies source directory
. -> source directory is current directory
-B -> specify build directory
compiler -> put generated build in compiler directory

(run above when changes made to cmake, for code changes only build is enough)


Build the project:

```bash
cmake --build compiler
```
build project using build files in compiler

Run the executable:

```powershell
.\compiler\Compiler.exe
```
(command to run executable)


## Compilation Steps

1. **CMake configuration** — CMake reads `CMakeLists.txt` and generates the build system inside `compiler/`.
2. **Compilation** — `main.c` and `lexer.c` are compiled into object files.
3. **Linking** — The object files are linked together to create the `Compiler.exe` executable.
4. **Execution** — The generated executable can then be run.

## Project Structure

* `main.c` — Program entry point and input-file handling.
* `lexer.c` — Lexer implementation.
* `lexer.h` — Token structures and lexer function declarations.
* `common.h` — Common standard-library includes.
* `CMakeLists.txt` — CMake build configuration.

## Current Status

The lexer reads an input file and produces a list of tokens. The planned next stages are parsing the tokens into an AST and generating code from the AST.
