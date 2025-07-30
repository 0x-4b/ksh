# C Shell

[![C](https://img.shields.io/badge/C-99%2B-blue.svg)](https://en.cppreference.com/)
[![Unix](https://img.shields.io/badge/Unix-Compatible-green.svg)](https://en.wikipedia.org/wiki/Unix)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

A minimal, functional shell implementation in C with essential features for command execution, directory navigation, and command history. Built for simplicity and educational purposes — no bloat, just clean system calls and process management.

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Project Structure](#project-structure)
- [Technical Details](#technical-details)
- [Contributing](#contributing)
- [License](#license)
- [Author](#author)

---

## Overview

**C Shell** is a lightweight shell implementation that provides core shell functionality through clean C code. It demonstrates fundamental Unix concepts like process creation, command execution, and memory management while maintaining a simple, readable codebase.

---

## Features

- 🖥️ **Command Execution** — Fork/exec model for external programs
- 📂 **Directory Navigation** — Built-in `cd` command with error handling
- 📝 **Command History** — `!!` to repeat last command
- 🗂️ **Current Directory Display** — Shows full path in prompt
- 🧹 **Screen Clearing** — Built-in `clear` command
- 💾 **Dynamic Memory Management** — Proper allocation and cleanup
- 🛠️ **Extensible Design** — Easy to add new built-in commands

---

## Installation

### Prerequisites
- **GCC** or any C99 compatible compiler
- **Unix-like system** (Linux, macOS, WSL)

### Build Instructions
1. **Clone the repository:**
   ```bash
   git clone https://github.com/yourusername/c-shell.git
   cd c-shell
   ```

2. **Compile the shell:**
   ```bash
   gcc -o ksh src/main.c
   ```

3. **Run the shell:**
   ```bash
   ./ksh
   ```

---

## Usage

Start the shell and you'll see a prompt showing your current directory:

```bash
/home/user/projects/c-shell > ls -la
/home/user/projects/c-shell > cd ..
/home/user/projects > !!
/home/user/projects > help
```

### Basic Commands
- Type any system command: `ls`, `cat`, `grep`, etc.
- Navigate directories: `cd /path/to/directory`
- Repeat last command: `!!`
- Clear screen: `clear`
- Exit shell: `exit`

---

## Built-in Commands

| Command | Description | Usage |
|---------|-------------|-------|
| `cd` | Change directory | `cd /path/to/dir` |
| `exit` | Exit the shell | `exit` |
| `help` | Show available commands | `help` |
| `clear` | Clear the screen | `clear` |

---

## Project Structure

```
c-shell/
├── src/
│   └── main.c             # Main shell implementation
├── .gitignore            # Git ignore rules
└── README.md             # This file
```

---

## Technical Details

### Core Architecture
- **Process Model**: Uses `fork()` and `execvp()` for command execution
- **Memory Management**: Dynamic allocation with `malloc()` and `realloc()`
- **Command Parsing**: Token-based parsing with `strtok()`
- **Built-in Dispatch**: Function pointer table for internal commands

### Memory Management
- **Dynamic Line Reading**: Automatically expands buffer as needed
- **Command Tokenization**: Efficient string splitting with proper cleanup
- **History Storage**: Simple last-command storage with `strdup()`

### Error Handling
- **System Call Validation**: Proper error checking with `perror()`
- **Memory Allocation**: Graceful failure handling
- **Command Not Found**: Clear error messages for invalid commands

---

## Contributing

Contributions welcome! This is a learning project, so improvements and educational enhancements are especially appreciated.

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/your-feature`)
3. Write clean, commented C code
4. Test thoroughly on Unix systems
5. Push and open a Pull Request

Please maintain the simple, educational nature of the codebase.

---

## License

This project is licensed under the [MIT License](LICENSE).

---

## Author

**0x-4b**  
GitHub: [@0x-4b](https://github.com/0x-4b)
