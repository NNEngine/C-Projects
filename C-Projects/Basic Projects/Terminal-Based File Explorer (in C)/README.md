# Terminal-Based File Explorer (in C)

### Project Goals

- Navigate directories via command-line input
- List files with basic metadata (name, size, type)
- Open and view content of text files
- Go back to parent directories
- Exit on command

### Requirements

- Compiler: gcc (used version: (MinGW.org GCC-6.3.0-1) 6.3.0)
- Libraries:
  - **<dirent.h>** for directory handling
  - **<stdio.h>**, **<stdlib.h>** for I/O
  - **<string.h>** for string operations
  - **<sys/stat.h>** for file metadata
  - **<unistd.h>** for path operations (Linux/Mac)
