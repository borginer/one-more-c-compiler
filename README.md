# One More C Compiler (OMCC)

OMCC is a C compiler written entirely in standard C++, following “Writing a C Compiler” by Nora Sandler.
The goal of this project is to build a minimal, self-hosted C compiler from scratch

## Build

```
make
```

This will compile the project and output an executable at `bin/omcc`.

## Usage

```
bin/omcc <file.c>
```

OMCC will parse and compile the given C source file.

## Goals

- Implement a working subset of C into x86
- Use only standard C++
- Learn compiler design

## References

- “Writing a C Compiler” by Nora Sandler (https://norasandler.com)
