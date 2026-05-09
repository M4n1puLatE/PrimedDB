# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

PrimedDB is a C++20 database system project with SQL compilation capabilities. The codebase is organized as a collection of static libraries built with CMake, using modern C++ features and several external dependencies.

## Build System

### Dependencies
- **Boost** (multiple components: system, filesystem, thread, log, log_setup, atomic, date_time, regex, chrono, serialization)
- **GMP** (GNU Multiple Precision Arithmetic Library)
- **Crypto++** (cryptopp)

Install these dependencies before building. On Windows, consider using vcpkg or system package managers.

### CMake Presets
The project uses CMake presets for different configurations:
- `x64-debug` - 64-bit Debug build (Windows)
- `x64-release` - 64-bit Release build (Windows)
- `x86-debug` - 32-bit Debug build (Windows)
- `x86-release` - 32-bit Release build (Windows)
- `linux-debug` - Linux Debug build
- `macos-debug` - macOS Debug build

All presets use the Ninja generator. Build outputs are placed in `out/build/${presetName}`.

### Building the Project
```bash
# Configure with a preset (example: x64-debug)
cmake --preset x64-debug

# Build the project
cmake --build out/build/x64-debug

# For Visual Studio developers, you can also open the generated solution
```

### Running Tests
The `Tester` executable contains all unit tests and is the primary test runner:
```bash
# After building, run the test executable
./out/build/x64-debug/Tester/Tester.exe  # Windows
./out/build/x64-debug/Tester/Tester      # Linux/macOS
```

Currently, the test runner focuses on Lexer tests (see `Tester/src/Tests.cpp`). Additional test components can be enabled by uncommenting lines in the main function.

### Main Executable
The `PrimedDB` executable (`out/build/x64-debug/PrimedDB/PrimedDB.exe`) links all libraries and serves as the main database application. Currently it's a placeholder implementation that will evolve into the full database system.

## Code Architecture

### Module Structure
Each subdirectory represents a static library with its own `CMakeLists.txt`:

1. **Compiler** - SQL lexical analysis and parsing
   - `Lexer` - Tokenization and lexical analysis
   - `Parser` - SQL statement parsing
   - `Token` - Token type definitions and utilities
   - `State` - State machine components for lexing
   - Located in `Compiler/include/` and `Compiler/src/`

2. **Util** - General utilities
   - String manipulation (`Util::Util::SplitString`, `IndexSplitString`)
   - Timer classes (`Timer`, `TimerPlus`)
   - TimeStamp management
   - Singleton pattern implementation
   - Manager class for resource management
   - Located in `Util/include/` and `Util/src/`

3. **LogLib** - Logging system
   - `ClassInfo` - Runtime class/function introspection
   - Log management and formatting
   - Located in `LogLib/include/` and `LogLib/src/`

4. **ErrorHandler** - Error management (currently minimal implementation)

5. **Command** - Command-line interface components (links with Util)

6. **Network**, **StorageUnit**, **Transaction** - Planned modules (currently commented out in root CMakeLists.txt)

7. **PrimedDB** - Main database library (placeholder implementation)

8. **Tester** - Test executable that links all libraries

### Key Design Patterns
- **Singleton**: Used in manager classes
- **Factory**: Token creation patterns in Compiler
- **State Machine**: Lexer implements a state machine for tokenization
- **RAII**: Resource management throughout codebase

### Namespace Convention
- `Compiler` - All compiler-related classes
- `Util` - Utility classes
- `Log` - Logging system
- `Tester` - Test framework

### SQL Support
The Compiler module recognizes a comprehensive set of SQL tokens including:
- Keywords: `SELECT`, `FROM`, `INSERT`, `WHERE`, `CREATE`, `UPDATE`, etc.
- Operators: Arithmetic, logical, comparison, bitwise
- Literals: String, integer, double
- Punctuation: Brackets, commas, semicolons

## Development Workflow

### Adding New Features
1. Place header files in `ModuleName/include/`
2. Place implementation in `ModuleName/src/`
3. Update the module's `CMakeLists.txt` if adding new source files
4. Link dependencies in `target_link_libraries`
5. Add tests in `Tester/src/` with corresponding headers in `Tester/include/`

### Running Specific Tests
Modify `Tester/src/Tests.cpp` to enable/disable specific test suites:
```cpp
// Currently only Lexer tests are enabled
LexerTester lexerTest;
lexerTest.run();

// To enable other tests, uncomment:
// UtilTester utilTest;
// utilTest.run();
// ClassInfoTester classInfoTest;
// classInfoTest.run();
// etc.
```

### Debugging
- The project generates `compile_commands.json` for tooling integration
- Uses MSVC EditAndContinue for Debug builds on Windows
- Logging system available for runtime diagnostics

## Common Issues

### Missing Dependencies
If CMake fails to find Boost, GMP, or Crypto++:
- Ensure they are installed and discoverable by CMake
- Consider setting `BOOST_ROOT`, `GMP_ROOT`, etc. environment variables
- On Windows, vcpkg can manage these dependencies

### Build Failures
- Verify CMake version >= 3.18
- Check that all subdirectory `CMakeLists.txt` files are valid
- Ensure no circular dependencies between libraries

### Test Failures
- Check that the Lexer is properly initialized
- Verify token definitions match expected SQL grammar
- Examine log output for diagnostic information

## Code Style
- C++20 standard with `CMAKE_CXX_STANDARD 20`
- `#pragma once` for include guards
- PascalCase for class names, camelCase for methods
- Member variables prefixed with `m_`
- Extensive use of `const` and `noexcept` where appropriate
- Smart pointers (`std::unique_ptr`, `std::shared_ptr`) for resource management

## Documentation
- Chinese documentation in `docs/CN/doc/`
- Module-specific documentation in respective subdirectories
- Documented using Markdown with Obsidian-based organization
- Architecture diagrams and design notes in `docs/`

This file should be updated as the project evolves to reflect new modules, build changes, or architectural decisions.