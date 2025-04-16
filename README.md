# Pi Digit Checker

This program searches for a specific sequence of numbers within the digits of pi.

## Requirements

MacOS:

- C++ compiler (g++)
- libcurl library
- make

Windows:

- MSYS2
- C++ compiler (g++)
- curl library

## Installation

Installing libcurl on macOS:

```bash
brew install curl
```

Installing libcurl on Windows:

Open "C:\msys64\mingw64.exe"

```bash
pacman -S mingw-w64-x86_64-curl
```

## Usage

For macOS:

1. Write the number to search for in the `check.txt` file.
2. To compile the program:
   ```bash
   make
   ```
3. To run the program:
   ```bash
   ./pi_checker
   ```

For Windows:

1. Write the number to search for in the `check.txt` file.
2. Open "C:\msys64\mingw64.exe".
3. To compile the program:

   ```bash
   g++ pi_checker.cpp -o pi_checker.exe -lcurl
   ```

4. To run the program:
   ```bash
   ./pi_checker
   ```

## Cleanup

To clean up compiled files:

For macOS:

```bash
make clean
```

For Windows:

Just delete `pi_checker.exe`.
