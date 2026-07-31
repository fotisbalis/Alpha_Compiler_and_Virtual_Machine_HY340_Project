# Alpha Compiler & Virtual Machine

**Balis Fotios Marios** *· csd4958*

The project implements a compiler and a virtual machine for the Alpha programming language (similar to Javascript).
The language used for the implementation is c alongside Flex for lexical analysis and Yacc Bison for syntactical analysis.

---

## Prerequisites

Install Flex, Bison and the build tools:

```sh
sudo apt update
sudo apt install -y flex bison build-essential
```

## How to compile

- To compile the entire project run `$make all`
- To compile only the compiler run `$make compiler`
- To compile only the virtual machine run `$make vm`
- To clean all the compile time and runtime created files run `$make clean`

## How to run

Run `$make run TEST=[input file]`

## How to run only the compiler

Run `$./alpha_compiler [input file]`

## Compiler output

If compilation is not successful, the console output will be the existing errors.

If compilation is successful, then the following files are created:

| File | Description |
| --- | --- |
| `quads.txt` | assembly like intermediate code |
| `instructions.txt` | target code |
| `symbol_table.txt` | symbol table content |
| `syntax_rules.txt` | grammar reduce rules used for the syntactical analysis |
| `alpha.abc` | binary version of instructions.txt and input of the virtual machine |

## How to run only the virtual machine

Run `$./alpha_vm alpha.abc`

## Virtual Machine output

Console type output of the input code

---

## Binary file info

The compiler writes the target code in a custom `.abc` binary format, which is read directly by the virtual machine.

### Structure of `alpha.abc`

1. Magic number (unsigned, 32-bit)
2. String constants table
3. Number constants table
4. User functions table
5. Library functions table
6. Instructions table

### Magic number

`340200501`

### String constants table

- total string count (int, 32-bit)
- for each string:
  - string length (unsigned, 32-bit)
  - raw string bytes (char[length], no terminating '\0' stored in file)

### Number constants table

- total number count (int, 32-bit)
- for each number:
  - number value (double, 64-bit)

### User functions table

- total user function count (int, 32-bit)
- for each user function:
  - starting instruction address / taddress (int, 32-bit)
  - local variables count / localSize (int, 32-bit)
  - function name length (unsigned, 32-bit)
  - function name bytes (char[length])

### Library functions table

- total library function count (int, 32-bit)
- for each library function:
  - function name length (unsigned, 32-bit)
  - function name bytes (char[length])

### Instructions table

- total instruction count (int, 32-bit)
- for each instruction:
  - opcode (int, 32-bit)
  - result.type (int, 32-bit)
  - result.val (unsigned, 32-bit)
  - arg1.type (int, 32-bit)
  - arg1.val (unsigned, 32-bit)
  - arg2.type (int, 32-bit)
  - arg2.val (unsigned, 32-bit)
  - source line (int, 32-bit)

### Operand type encoding

| Value | Type |
| ---: | --- |
| 0 | label |
| 1 | global |
| 2 | formal |
| 3 | local |
| 4 | number |
| 5 | string |
| 6 | bool |
| 7 | nil |
| 8 | userfunc |
| 9 | libfunc |
| 10 | retval |
| 11 | unused |

### Opcode encoding

| Value | Opcode |
| ---: | --- |
| 0 | assign |
| 1 | add |
| 2 | sub |
| 3 | mul |
| 4 | div |
| 5 | mod |
| 6 | uminus |
| 7 | and |
| 8 | or |
| 9 | not |
| 10 | jeq |
| 11 | jne |
| 12 | jle |
| 13 | jge |
| 14 | jlt |
| 15 | jgt |
| 16 | jump |
| 17 | call |
| 18 | pusharg |
| 19 | funcenter |
| 20 | funcexit |
| 21 | newtable |
| 22 | tablegetelem |
| 23 | tablesetelem |
| 24 | nop |
