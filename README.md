# Medical Scan Compression & Encryption Software

**ANSI C (C89) compliant** – Lossless RLE compression + XOR/RC4 encryption for PGM medical images.

---

## Overview

This command‑line tool demonstrates two essential techniques for handling medical image data:

1. **Run‑Length Encoding (RLE)** – Compresses grayscale PGM images by merging consecutive identical pixel values.
2. **Stream Cipher Encryption** – Protects compressed data using either:
   - **XOR cipher** (single‑byte key, generated randomly)
   - **RC4 cipher** (password‑based, up to 256‑byte key)

Designed for **educational use** – shows low‑level C89 programming, memory management, file I/O, and basic cryptography.

---

## Features

| Feature             | Description                                                                         |
|---------------------|-------------------------------------------------------------------------------------|
| **Read PGM**        | Loads binary P5 (grayscale) images, extracts width, height, and pixel array.        |
| **Write PGM**       | Saves a pixel array back to a valid PGM file (P5 format, max pixel 255).            |
| **RLE Compression** | Lossless compression – output format `[value, length]`. Max run length = 255 bytes. |
| **RLE Decompression** | Restores original pixel array exactly.                                            |
| **XOR Encryption**  | Single‑byte key (0–255). Key generated randomly and displayed to user.              |
| **RC4 Encryption**  | Password‑based stream cipher (any length up to 255 bytes).                          |
| **Decryption**      | Automatic detection of which cipher was used (XOR or RC4). No user guesswork.       |
| **Safety Checks**   | Prevents double encryption; warns if no data to compress/encrypt.                   |
| **ANSI C (C89)**    | Portable code – compiles with `-ansi -Wall -Werror` on any standard compiler.       |

---

## Compilation

Compile **all three source files** together:

gcc -ansi -Wall -Werror main.c compression.c encryption.c

## Usage

### Running the Program

After compiling, start the program:

./a.out OR ./a.exe (depending on terminal)

### Inputting  a file

The dataset provided under /dataset contains 10 medical scans from the NIH Chest X-ray Dataset. It contains pgm files -- 5 P2 and 5 P5 (in order in folder). The dataset provided is purely for testing and the program goes beyond the test dataset. Inputting files is done using relative file path so ensure to call in the format of "dataset/image.pgm"