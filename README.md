# Utilities Implementation: cat and grep
## Project Overview
This project implements two core UNIX utilities:
1. `s21_cat` - File concatenation and display tool
2. `s21_grep` - Pattern searching tool
Both implementations closely follow the behavior of their GNU counterparts with support for common options.
## Project Structure
### s21_cat Implementation
cat/
- ├── applyFlagsOnLine.c
- ├── applyFlagsOnLine.h
- ├── checkArguments.c 
- ├── initializeArrays.c 
- ├── main.c 
- ├── Makefile
- ├── workWithArguments.h
- └── test/ # Test files and scripts
  - ├── 1.txt
  - ├── 2.txt
  - ├── 3.txt
  - └── test.sh
### s21_grep Implementation
grep/
- ├── checkArguments.c 
- ├── checkArguments.h
- ├── grep.c
- ├── grep.h
- ├── initializeArrays.c
- ├── initializeArrays.h
- ├── main.c
- ├── Makefile
- └── test/
  - ├── 1.txt
  - ├── 2.txt
  - ├── 3.txt
  - ├── patterns.txt
  - └── test.sh
## Implemented Features
### s21_cat Options
| Option | GNU Equivalent | Description |
|--------|----------------|-------------|
| `-b`   | `--number-nonblank` | Number only non-empty lines |
| `-e`   | `-E` (without `-v`) | Show end-of-line as `$` (implies `-v`) |
| `-n`   | `--number`      | Number all output lines |
| `-s`   | `--squeeze-blank` | Suppress repeated empty lines |
| `-t`   | `-T` (without `-v`) | Show tabs as `^I` (implies `-v`) |
### s21_grep Options
| Option | Description |
|--------|-------------|
| `-e`   | Specify pattern |
| `-i`   | Case-insensitive search |
| `-v`   | Invert match (show non-matching lines) |
| `-c`   | Count of matching lines only |
| `-l`   | Show matching files only |
| `-n`   | Show line numbers |
| `-h`   | Suppress filenames in output |
| `-s`   | Suppress error messages |
| `-f`   | Read patterns from file |
| `-o`   | Show only matched parts |
## Build Instructions
### s21_cat
```bash
cd cat/
make
cd test/
bash test.sh
```
### s21_grep
```bash
cd grep/
make
cd test/
bash test.sh
```
